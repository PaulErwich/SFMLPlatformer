//
// Created by MLG Erwich on 26/04/2022.
//

#include "HomingEnemy.h"

HomingEnemy::HomingEnemy(sf::RenderWindow& game_window) : Entity(game_window)
{
  for (int i = 0; i < MAX_BULLETS; i++)
  {
    bullets[i] = new Projectile(window);
  }
  
  active_bullets = 0;
}

HomingEnemy::~HomingEnemy()
{
  for (int i = 0; i < MAX_BULLETS; i++)
  {
    delete bullets[i];
  }
}

bool HomingEnemy::init(float x, float y)
{
  if (!texture->loadFromFile("Data/Images/kenney_pixelplatformer/Characters/character_0010.png"))
  {
    return false;
  }

  sprite->setTexture(*texture);
  sprite->setScale(2, 2);
  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;
  sprite->setPosition(x + ((60 - width) / 2), y + ((60 - height) / 2));

  setMin();
  calculateMax();

  for (int i = 0; i < MAX_BULLETS; i++)
  {
    bullets[i]->init(0, 0);
  }

  return true;
}

void HomingEnemy::fire(Entity* player)
{
  if (!bullets[active_bullets]->getVisible() && timer.getElapsedTime().asSeconds() >= 3)
  {
    bullets[active_bullets]->getSprite()->setPosition(sprite->getPosition());
    bullets[active_bullets]->setVisible(true);
    bullets[active_bullets]->prepareBullet(sprite->getPosition(), player->getSprite()->getPosition());
    timer.restart();

    if (active_bullets == MAX_BULLETS - 1) { active_bullets = 0; }
    else { active_bullets++; }
  }
}

void HomingEnemy::update(float dt, Entity* player, GameObject* floor)
{
  fire(player);

  for (int i = 0; i < MAX_BULLETS; i++)
  {
    if (bullets[i]->getVisible())
    {
      bullets[i]->update(dt);

      if (bullets[i]->AABB(player))
      {
        player->changeHp(-1);
        bullets[i]->setVisible(false);
      }

      if (bullets[i]->AABB(floor))
      {
        bullets[i]->setVisible(false);
      }
    }
  }
}

void HomingEnemy::render()
{
  GameObject::render();

  for (int i = 0; i < MAX_BULLETS; i++)
  {
    if (bullets[i]->getVisible())
    {
      bullets[i]->render();
    }
  }
}