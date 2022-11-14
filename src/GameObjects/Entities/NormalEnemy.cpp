//
// Created by MLG Erwich on 25/04/2022.
//

#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(sf::RenderWindow& game_window) : Entity(game_window)
{
  for (int i = 0; i < MAX_BULLETS; i++)
  {
    bullets[i] = new Projectile(window);
  }
  active_bullets = 0;
}

NormalEnemy::~NormalEnemy()
{
  for (int i = 0; i < MAX_BULLETS; i++)
  {
    delete bullets[i];
  }
}

bool NormalEnemy::init(float x, float y)
{
  if (!texture->loadFromFile("Data/Images/kenney_pixelplatformer/Characters/character_0001.png"))
  {
    return false;
  }

  sprite->setTexture(*texture);
  sprite->setScale(2, 2);
  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;

  sprite->setPosition(x + ((60 - width) / 2), y + (60 - height));

  setMin();
  calculateMax();

  for (int i = 0; i < MAX_BULLETS; i++)
  {
    bullets[i]->init(0, 0);
  }

  return true;
}

void NormalEnemy::fire()
{
  if (!bullets[active_bullets]->getVisible() && timer.getElapsedTime().asSeconds() >= 3)
  {
    bullets[active_bullets]->getSprite()->setPosition(sprite->getPosition().x + width / 2, sprite->getPosition().y + height / 2);
    bullets[active_bullets]->setVisible(true);
    bullets[active_bullets]->setMovement(Vector2(-3, 0));
    bullets[active_bullets]->getSprite()->rotate(180);
    timer.restart();

    if (active_bullets == MAX_BULLETS - 1) { active_bullets = 0; }
    else { active_bullets++; };
  }
}

void NormalEnemy::update(float dt, Entity* player, GameObject* floor)
{
  fire();

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

void NormalEnemy::render()
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