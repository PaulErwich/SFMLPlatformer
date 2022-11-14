//
// Created by MLG Erwich on 04/03/2022.
//

#ifndef PLATFORMERSFML_ENTITY_H
#define PLATFORMERSFML_ENTITY_H

#include "../GameObject.h"

enum class ANIM_STATE
{
  IDLE = 0,
  RUNNING = 1,
  JUMPING = 2
};

class Entity : public GameObject
{
 public:
  Entity(sf::RenderWindow& game_window);
  virtual bool init(float x, float y);

  void changeHp(int amount);
  int getHp() const;

  void animation_handler();

  virtual void update(float dt, Entity *player, GameObject* floor);

 protected:
  ANIM_STATE animation;

  sf::Texture running;

  sf::IntRect idle_rect;
  sf::IntRect running_rect;

  sf::Clock anim_timer;

  int MAX_HP = 10;
  int current_hp;
};

#endif // PLATFORMERSFML_ENTITY_H
