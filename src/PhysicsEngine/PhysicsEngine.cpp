//
// Created by MLG Erwich on 05/03/2022.
//

#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
  for (int i = 0; i < MAX_NUMBER_OF_OBJECTS; i++)
  {
    objects[i] = nullptr;
  }
}

PhysicsEngine::~PhysicsEngine()
{
  for (int i = 0; i < MAX_NUMBER_OF_OBJECTS; i++)
  {
    delete objects[i];
  }
}

bool PhysicsEngine::AABBvsAABB_MK2(Manifold *m)
{
  // Determine if there was a collision and then calculate the penetration distance
  // And the normal value of the collision
  // Work for 2 objects that both have AABB shapes
  // Can then do something with those values
  Body *a = m->A;
  Body *b = m->B;

  Vector2 n(b->gameObject->getMin().x - a->gameObject->getMin().x,
            b->gameObject->getMin().y - a->gameObject->getMin().y);

  AABB abox;
  abox.min = a->gameObject->getMin();
  abox.max = a->gameObject->getMax();
  AABB bbox;
  bbox.min = b->gameObject->getMin();
  bbox.max = b->gameObject->getMax();

  float a_extent_x = (abox.max.x - abox.min.x) / 2;
  float b_extent_x = (bbox.max.x - bbox.min.x) / 2;

  float x_overlap = a_extent_x + b_extent_x - std::abs(n.x);

  if (x_overlap > 0)
  {
    float a_extent_y = (abox.max.y - abox.min.y) / 2;
    float b_extent_y = (bbox.max.y - bbox.min.y) / 2;

    float y_overlap = a_extent_y + b_extent_y - std::abs(n.y);

    if (y_overlap > 0)
    {
      std::cout << "collide" << std::endl;
      if (x_overlap < y_overlap)
      {
        if (n.x < 0)
          m->normal = Vector2(-1, 0);
        else
          m->normal = Vector2(1, 0);
        m->penetration = x_overlap;
        return true;
      }
      else
      {
        if (n.y < 0)
          m->normal = Vector2(0, -1);
        else
          m->normal = Vector2(0, 1);
        m->penetration = y_overlap;
        return true;
      }
    }
  }
  return false;
}

float PhysicsEngine::SweptAABB(Manifold* m, float dt)
{
  float xInvEntry, yInvEntry;
  float xInvExit, yInvExit;

  Body *a = m->A;
  Body *b = m->B;

  if (a->velocity.x * dt * 100 > 0.0f)
  {
    xInvEntry = b->gameObject->getMin().x - (a->gameObject->getMin().x + a->gameObject->getWidth());
    xInvExit = (b->gameObject->getMin().x + b->gameObject->getWidth()) - a->gameObject->getMin().x;
  }
  else
  {
    xInvEntry = (b->gameObject->getMin().x + b->gameObject->getWidth()) - a->gameObject->getMin().x;
    xInvExit = b->gameObject->getMin().x - (a->gameObject->getMin().x + a->gameObject->getWidth());
  }

  if (a->velocity.y * dt * 100 > 0.0f)
  {
    yInvEntry = b->gameObject->getMin().y - (a->gameObject->getMin().y + a->gameObject->getHeight());
    yInvExit = (b->gameObject->getMin().y + b->gameObject->getHeight()) - a->gameObject->getMin().y;
  }
  else
  {
    yInvEntry = (b->gameObject->getMin().y + b->gameObject->getHeight()) - a->gameObject->getMin().y;
    yInvExit = b->gameObject->getMin().y - (a->gameObject->getMin().y + a->gameObject->getHeight());
  }

  float xEntry, yEntry;
  float xExit, yExit;

  if (a->velocity.x * dt * 100 == 0.0f)
  {
    xEntry = -std::numeric_limits<float>::infinity();
    xExit = std::numeric_limits<float>::infinity();
  }
  else
  {
    xEntry = xInvEntry / (a->velocity.x * 100 * dt);
    xExit = xInvExit / (a->velocity.x * 100 * dt);
  }

  if (a->velocity.y * dt * 100 == 0.0f)
  {
    yEntry = -std::numeric_limits<float>::infinity();
    yExit = std::numeric_limits<float>::infinity();
  }
  else
  {
    yEntry = yInvEntry / (a->velocity.y * dt * 100);
    yExit = yInvExit / (a->velocity.y * dt * 100);
  }

  float entryTime = std::max(xEntry, yEntry);
  float exitTime = std::min(xExit, yExit);

  if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
  {
    m->normal.x = 0.0f;
    m->normal.y = 0.0f;
    return 1.0f;
  }
  else // if there was a collision
  {
    // calculate normal of collided surface
    if (xEntry > yEntry)
    {
      if (xInvEntry < 0.0f)
      {
        m->normal.x = 1.0f;
        m->normal.y = 0.0f;
      }
      else
      {
        m->normal.x = -1.0f;
        m->normal.y = 0.0f;
      }
    }
    else
    {
      if (yInvEntry < 0.0f)
      {
        m->normal.x = 0.0f;
        m->normal.y = 1.0f;
      }
      else
      {
        m->normal.x = 0.0f;
        m->normal.y = -1.0f;
      }
    }
  } // return the time of collision
  return entryTime;
}

