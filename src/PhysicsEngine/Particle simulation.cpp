//
// Created by MLG Erwich on 06/03/2022.
//

// Particle testing
// Working particle simulation
/*
#include <iostream>
#include <windows.h>

#define random(min, max) rand() % (max + 1 - min) + min // The function I've used to generate random numbers

struct vector
{
  vector(float _x, float _y)
  {
    x = _x;
    y = _y;
  }
  float x;
  float y;
};

struct Particle
{
  Particle(vector position, vector velocity) : position(position), velocity(velocity)
  {
    mass = 1;
  }
  vector position;
  vector velocity;
  float mass;
};

const int PARTICLE_NUM = 1;
Particle particles[PARTICLE_NUM] = {Particle(vector(0, 0), vector(0, 0))};

void PrintParticles()
{
  for (int i = 0; i < PARTICLE_NUM; i++)
  {
    Particle *particle = &particles[i];
    std::cout << "particle " << i << " , " << particle->position.x << ", " << particle->position.y << std::endl;
  }
}

void InitializeParticles()
{
  for (int i = 0; i < PARTICLE_NUM; i++)
  {
    particles[i].position.x = random(0, 50);
    particles[i].position.y = random(0, 50);
    particles[i].velocity.x = 0;
    particles[i].velocity.y = 0;
    particles[i].mass = 1;
  }
}

vector ComputeForce(Particle *particle)
{
  // Apply Earths gravitational force
  return vector(0, particle->mass * -9.81);
}

int main()
{
  float totalSimulationTime = 10;
  float currentTime = 0;
  float dt = 1;

  InitializeParticles();
  PrintParticles();

  while (currentTime < totalSimulationTime)
  {
    Sleep(dt);

    for (int i = 0; i < PARTICLE_NUM; i++)
    {
      Particle *particle = &particles[i];
      vector force = ComputeForce(particle);
      vector acceleration = vector(force.x / particle->mass, force.y / particle->mass);

      particle->velocity.x += acceleration.x * dt;
      particle->velocity.y += acceleration.y * dt;

      particle->position.x += particle->velocity.x * dt;
      particle->position.y += particle->velocity.y * dt;
    }

    PrintParticles();
    currentTime += dt;
  }

  return 0;
}
*/