//
// Created by MLG Erwich on 05/03/2022.
//

#ifndef PLATFORMERSFML_PHYSICSENGINE_H
#define PLATFORMERSFML_PHYSICSENGINE_H

#include "PhysicsStructs.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class PhysicsEngine
{
 public:
  PhysicsEngine();
  ~PhysicsEngine();

  bool AABBvsAABB( AABB a, AABB b )
  {
    // Exit with no intersection if found separated along an axis
    if(a.max.x < b.min.x or a.min.x > b.max.x) return false;

    if(a.max.y < b.min.y or a.min.y > b.max.y) return false;

    // No separating axis found, therefor there is at least one overlapping axis
    std::cout << "collide" << std::endl;
    return true;
  }

  bool AABBvsAABB_MK2(Manifold *m);

  float SweptAABB(Manifold *m, float dt);

  void ResolveCollisions(Manifold *m);

  void PositionalCorrection(Manifold *m);

  static float DotProduct(Vector2 &a, Vector2 &b);

  void setObject(Body *body, int index);

  // Allow me to update/render bodies within physics engine
  void update(float dt);
  void render();

 private:
  static const int MAX_NUMBER_OF_OBJECTS = 10;
  Body *objects[MAX_NUMBER_OF_OBJECTS];
  Vector2 Gravity = Vector2(0, 9.81f);
};

#endif // PLATFORMERSFML_PHYSICSENGINE_H
