//
// Created by MLG Erwich on 25/04/2022.
//

#ifndef PLATFORMERSFML_NORMALENEMY_H
#define PLATFORMERSFML_NORMALENEMY_H

#include "Entity.h"
#include "../Projectiles/Projectile.h"

class NormalEnemy : public Entity
{
 public:
  NormalEnemy(sf::RenderWindow& game_window);
  ~NormalEnemy();

  bool init(float x, float y) override;

  void fire();

  void update(float dt, Entity *player, GameObject* floor) override;
  void render() override;

 private:
  sf::Clock timer;
  static const int MAX_BULLETS = 5;
  int active_bullets;
  Projectile* bullets[MAX_BULLETS];
};

#endif // PLATFORMERSFML_NORMALENEMY_H
