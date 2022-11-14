//
// Created by p2-erwich on 08/04/2022.
//

#ifndef PLATFORMERSFML_ARTILLERYENEMY_H
#define PLATFORMERSFML_ARTILLERYENEMY_H

#include "../Projectiles/Projectile.h"
#include "../Projectiles/Shell.h"
#include "Entity.h"

class ArtilleryEnemy : public Entity
{
 public:
  ArtilleryEnemy(sf::RenderWindow& game_window);
  ~ArtilleryEnemy();

  bool init(float x, float y) override;

  void fire(Entity* player);

  void update(float dt, Entity *player, GameObject* floor) override;
  void render() override;

 private:
  sf::Clock timer;
  static const int MAX_BULLETS = 5;
  int active_bullets;
  Projectile *bullets[MAX_BULLETS];

  sf::Clock shell_timer;
  static const int MAX_SHELLS = 5;
  int active_shell;
  Shell *shells[MAX_SHELLS];
};

#endif // PLATFORMERSFML_ARTILLERYENEMY_H
