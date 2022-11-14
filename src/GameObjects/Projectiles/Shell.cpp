//
// Created by MLG Erwich on 08/04/2022.
//

#include "Shell.h"
Shell::Shell(sf::RenderWindow& game_window) : GameObject(game_window)
{
  apex = 0;
  center_x = 0;
  a = 0;
  b = 0;
  c = 0;
}

bool Shell::init(float x, float y)
{
  if (!texture->loadFromFile("Data/Images/Extra/shell.png"))
  {
    std::cout << "shell didn't load" << std::endl;
    return false;
  }
  visible = false;

  sprite->setTexture(*texture);
  sprite->setPosition(x, y);
  return true;
}

void Shell::prepareShell(const Vector2& start_pos, const Vector2& end_pos)
{
  start_position = start_pos;
  end_position = end_pos;

  sprite->setPosition(start_pos.x, start_pos.y);
  visible = true;

  float x_change = -(start_pos.x - end_pos.x);

  center_x = start_pos.x + x_change / 2;

  if (start_pos.y <= end_pos.y)
  {
    apex = start_pos.y - 300;
  }
  else
  {
    apex = end_pos.y - 300;
  }


  mid = Vector2(center_x, apex);

  // Without this, it goes quick when you get close
  // This is because there's no Y value when normalising the vector
  movement.y = start_position.y;

  movement.x = x_change;
  movement.normalise();
  movement.x *= 8;

  recalculateY();
  std::cout << movement.y << std::endl;
}

void Shell::recalculateY()
{
  float x = sprite->getPosition().x;

  Vector2 p1 = start_position;
  Vector2 p2 = end_position;
  Vector2 p3 = mid;

  float denom;
  denom = (p1.x - p2.x) * (p1.x - p3.x) * (p2.x - p3.x);
  a = (p3.x * (p2.y - p1.y) + p2.x * (p1.y - p3.y) + p1.x * (p3.y - p2.y)) / denom;
  b = (p3.x*p3.x * (p1.y - p2.y) + p2.x * p2.x * (p3.y - p1.y) + p1.x * p1.x * (p2.y - p3.y)) / denom;
  c = (p2.x * p3.x * (p2.x - p3.x) * p1.y + p3.x * p1.x * (p3.x - p1.x) * p2.y + p1.x * p2.x * (p1.x - p2.x) * p3.y) / denom;

  movement.y = (a * x * x) + (b * x) + c;
  sprite->setPosition(sprite->getPosition().x + movement.x, movement.y);
}

void Shell::update(float dt)
{
  recalculateY();
  setMin();
  calculateMax();
}
