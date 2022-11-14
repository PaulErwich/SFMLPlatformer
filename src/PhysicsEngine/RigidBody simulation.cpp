//
// Created by MLG Erwich on 06/03/2022.
//

#include <iostream>
#include <windows.h>
#include "../Extra/Vector2.h"

#define random(min, max) rand() % (max + 1 - min) + min // The function I've used to generate random numbers

struct BoxShape
{
  float width;
  float height;
  float mass;
  float momentOfInertia;
};

void CalculateBoxInertia(BoxShape *boxShape)
{
  float m = boxShape->mass;
  float w = boxShape->width;
  float h = boxShape->height;

  boxShape->momentOfInertia = m * (w * w + h * h) / 12;
}

struct RigidBody
{
  Vector2 position = Vector2(0, 0);
  Vector2 linearVelocity = Vector2(0, 0);
  float angle = 0;
  float angularVelocity = 0;
  Vector2 force = Vector2(0, 0);
  float torque = 0;
  BoxShape shape = BoxShape();
};

const int RIGID_BODY_NUM = 1;
RigidBody rigidBodies[RIGID_BODY_NUM];

void PrintRigidBodies()
{
  for (int i = 0; i < RIGID_BODY_NUM; i++)
  {
    RigidBody *rigidBody = &rigidBodies[i];

    std::cout << "body " << i << " , " << rigidBody->position.x << ", " << rigidBody->position.y << std::endl;
    std::cout << "body " << i << " , " << rigidBody->angle << std::endl;
  }
}

void InitializeRigidBodies()
{
  for (int i = 0; i < RIGID_BODY_NUM; i++)
  {
    RigidBody *rigidBody = &rigidBodies[i];
    rigidBody->position = Vector2(random(0, 50), random(0, 50));
    rigidBody->angle = random(0, 360) / 360 * 3.1415 * 2;
    rigidBody->linearVelocity = Vector2(0, 0);
    rigidBody->angularVelocity = 0;

    BoxShape shape;
    shape.mass = 10;
    shape.width = 1 + random(0, 2);
    shape.height = 1 + random(0, 2);
    CalculateBoxInertia(&shape);
    rigidBody->shape = shape;
  }
}

void ComputeForceAndTorque(RigidBody *rigidBody)
{
  Vector2 f = Vector2(0, 100);
  rigidBody->force = f;

  Vector2 r = Vector2(rigidBody->shape.width / 2, rigidBody->shape.height / 2);
  rigidBody->torque = r.x * f.y - r.y * f.x;
}

struct AABB
{
  Vector2 min;
  Vector2 max;
};

bool TestAABBOverlap(AABB *a, AABB *b)
{
  float d1x = b->min.x - a->max.x;
  float d1y = b->min.y - a->max.y;
  float d2x = a->min.x - b->max.x;
  float d2y = a->min.y - b->max.y;

  if (d1x > 0.0f || d1y > 0.0f) return false;

  if (d2x > 0.0f || d2y > 0.0f) return false;

  return true;
}

/*
int main()
{
  float totalSimulationTime = 10;
  float currentTime = 0;
  float dt = 1;

  InitializeRigidBodies();
  PrintRigidBodies();

  while (currentTime < totalSimulationTime)
  {
    Sleep(dt);

    for (int i = 0; i < RIGID_BODY_NUM; i++)
    {
      RigidBody *rigidBody = &rigidBodies[i];
      ComputeForceAndTorque(rigidBody);

      Vector2 linearAcceleration = Vector2(rigidBody->force.x / rigidBody->shape.mass, rigidBody->force.y / rigidBody->shape.mass);
      rigidBody->linearVelocity.x += linearAcceleration.x * dt;
      rigidBody->linearVelocity.y += linearAcceleration.y * dt;

      rigidBody->position.x += rigidBody->linearVelocity.x * dt;
      rigidBody->position.y += rigidBody->linearVelocity.y * dt;

      float angularAcceleration = rigidBody->torque / rigidBody->shape.momentOfInertia;

      rigidBody->angularVelocity += angularAcceleration * dt;
      rigidBody->angle += rigidBody->angularVelocity * dt;
    }

    PrintRigidBodies();
    currentTime += dt;
  }

  return 0;
}
*/