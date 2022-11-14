//
// Created by MLG Erwich on 04/03/2022.
//

#ifndef PLATFORMERSFML_LEVEL_H
#define PLATFORMERSFML_LEVEL_H

#include "../../Extra/UI.h"
#include "../../GameStates/GameStateBase.h"
#include "../../PhysicsEngine/PhysicsCollisions.h"
#include "../../PhysicsEngine/PhysicsStructs.h"
#include "../Block.h"
#include "../Collectable.h"
#include "../Entities/ArtilleryEnemy.h"
#include "../Entities/HomingEnemy.h"
#include "../Entities/NormalEnemy.h"
#include "../Entities/Player.h"
#include "../Flag.h"
#include "../Projectiles/Projectile.h"
#include "../Projectiles/Shell.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Level
{
 public:
  Level(sf::RenderWindow& game_window);
  ~Level();

  virtual bool init(Player* _player, UI* _ui);
  static bool loadAssets();

  void reset();

  static int getWidth();
  //Body* getFloorBody() const;
  GameObject* getFloor() const;

  void input(sf::Event event);
  STATE update(float dt);
  void render();


  // Static textures, so I don't need
  // To store them in each copy of Level
  static sf::Texture single_block_textures[3];
  static sf::Texture dirt_block_texture;

  static sf::Texture dirt_corner_textures[4];
  static sf::Texture single_dirt_textures[2];
  static sf::Texture dirt_mid_textures[3];
  static sf::Texture dirt_bottom_textures[3];

  static sf::Texture single_top_block_textures[3];

  static sf::Texture grass_top_textures[3];
  static sf::Texture sand_top_textures[3];
  static sf::Texture snow_top_textures[3];

  static sf::Texture grass_platform_textures[3];
  static sf::Texture sand_platform_textures[3];
  static sf::Texture snow_platform_textures[3];

  static sf::Texture gem_texture;

 protected:
  sf::RenderWindow& window;

  static const int WIDTH = 48;
  static const int HEIGHT = 18;
  static const int BLOCK_SZ = 60;

  Block *world[WIDTH * HEIGHT]; // Textures

  static const int GEM_NUMBER = 40;
  int current_gems;
  Collectable *gem[GEM_NUMBER];

  GameObject* floor;
  //Body* floor_body;

  // Non textured GameObjects used as an
  // Overlay of tiles for collision detection
  static const int PLAT_NUM = 18;
  int current_platforms;
  GameObject* platforms[PLAT_NUM];

  // Bullets fired by the player
  static const int MAX_BULLETS = 30;
  int active_bullets;
  sf::Clock fire_timer;
  Projectile *bullets[MAX_BULLETS];

  // Pointer to player created in GamePlay class
  Player* player;
  UI* ui;

  static const int MAX_ENEMIES = 5;
  Entity* enemies[MAX_ENEMIES];

  // Flag for ending the level
  Flag *flag;

  bool init_setup_bullets();
  virtual void init_setup_blocks();
  virtual void init_setup_platforms();
  virtual void init_setup_enemies();

  void textureRow(int platform_x, int platform_y, int width, sf::Texture textures[]);

  void generatePlatform(int platform_x, int platform_y, int width, sf::Texture textures[], bool gems);

  void generateBlock(int platform_x, int platform_y, int texture_num);

  void generateBox(int platform_x, int platform_y, int width, int height,
                   sf::Texture top_texture[], bool on_floor);

  void generateStairs(int stair_x, int stair_y, int width, int height,
                      sf::Texture &textures, int texture_num, bool side);

  void generateGems(int platform_x, int platform_y, int width);



};

#endif // PLATFORMERSFML_LEVEL_H
