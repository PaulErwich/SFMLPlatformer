//
// Created by MLG Erwich on 08/03/2022.
//

#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

#include "Entity.h"

class Player : public Entity
{
 public:
  Player(sf::RenderWindow& game_window);
  bool init() override;

  void reset();

  void setOnGround(bool _on_ground);

  void setMin() override;
  void calculateMax() override;

  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  void update(float dt) override;

  void render() override;

 private:
  bool on_ground;
  const int SPEED = 100;
  sf::Sprite gun;
  sf::Texture gun_texture;
};

#endif // PLATFORMERSFML_PLAYER_H
