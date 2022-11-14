//
// Created by MLG Erwich on 28/04/2022.
//

#include "LevelTwo.h"

LevelTwo::LevelTwo(sf::RenderWindow& game_window) : Level(game_window) {}

bool LevelTwo::init(Player* _player, UI* _ui)
{
  init_setup_blocks();
  init_setup_platforms();
  init_setup_enemies();

  if (!flag->init(44 * BLOCK_SZ, 5 * BLOCK_SZ)) return false;

  return Level::init(_player, _ui);
}

void LevelTwo::init_setup_blocks()
{
  int block_width = BLOCK_SZ;

  for (int i = 0; i < WIDTH; i++)
  {
    for (int j = 0; j < HEIGHT; j += 18)
    {
      world[i * HEIGHT + (j + 15)]->init(
        snow_top_textures[1], 0 + i * block_width, 0 + (j + 15) * block_width);
      world[i * HEIGHT + (j + 16)]->init(
        dirt_block_texture, 0 + i * block_width, 0 + (j + 16) * block_width);
      world[i * HEIGHT + (j + 17)]->init(
        dirt_block_texture, 0 + i * block_width, 0 + (j + 17) * block_width);
    }
  }
}

void LevelTwo::init_setup_platforms()
{
  floor->getSprite()->setPosition(world[15]->getSprite()->getPosition());
  floor->setWidth(WIDTH * BLOCK_SZ);
  floor->setHeight(3 * BLOCK_SZ);
  floor->setMin();
  floor->calculateMax();

  int platform_x[8] = {5, 12, 20, 9, 17, 13, 29, 42};
  int platform_y[8] = {12, 12, 12, 9, 9, 5, 8, 7};
  int platform_width[8] = {3, 4, 3, 2, 2, 2, 3, 5};
  bool gems[8] = {true, false, false, true, true, true, true, false};

  for (int i = 0; i < 8; i++)
  {
    generatePlatform(platform_x[i], platform_y[i], platform_width[i], snow_platform_textures,gems[i]);
  }

  generateBlock(10, 3, 2);
  generateBlock(17, 3, 2);

  generateBox(38, 11, 3, 4, snow_top_textures, true);

  // Creates even size staircases e.g. if 5 wide, needs to be 5 high
  generateStairs(26, 12, 3, 3, snow_top_textures[0], 2, true);
  generateStairs(32, 12, 3, 3, snow_top_textures[2], 2, false);
}

void LevelTwo::init_setup_enemies()
{
  int enemy_x[MAX_ENEMIES] = {21, 39, 10, 17, 30};
  int enemy_y[MAX_ENEMIES] = {11, 10, 1, 1, 14};

  for (int i = 0; i < MAX_ENEMIES; i++)
  {
    enemies[i]->init(enemy_x[i] * BLOCK_SZ, enemy_y[i] * BLOCK_SZ);
  }
}