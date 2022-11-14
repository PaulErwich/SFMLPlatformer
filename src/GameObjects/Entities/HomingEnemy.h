//
// Created by MLG Erwich on 26/04/2022.
//

#ifndef PLATFORMERSFML_HOMINGENEMY_H
#define PLATFORMERSFML_HOMINGENEMY_H

#include "Entity.h"
#include "../Projectiles/Projectile.h"

class HomingEnemy : public Entity
{
 public:
  HomingEnemy(sf::RenderWindow& game_window);
  ~HomingEnemy();

  bool init(float x, float y) override;

  void fire(Entity *player);

  void update(float dt, Entity *player, GameObject* floor) override;
  void render() override;

 private:
  sf::Clock timer;
  static const int MAX_BULLETS = 5;
  int active_bullets;
  Projectile* bullets[MAX_BULLETS];

};

#endif // PLATFORMERSFML_HOMINGENEMY_H