void PhysicsEngine::ResolveCollisions(Manifold* m)
{
  // Used for bouncing objects off each other?
  Body *a = m->A;
  Body *b = m->B;

  Vector2 rv(b->velocity.x - a->velocity.x, b->velocity.y - a->velocity.y);

  float velAlongNormal = DotProduct(rv, m->normal);

  // Only resolve collision if objects are moving towards each other
  if(velAlongNormal > 0)
  {
    return;
  }

  float e = std::min(a->material.restitution, b->material.restitution);

  float j = -(1 + e) * velAlongNormal;

  j /= (a->mass_data.inv_mass + b->mass_data.inv_mass);

  Vector2 impulse(m->normal.x * j, m->normal.y * j);
/*
  // Applying impulse v1
  a->velocity.x -= a->mass_data.inv_mass * impulse.x;
  a->velocity.y -= a->mass_data.inv_mass * impulse.y;

  b->velocity.x += b->mass_data.inv_mass * impulse.x;
  b->velocity.y += b->mass_data.inv_mass * impulse.y;
*/

  // applying impulse v2 but based on object mass
  float mass_sum = a->mass_data.mass + b->mass_data.mass;
  float ratio = a->mass_data.mass / mass_sum;
  a->velocity.x -= ratio * impulse.x;
  a->velocity.y -= ratio * impulse.y;

  if (b->mass_data.mass != 0)
  {
    ratio = b->mass_data.mass / mass_sum;
    b->velocity.x -= ratio * impulse.x;
    b->velocity.y -= ratio * impulse.y;
  }
}

void PhysicsEngine::PositionalCorrection(Manifold* m)
{
  // Linear projection method to stop sinking objects - think it's the jittering
  // Reduces object penetration of 2 objects by small amount.
  Body *a = m->A;
  Body *b = m->B;

  // Percentage to move objects by
  const float percent = 0.8;
  // Slack given to stop jitter between objects that are resting on each other
  const float slop = 0.5;

  Vector2 correction(std::max(m->penetration - slop, 0.0f) /
                       (a->mass_data.inv_mass + b->mass_data.inv_mass) * percent * m->normal.x,
                     std::max(m->penetration - slop, 0.0f) /
                       (a->mass_data.inv_mass + b->mass_data.inv_mass) * percent * m->normal.y);

  Vector2 a_current_pos(a->gameObject->getMin());
  Vector2 b_current_pos(b->gameObject->getMin());

  a_current_pos.x -= a->mass_data.inv_mass * correction.x;
  a_current_pos.y -= a->mass_data.inv_mass * correction.y;

  b_current_pos.x += a->mass_data.inv_mass * correction.x;
  b_current_pos.y += a->mass_data.inv_mass * correction.y;
}

float PhysicsEngine::DotProduct(Vector2 &a, Vector2 &b) { return (a.x * b.x) + (a.y * b.y); }

void PhysicsEngine::setObject(Body* body, int index) { objects[index] = body; }

void PhysicsEngine::update(float dt)
{
  for (int i = 0; i < MAX_NUMBER_OF_OBJECTS; i++)
  {
    if (objects[i] != nullptr)
    {
      //if (objects[i]->mass_data.mass != 0)
      {
        // Move objects based on their acceleration
        if (objects[i]->mass_data.mass != 0)
        {
          Vector2 acceleration;
          // Generate acceleration if object has mass and a force is being applied
          if (objects[i]->force.x != 0)
          { acceleration.x = objects[i]->force.x / objects[i]->mass_data.mass; }

          if (objects[i]->force.y != 0)
          { acceleration.y = objects[i]->force.y / objects[i]->mass_data.mass; }

          // Change velocity as long as it's within a certain range
          if (objects[i]->velocity.x < 150 && objects[i]->velocity.x > -150)
          { objects[i]->velocity.x += acceleration.x * dt; }

          if (objects[i]->velocity.y < 150)
          { objects[i]->velocity.y += acceleration.y * dt; }

          // Apply velocity to objects position accordingly
          std::cout << objects[i]->velocity.y << std::endl;
          Vector2 current_pos(objects[i]->gameObject->getSprite()->getPosition().x, objects[i]->gameObject->getSprite()->getPosition().y);
          objects[i]->gameObject->getSprite()->setPosition(current_pos.x + objects[i]->velocity.x * dt,current_pos.y + objects[i]->velocity.y * dt);
          objects[i]->gameObject->setMin();
          objects[i]->gameObject->calculateMax();
          objects[i]->force = Vector2(0, 0);
        }
      }
    }
  }

  Manifold test(objects[0], objects[2]);

  /*
  float collision_time = SweptAABB(&test, dt);
  Vector2 current_pos = objects[0]->gameObject->getMin();
  objects[0]->gameObject->getSprite()->setPosition(current_pos.x + objects[0]->velocity.x * collision_time,
                                                   current_pos.y + objects[0]->velocity.y * collision_time);
  objects[0]->gameObject->setMin();
  objects[0]->gameObject->calculateMax();
  float remaining_time = 1.0f - collision_time;

  if (remaining_time != 0)
  {
    test.A->velocity = Vector2(test.A->velocity.x * remaining_time, test.A->velocity.y * remaining_time);

    if (std::abs(test.normal.x) > 0.0001f) test.A->velocity = Vector2(-test.A->velocity.x, test.A->velocity.y);
    if (std::abs(test.normal.y > 0.0001f)) test.A->velocity = Vector2(test.A->velocity.x, -test.A->velocity.y);

    //PositionalCorrection(&test);
  }*/

  if (AABBvsAABB_MK2(&test))
  {
    //test.A->force = Vector2(0, 0);
    ResolveCollisions(&test);

    //test.A->force = Vector2(0, 0);
    //test.A->velocity = Vector2(0, 0);
    //
  }
}

void PhysicsEngine::render()
{
  for (int i = 0; i < MAX_NUMBER_OF_OBJECTS; i++)
  {
    if (objects[i] != nullptr)
    {
      objects[i]->gameObject->render();
    }
  }
}