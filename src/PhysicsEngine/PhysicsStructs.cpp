//
// Created by MLG Erwich on 06/03/2022.
//

#include "PhysicsStructs.h"

MassData::MassData()
{
  mass = 0;
  inv_mass = 0;
}

MassData::MassData(float _mass)
{
  mass = _mass;

  if (mass == 0)
  {
    inv_mass = 0;
  }
  else
  {
    inv_mass = 1 / mass;
  }
}

Material::Material()
{
  density = 0;
  restitution = 0;
}

Material::Material(float _density, float _restitution)
{
    density = _density;
    restitution = _restitution;
}

Body::Body()
{
  gameObject = nullptr;
}

Body::Body(GameObject* _gameObject, float _density, float _restitution)
{
  gameObject = _gameObject;

  material.density = _density;
  material.restitution = _restitution;
  mass_data.mass = material.density * gameObject->getWidth() * gameObject->getHeight();

  if (mass_data.mass != 0)
    mass_data.inv_mass = 1 / mass_data.mass;
  else
    mass_data.inv_mass = 0;
}

Manifold::Manifold()
{
  A = nullptr;
  B = nullptr;

  penetration = 0;
}

Manifold::Manifold(Body* a, Body* b)
{
  A = a;
  B = b;

  penetration = 0;
}

Object_Manifold::Object_Manifold()
{
  A = nullptr;
  B = nullptr;

  penetration = 0;
}

Object_Manifold::Object_Manifold(GameObject* a, GameObject* b)
{
  A = a;
  B = b;

  penetration = 0;
}