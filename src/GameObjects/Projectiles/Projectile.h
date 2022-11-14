//
// Created by MLG Erwich on 07/04/2022.
//

#ifndef PLATFORMERSFML_PROJECTILE_H
#define PLATFORMERSFML_PROJECTILE_H

#include "../GameObject.h"
#include <cmath>

class Projectile : public GameObject
{
 public:
  Projectile(sf::RenderWindow& game_window);

  bool init(float x, float y);

  // Prepare homing bullet
  // This is for bullets that go to a specific location
  // Such as the player's bullets that go to the mouse position
  void prepareBullet(const sf::Vector2f& player_pos, const sf::Vector2f& end_pos);

  void update(float dt) override;

 private:
  const int SPEED = 100;
};

#endif // PLATFORMERSFML_PROJECTILE_H
