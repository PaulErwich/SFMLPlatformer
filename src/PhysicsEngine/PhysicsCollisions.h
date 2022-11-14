//
// Created by MLG Erwich on 14/03/2022.
//

#ifndef PLATFORMERSFML_PHYSICSCOLLISIONS_H
#define PLATFORMERSFML_PHYSICSCOLLISIONS_H

#include "PhysicsStructs.h"

bool AABBvsAABB_MK2(Object_Manifold *m);

float sweptAABB(Object_Manifold *m, float dt);

bool AABBvsAABB_MK3(Object_Manifold *m);

#endif // PLATFORMERSFML_PHYSICSCOLLISIONS_H
