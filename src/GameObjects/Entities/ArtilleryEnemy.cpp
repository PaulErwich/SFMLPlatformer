//
// Created by p2-erwich on 08/04/2022.
//

#include "ArtilleryEnemy.h"
ArtilleryEnemy::ArtilleryEnemy(sf::RenderWindow& game_window) : Entity(game_window)
{
  for (int i = 0; i < MAX_BULLETS; i++)
  {
    bullets[i] = new Projectile(window);
  }

  for (int i = 0; i < MAX_SHELLS; i++)
  {
    shells[i] = new Shell(window);
  }

  active_bullets = 0;
  active_shell = 0;

}

ArtilleryEnemy::~ArtilleryEnemy()
{
  for (int i = 0; i < MAX_BULLETS; i++)
  {
    delete bullets[i];
  }

  for (int i = 0; i < MAX_SHELLS; i++)
  {
    delete shells[i];
  }
}

bool ArtilleryEnemy::init(float x, float y)
{
  if (!texture->loadFromFile("Data/Images/kenney_pixelplatformer/Characters/character_0013.png"))
  {
    std::cout << "Enemy didn't load\n";
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

  for (int i = 0; i < MAX_SHELLS; i++)
  {
    shells[i]->init(0, 0);
  }

  return true;
}

void ArtilleryEnemy::fire(Entity *player)
{
  if (!bullets[active_bullets]->getVisible() && timer.getElapsedTime().asSeconds() >= 3)
  {
    bullets[active_bullets]->getSprite()->setPosition(sprite->getPosition().x + width / 2, sprite->getPosition().y + height / 2);
    bullets[active_bullets]->setVisible(true);
    bullets[active_bullets]->setMovement(Vector2(-3, 0));
    bullets[active_bullets]->getSprite()->rotate(180);
    timer.restart();

    if (active_bullets == MAX_BULLETS - 1) { active_bullets = 0; }
    else { active_bullets++; }
  }

  if (!shells[active_shell]->getVisible() && shell_timer.getElapsedTime().asSeconds() >= 5)
  {
    std::cout << "create shell" << std::endl;
    shells[active_shell]->prepareShell(Vector2(sprite->getPosition().x, sprite->getPosition().y),
                                        Vector2(player->getSprite()->getPosition().x, player->getSprite()->getPosition().y));
    shell_timer.restart();

    if (active_shell == MAX_SHELLS - 1) { active_shell = 0; }
    else { active_shell++; }
  }
}

void ArtilleryEnemy::update(float dt, Entity *player, GameObject* floor)
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
    }
  }

  for (int i = 0; i < MAX_SHELLS; i++)
  {
    if (shells[i]->getVisible())
    {
      shells[i]->update(dt);

      if (shells[i]->AABB(floor))
      {
        shells[i]->setVisible(false);
      }

      if (shells[i]->AABB(player))
      {
        player->changeHp(-1);
        shells[i]->setVisible(false);
      }
    }
  }
}

void ArtilleryEnemy::render()
{
  GameObject::render();

  for (int i = 0; i < MAX_BULLETS; i++)
  {
    if (bullets[i]->getVisible())
    {
      bullets[i]->render();
    }
  }

  for (int i = 0; i < MAX_SHELLS; i++)
  {
    if (shells[i]->getVisible())
    {
      shells[i]->render();
    }
  }
}
