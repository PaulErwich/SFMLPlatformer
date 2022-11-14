//
// Created by MLG Erwich on 08/04/2022.
//

#ifndef PLATFORMERSFML_SHELL_H
#define PLATFORMERSFML_SHELL_H

#include "../GameObject.h"

class Shell : public GameObject
{
 public:
  Shell(sf::RenderWindow& game_window);

  bool init(float x, float y);
  void prepareShell(const Vector2& start_pos, const Vector2& end_pos);

  void update(float dt) override;
 private:
  Vector2 start_position;
  Vector2 end_position;
  Vector2 mid;

  float apex;
  float center_x;
  float a;
  float b;
  float c;

  void recalculateY();
};

#endif // PLATFORMERSFML_SHELL_H
