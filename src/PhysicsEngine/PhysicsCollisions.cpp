//
// Created by MLG Erwich on 14/03/2022.
//

#include "PhysicsCollisions.h"

bool AABBvsAABB_MK2(Object_Manifold *m)
{
  // Determine if there was a collision and then calculate the penetration distance
  // And the normal value of the collision
  // Work for 2 objects that both have AABB shapes
  // Can then do something with those values
  GameObject *a = m->A;
  GameObject *b = m->B;

  Vector2 n(b->getMin().x - a->getMin().x,
            b->getMin().y - a->getMin().y);

  AABB abox;
  abox.min = a->getMin();
  abox.max = a->getMax();
  AABB bbox;
  bbox.min = b->getMin();
  bbox.max = b->getMax();

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
      //std::cout << "collide" << std::endl;
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

float sweptAABB(Object_Manifold *m, float dt)
{
  float xInvEntry, yInvEntry;
  float xInvExit, yInvExit;

  GameObject* obj_1 = m->A;
  GameObject* obj_2 = m->B;

  if (obj_1->getMovement().x * dt * 100 > 0.0f)
  {
    xInvEntry = obj_2->getMin().x - (obj_1->getMin().x + obj_1->getWidth());
    xInvExit = (obj_2->getMin().x + obj_2->getWidth()) -
               obj_1->getMin().x;
  }
  else
  {
    xInvEntry = (obj_2->getMin().x + obj_2->getWidth()) -
                obj_1->getMin().x;
    xInvExit = obj_2->getMin().x - (obj_1->getMin().x + obj_1->getWidth());
  }

  if (obj_1->getMovement().y * dt * 100 > 0.0f)
  {
    yInvEntry =
      obj_2->getMin().y - (obj_1->getMin().y +
                                             obj_1->getHeight());
    yInvExit = (obj_2->getMin().y + obj_2->getHeight()) -
               obj_1->getMin().y;
  }
  else
  {
    yInvEntry = (obj_2->getMin().y + obj_2->getHeight()) -
                obj_1->getMin().y;
    yInvExit = obj_2->getMin().y - (obj_1->getMin().y + obj_1->getHeight());
  }

  float xEntry, yEntry;
  float xExit, yExit;

  if (obj_1->getMovement().x * dt * 100 == 0.0f)
  {
    xEntry = -std::numeric_limits<float>::infinity();
    xExit = std::numeric_limits<float>::infinity();
  }
  else
  {
    xEntry = xInvEntry / (obj_1->getMovement().x * 100 * dt);
    xExit = xInvExit / (obj_1->getMovement().x * 100 * dt);
  }

  if (obj_1->getMovement().y * dt * 100 == 0.0f)
  {
    yEntry = -std::numeric_limits<float>::infinity();
    yExit = std::numeric_limits<float>::infinity();
  }
  else
  {
    yEntry = yInvEntry / (obj_1->getMovement().y * dt * 100);
    yExit = yInvExit / (obj_1->getMovement().y * dt * 100);
  }

  float entryTime = std::max(xEntry, yEntry);
  float exitTime = std::min(xExit, yExit);

  //std::cout << entryTime << ", " << exitTime << ", " << xEntry << ", " << yEntry << std::endl;

  if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
  {
    std::cout << "no collision" << std::endl;
    m->normal.x = 0.0f;
    m->normal.y = 0.0f;
    return 1.0f;
  }
  else // if there was obj_1 collision
  {
    std::cout << "collision" << std::endl;
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

bool AABBvsAABB_MK3(Object_Manifold *m)
{
  AABB abox;
  abox.min = m->A->getMin();
  abox.max = m->A->getMax();

  AABB bbox;
  bbox.min = m->B->getMin();
  bbox.max = m->B->getMax();

  float x_pen = 0, y_pen = 0;
  bool right = false, bottom = false;

  if ((bbox.min.x < abox.min.x && abox.min.x < bbox.max.x))
  {

    x_pen = bbox.max.x - abox.min.x;
    right = true;
  }
  else if (bbox.min.x < abox.max.x && abox.max.x < bbox.max.x)
  {
    x_pen = abox.max.x - bbox.min.x;
  }

  if (bbox.min.y < abox.min.y && abox.min.y < bbox.max.y)
  {

    y_pen = bbox.max.y - abox.min.y;
    bottom = true;
  }
  else if (bbox.min.y < abox.max.y && abox.max.y < bbox.max.y)
  {

    y_pen = abox.max.y - bbox.min.y;
  }

  if (x_pen == 0 || y_pen == 0)
  {
    return false;
  }
  else
  {
    if (x_pen < y_pen)
    {
      if (right)
      {
        m->normal = Vector2(-1, 0);
      }
      else
      {
        m->normal = Vector2(1, 0);
      }
    }
    else
    {
      if (bottom)
      {
        m->normal = Vector2(0, -1);
      }
      else
      {
        m->normal = Vector2(0, 1);
      }
    }
    return true;
  }
}