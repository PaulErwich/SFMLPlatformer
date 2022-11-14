//
// Created by MLG Erwich on 06/03/2022.
//

#ifndef PLATFORMERSFML_PHYSICSSTRUCTS_H
#define PLATFORMERSFML_PHYSICSSTRUCTS_H

#include "../Extra/Vector2.h"
#include "../GameObjects/GameObject.h"

enum class BODY_TYPE
{
  PLAYER = 1,
  ENEMY = 2,
  BOX = 3
};

struct AABB
{
  Vector2 min = Vector2(0, 0);
  Vector2 max = Vector2(0, 0);
};

struct MassData
{
  MassData();
  MassData(float _mass);

  float mass;
  // Remember to calculate this 1 / mass
  float inv_mass;
};

struct Material
{
  Material();
  Material(float _density, float _restitution);

  float density = 0;
  float restitution = 0;
};

struct Body
{
  Body();
  Body(GameObject *_gameObject, float _density, float _restitution);

  GameObject *gameObject;
  Material material;
  MassData mass_data;
  Vector2 velocity;
  Vector2 force;
  //float gravityScale; // Real number
};

struct Manifold
{
  Manifold();
  Manifold(Body* a, Body* b);

  Body *A;
  Body *B;
  float penetration;
  Vector2 normal;
};

struct Object_Manifold
{
  Object_Manifold();
  Object_Manifold(GameObject *a, GameObject *b);

  GameObject *A;
  GameObject *B;

  float penetration;
  Vector2 normal;
};

#endif // PLATFORMERSFML_PHYSICSSTRUCTS_H
