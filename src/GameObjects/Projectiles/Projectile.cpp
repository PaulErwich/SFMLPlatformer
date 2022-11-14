//
// Created by MLG Erwich on 07/04/2022.
//

#include "Projectile.h"
Projectile::Projectile(sf::RenderWindow& game_window) : GameObject(game_window)
{
}

bool Projectile::init(float x, float y)
{
  if (!texture->loadFromFile("Data/Images/Extra/bullet.png"))
  {
    std::cout << "bullet didn't load" << std::endl;
    return false;
  }

  sprite->setTexture(*texture);
  sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);
  sprite->setPosition(x, y);
  sprite->scale(0.5, 0.5);
  movement = Vector2(5, 0);
  visible = false;
  sprite->rotate(45);

  return true;
}

void Projectile::prepareBullet(const sf::Vector2f& player_pos, const sf::Vector2f& end_pos)
{
  float change_x = end_pos.x - player_pos.x;
  float change_y = end_pos.y - player_pos.y;
  Vector2 movement(change_x, change_y);
  movement.normalise();
  movement.x *= 3;
  movement.y *= 3;
  setMovement(movement);

  float dx = player_pos.x - end_pos.x;
  float dy = player_pos.y - end_pos.y;
  float rotation = (std::atan2(dy, dx)) * 180 / M_PI;
  sprite->setRotation(rotation + 180 + 45);
}

void Projectile::update(float dt)
{
  sprite->move(movement.x * SPEED * dt, movement.y * SPEED * dt);
  setMin();
  calculateMax();

  if (min.x < 0 || max.x > window.getView().getCenter().x + window.getSize().x / 2 || min.y < 0)
  {
    visible = false;
  }
}
