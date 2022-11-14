//
// Created by MLG Erwich on 04/03/2022.
//

#include "Entity.h"

Entity::Entity(sf::RenderWindow& game_window) : GameObject(game_window)
{
  animation = ANIM_STATE::IDLE;

  current_hp = MAX_HP;
}

bool Entity::init(float x, float y)
{
  return true;
}

void Entity::changeHp(int amount)
{
  current_hp += amount;
  if (current_hp < 0)
  {
    current_hp = 0;
  }
}

int Entity::getHp() const { return current_hp; }

void Entity::animation_handler()
{
  switch (animation)
  {
    case ANIM_STATE::IDLE:
      if (anim_timer.getElapsedTime().asSeconds() > 0.5)
      {
        if (idle_rect.left == 24) { idle_rect.left = 0; }
        else { idle_rect.left += 24; }

        sprite->setTextureRect(idle_rect);
        sprite->setTexture(*texture);
        anim_timer.restart();
      }
      break;
    case ANIM_STATE::RUNNING:
      if (anim_timer.getElapsedTime().asSeconds() > 0.1)
      {
        if (running_rect.left == 72) {running_rect.left = 0; }
        else { running_rect.left += 24; }

        sprite->setTextureRect(running_rect);
        sprite->setTexture(running);
        anim_timer.restart();
      }
      break;
    case ANIM_STATE::JUMPING:
      break;
    default:
      break;
  }
}

void Entity::update(float dt, Entity* player, GameObject* floor) {}

