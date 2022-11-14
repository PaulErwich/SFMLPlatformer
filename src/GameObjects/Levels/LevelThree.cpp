//
// Created by MLG Erwich on 28/04/2022.
//

#include "LevelThree.h"
LevelThree::LevelThree(sf::RenderWindow& game_window) : Level(game_window)
{

}

bool LevelThree::init(Player* _player, UI* _ui)
{
  init_setup_blocks();
  init_setup_platforms();
  init_setup_enemies();

  if (!flag->init(44 * BLOCK_SZ, 5 * BLOCK_SZ)) return false;

  return Level::init(_player, _ui);
}

void LevelThree::init_setup_blocks()
{
  int block_width = BLOCK_SZ;

  for (int i = 0; i < WIDTH; i++)
  {
    for (int j = 0; j < HEIGHT; j += 18)
    {
      world[i * HEIGHT + (j + 15)]->init(
        sand_top_textures[1], 0 + i * block_width, 0 + (j + 15) * block_width);
      world[i * HEIGHT + (j + 16)]->init(
        dirt_block_texture, 0 + i * block_width, 0 + (j + 16) * block_width);
      world[i * HEIGHT + (j + 17)]->init(
        dirt_block_texture, 0 + i * block_width, 0 + (j + 17) * block_width);
    }
  }
}

void LevelThree::init_setup_platforms()
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
    generatePlatform(platform_x[i], platform_y[i], platform_width[i], sand_platform_textures,gems[i]);
  }

  generateBlock(10, 3, 1);
  generateBlock(17, 3, 1);

  generateBox(38, 11, 3, 4, sand_top_textures, true);

  // Creates even size staircases e.g. if 5 wide, needs to be 5 high
  generateStairs(26, 12, 3, 3, sand_top_textures[0], 1, true);
  generateStairs(32, 12, 3, 3, sand_top_textures[2], 1, false);
}

void LevelThree::init_setup_enemies()
{
  int enemy_x[MAX_ENEMIES] = {10, 11, 12, 13, 14};
  int enemy_y[MAX_ENEMIES] = {11, 10, 1, 1, 14};

  for (int i = 0; i < MAX_ENEMIES; i++)
  {
    enemies[i]->init(enemy_x[i] * BLOCK_SZ, enemy_y[i] * BLOCK_SZ);
  }
}
