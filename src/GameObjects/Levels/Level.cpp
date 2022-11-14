//
// Created by MLG Erwich on 04/03/2022.
//

#include "Level.h"

sf::Texture Level::single_block_textures[3];
sf::Texture Level::dirt_block_texture;
sf::Texture Level::dirt_corner_textures[4];
sf::Texture Level::single_dirt_textures[2];
sf::Texture Level::dirt_mid_textures[3];
sf::Texture Level::dirt_bottom_textures[3];
sf::Texture Level::single_top_block_textures[3];
sf::Texture Level::grass_top_textures[3];
sf::Texture Level::sand_top_textures[3];
sf::Texture Level::snow_top_textures[3];
sf::Texture Level::grass_platform_textures[3];
sf::Texture Level::sand_platform_textures[3];
sf::Texture Level::snow_platform_textures[3];
sf::Texture Level::gem_texture;

Level::Level(sf::RenderWindow& game_window) : window(game_window)
{
  for (int i = 0; i < WIDTH * HEIGHT; i++)
  {
    world[i] = new Block(window);
  }

  floor = new GameObject(window);
  //floor_body = new Body(floor, 0, 0);

  for (int i = 0; i < GEM_NUMBER; i++)
  {
    gem[i] = new Collectable(window);
  }

  for (int i = 0; i < PLAT_NUM; i++)
  {
    platforms[i] = new GameObject(window);
  }

  player = nullptr;

  active_bullets = 0;
  for (int i = 0; i < MAX_BULLETS; i++)
  {
    bullets[i] = new Projectile(window);
  }

  for (int i = 0; i < MAX_ENEMIES; i += MAX_ENEMIES)
  {
    enemies[i] = new ArtilleryEnemy(window);
    enemies[i + 1] = new NormalEnemy(window);
    enemies[i + 2] = new HomingEnemy(window);
    enemies[i + 3] = new HomingEnemy(window);
    enemies[i + 4] = new ArtilleryEnemy(window);
  }

  current_platforms = 0;
  current_gems = 0;

  flag = new Flag(window);
}

Level::~Level()
{
  for (int i = 0; i < WIDTH * HEIGHT; i++)
  {
    delete world[i];
  }

  delete floor;
  //delete floor_body;

  for (int i = 0; i < GEM_NUMBER; i++)
  {
    delete gem[i];
  }

  for (int i = 0; i < PLAT_NUM; i++)
  {
    delete platforms[i];
  }

  for (int i = 0; i < MAX_BULLETS; i++)
  {
    delete bullets[i];
  }

  for (int i = 0; i < MAX_ENEMIES; i++)
  {
    delete enemies[i];
  }

  delete flag;
}

bool Level::init(Player* _player, UI* _ui)
{
  player = _player;
  ui = _ui;

  return init_setup_bullets();
}

bool Level::init_setup_bullets()
{
  bool bullet_init = true;
  for (int i = 0; i < MAX_BULLETS; i++)
  {
    if (bullets[i]->init(0, 0)) bullet_init = true;
    else bullet_init = false;
  }

  if (!bullet_init)
  {
    return false;
  }
  return true;
}

void Level::init_setup_blocks()
{
}

void Level::init_setup_platforms()
{
}

void Level::init_setup_enemies()
{
}

bool Level::loadAssets()
{
  if (!single_block_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0000.png")) return false;
  if (!single_block_textures[1].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0040.png")) return false;
  if (!single_block_textures[2].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0080.png")) return false;

  if (!dirt_block_texture.loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0122.png")) return false;

  if (!dirt_corner_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0004.png")) return false;
  if (!dirt_corner_textures[1].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0005.png")) return false;
  if (!dirt_corner_textures[2].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0024.png")) return false;
  if (!dirt_corner_textures[3].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0025.png")) return false;

  if (!single_dirt_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0120.png")) return false;
  if (!single_dirt_textures[1].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0140.png")) return false;

  if (!dirt_mid_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0121.png")) return false;
  dirt_mid_textures[1] = dirt_block_texture;
  if (!dirt_mid_textures[2].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0123.png")) return false;

  if (!dirt_bottom_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0141.png")) return false;
  if (!dirt_bottom_textures[1].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0142.png")) return false;
  if (!dirt_bottom_textures[2].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0143.png")) return false;

  if (!single_top_block_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0020.png")) return false;
  if (!single_top_block_textures[1].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0060.png")) return false;
  if (!single_top_block_textures[2].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0100.png")) return false;

  if (!grass_top_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0021.png")) return false;
  if (!grass_top_textures[1].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0022.png")) return false;
  if (!grass_top_textures[2].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0023.png")) return false;

  if (!sand_top_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0061.png")) return false;
  if (!sand_top_textures[1].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0062.png")) return false;
  if (!sand_top_textures[2].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0063.png")) return false;

  if (!snow_top_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0101.png")) return false;
  if (!snow_top_textures[1].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0102.png")) return false;
  if (!snow_top_textures[2].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0103.png")) return false;

  if (!grass_platform_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0001.png")) return false;
  if (!grass_platform_textures[1].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0002.png")) return false;
  if (!grass_platform_textures[2].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0003.png")) return false;

  if (!sand_platform_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0041.png")) return false;
  if (!sand_platform_textures[1].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0042.png")) return false;
  if (!sand_platform_textures[2].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0043.png")) return false;

  if (!snow_platform_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0081.png")) return false;
  if (!snow_platform_textures[1].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0082.png")) return false;
  if (!snow_platform_textures[2].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0083.png")) return false;

  if (!gem_texture.loadFromFile("Data/Images/Extra/oryx_16bit_fantasy_items_55.png")) return false;

  return true;
}

void Level::reset()
{
  for (int i = 0; i < GEM_NUMBER; i++)
  {
    gem[i]->setVisible(true);
  }

  for (int i = 0; i < MAX_ENEMIES; i += MAX_ENEMIES)
  {
    enemies[i] = new ArtilleryEnemy(window);
    enemies[i + 1] = new NormalEnemy(window);
    enemies[i + 2] = new HomingEnemy(window);
    enemies[i + 3] = new HomingEnemy(window);
    enemies[i + 4] = new ArtilleryEnemy(window);
  }

  init_setup_enemies();
}

int Level::getWidth() { return WIDTH; }

//Body* Level::getFloorBody() const { return floor_body; }
GameObject* Level::getFloor() const { return floor; }

void Level::textureRow(int platform_x, int platform_y, int width, sf::Texture* textures)
{
  int start = platform_x * HEIGHT + platform_y;
  int end = (platform_x + width - 1) * HEIGHT + platform_y;

  for (int i = 0; i < width; i++)
  {
    if (i == 0)
    {
      int pos = (platform_x + i) * platform_y;
      world[start]->init(
        textures[0], (pos / platform_y) * BLOCK_SZ, (pos / (platform_x)) * BLOCK_SZ);
    }
    else if (i == width - 1)
    {
      int pos = (platform_x + i) * platform_y;
      world[end]->init(
        textures[2], (pos / platform_y) * BLOCK_SZ, (pos / (platform_x + i)) * BLOCK_SZ);
    }
    else
    {
      int world_pos = (platform_x + i) * HEIGHT + platform_y;
      int pos = (platform_x + i) * platform_y;
      world[world_pos]->init(
        textures[1], (pos / platform_y) * BLOCK_SZ, (pos / (platform_x + i)) * BLOCK_SZ);
    }
  }
}

void Level::generatePlatform(int platform_x, int platform_y, int width, sf::Texture *textures, bool gems)
{
  // Create a platform on screen based on the inputs given
  // Function is designed for 1 high, any width platforms

  textureRow(platform_x, platform_y, width, textures);
  if (gems)
  {
    generateGems(platform_x, platform_y, width);
  }

  platforms[current_platforms]->getSprite()->setPosition(
    world[platform_x * HEIGHT + platform_y]->getSprite()->getPosition());
  platforms[current_platforms]->setWidth(width * BLOCK_SZ);
  platforms[current_platforms]->setHeight(BLOCK_SZ);
  platforms[current_platforms]->setMin();
  platforms[current_platforms]->calculateMax();

  current_platforms++;
}

void Level::generateBlock(int platform_x, int platform_y, int texture_num)
{
  int world_pos = platform_x * HEIGHT + platform_y;
  world[world_pos]->init(single_block_textures[texture_num],
                                         platform_x * BLOCK_SZ, platform_y * BLOCK_SZ);

  platforms[current_platforms]->getSprite()->setPosition(world[world_pos]->getSprite()->getPosition());
  platforms[current_platforms]->setWidth(BLOCK_SZ);
  platforms[current_platforms]->setHeight(BLOCK_SZ);
  platforms[current_platforms]->setMin();
  platforms[current_platforms]->calculateMax();

  current_platforms++;
}

void Level::generateBox(int platform_x, int platform_y, int width, int height, sf::Texture *top_texture, bool on_floor)
{
  for (int i = 0; i < height; i++)
  {
    if (i == 0)
    {
      textureRow(platform_x, platform_y, width, top_texture);
    }
    else if (i == height - 1)
    {
      if (!on_floor)
      {
        textureRow(platform_x, platform_y + i, width, dirt_bottom_textures);
      }
      else
      {
        textureRow(platform_x, platform_y + i, width, dirt_mid_textures);
      }
    }
    else
    {
      textureRow(platform_x, platform_y + i, width, dirt_mid_textures);
    }
  }

  int world_pos = platform_x * HEIGHT + platform_y;
  platforms[current_platforms]->getSprite()->setPosition(world[world_pos]->getSprite()->getPosition());
  platforms[current_platforms]->setWidth(width * BLOCK_SZ);
  platforms[current_platforms]->setHeight(height * BLOCK_SZ);
  platforms[current_platforms]->setMin();
  platforms[current_platforms]->calculateMax();

  current_platforms++;
}

void Level::generateStairs(int stair_x, int stair_y, int width, int height,
                           sf::Texture &textures, int texture_num, bool side)
{
  // side shows orientation
  // true means up towards to right
  // false means down towards bottom left
  if (side)
  {
    world[(stair_x + width - 1) * HEIGHT + stair_y]->init(
      single_top_block_textures[texture_num], (stair_x + width - 1) *
                                                BLOCK_SZ, stair_y * BLOCK_SZ);

    for (int i = 1; i < height; i++)
    {
      textureRow(stair_x + width - i - 1,
                 stair_y + i, i + 1,
                 new sf::Texture[3]{textures, dirt_mid_textures[1], dirt_mid_textures[2]});
    }

    for (int i = 0; i < width; i++)
    {
      int world_pos = (stair_x + width - i - 1) * HEIGHT + (stair_y + i);
      platforms[current_platforms]->getSprite()->setPosition(world[world_pos]->getSprite()->getPosition());
      platforms[current_platforms]->setWidth(BLOCK_SZ);
      platforms[current_platforms]->setHeight((height - i) * BLOCK_SZ);
      platforms[current_platforms]->setMin();
      platforms[current_platforms]->calculateMax();
      current_platforms++;
    }

  }
  else
  {
    world[stair_x * HEIGHT + stair_y]->init(single_top_block_textures[texture_num],
                                            stair_x * BLOCK_SZ, stair_y * BLOCK_SZ);

    for (int i = 1; i < height; i++)
    {
      textureRow(stair_x, stair_y + i, i + 1,
                 new sf::Texture[3]{dirt_mid_textures[0], dirt_mid_textures[1], textures});
    }

    for (int i = 0; i < width; i++)
    {
      int world_pos = (stair_x + i) * HEIGHT + (stair_y + i);
      platforms[current_platforms]->getSprite()->setPosition(world[world_pos]->getSprite()->getPosition());
      platforms[current_platforms]->setWidth(BLOCK_SZ);
      platforms[current_platforms]->setHeight((height - i) * BLOCK_SZ);
      platforms[current_platforms]->setMin();
      platforms[current_platforms]->calculateMax();
      current_platforms++;
    }
  }
}

void Level::generateGems(int platform_x, int platform_y, int width)
{
  for (int i = 0; i < width; i++)
  {
    gem[current_gems]->init(gem_texture, (platform_x + i) * BLOCK_SZ, (platform_y - 1) * BLOCK_SZ);
    current_gems++;
  }
}

void Level::input(sf::Event event)
{
  if (event.type == sf::Event::KeyPressed)
  {

  }

  if (event.type == sf::Event::MouseButtonPressed)
  {
    if (event.mouseButton.button == sf::Mouse::Left && fire_timer.getElapsedTime().asSeconds() >= 1)
    {
      std::cout << "create bullet\n";
      if (!bullets[active_bullets]->getVisible())
      {
        bullets[active_bullets]->getSprite()->setPosition(player->getSprite()->getPosition().x, player->getSprite()->getPosition().y);
        bullets[active_bullets]->setVisible(true);
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        mouse_pos.x += window.getView().getCenter().x - window.getDefaultView().getCenter().x;
        mouse_pos.y += window.getView().getCenter().y - window.getDefaultView().getCenter().y;
        sf::Vector2f mouse_convert(mouse_pos.x, mouse_pos.y);

        bullets[active_bullets]->prepareBullet(player->getSprite()->getPosition(), mouse_convert);

        fire_timer.restart();

        if (active_bullets == MAX_BULLETS - 1) { active_bullets = 0; }
        else { active_bullets++; }
      }
    }
  }
}

STATE Level::update(float dt)
{
  player->update(dt);

  player->setOnGround(false);

  if (player->AABB(floor))
  {
    player->setOnGround(true);
    player->getSprite()->setPosition(player->getSprite()->getPosition().x, floor->getMin().y - player->getHeight() / 2);
  }

  Object_Manifold collision(player, nullptr);

  for (int i = 0; i < PLAT_NUM; i++)
  {
    if (platforms[i] != nullptr)
    {
      collision.B = platforms[i];

      if (AABBvsAABB_MK3(&collision))
      {
        std::cout << "hit\n";
        if (collision.normal.x != 0)
        {
          if (collision.normal.x == 1)
          {
            player->getSprite()->setPosition(collision.B->getMin().x - player->getWidth() / 2, player->getSprite()->getPosition().y);
          }
          else if (collision.normal.x == -1)
          {
            player->getSprite()->setPosition(collision.B->getMax().x + player->getWidth() / 2, player->getSprite()->getPosition().y);
          }
        }
        else if (collision.normal.y != 0)
        {
          if (collision.normal.y == 1)
          {
            player->setOnGround(true);
          }
          else if (collision.normal.y == -1)
          {
            player->setMovement(Vector2(player->getMovement().x, 2));
          }
        }
      }
    }
  }

  for (int i = 0; i < MAX_BULLETS; i++)
  {
    if (bullets[i]->getVisible())
    {
      bullets[i]->update(dt);

      for (int j = 0; j < PLAT_NUM; j++)
      {
        if (platforms[j] != nullptr)
        {
          if (bullets[i]->AABB(platforms[j]))
          {
            bullets[i]->setVisible(false);
          }
        }
      }

      if (bullets[i]->AABB(floor))
      {
        bullets[i]->setVisible(false);
      }

      for (int j = 0; j < MAX_ENEMIES; j++)
      {
        if (bullets[i]->AABB(enemies[j]))
        {
          enemies[j]->setVisible(false);
          bullets[i]->setVisible(false);
          ui->changeScore(25);
        }
      }
    }
  }

  for (int i = 0; i < GEM_NUMBER; i++)
  {
    if (gem[i]->getVisible())
    {
      gem[i]->update(dt);
      if (player->AABB(gem[i]))
      {
        gem[i]->setVisible(false);
        ui->changeScore(10);
      }
    }

  }

  for (int i = 0; i < MAX_ENEMIES; i++)
  {
    if (enemies[i]->getVisible())
    {
      enemies[i]->update(dt, player, floor);
    }
  }

  // Can also win if you collect all the gems
  int count = 0;
  for (int i = 0; i < GEM_NUMBER; i++)
  {
    if (!gem[i]->getVisible())
    {
      count++;
    }
  }
  if (count == GEM_NUMBER)
  {
    return STATE::GAME_WIN;
  }
  
  if (player->getHp() <= 0)
  {
    return STATE::GAME_OVER;
  }

  if (player->AABB(flag))
  {
    return STATE::GAME_WIN;
  }

  return STATE::GAME_PLAY;
}

void Level::render()
{
  for (int i = 0; i < GEM_NUMBER; i++)
  {
    if (gem[i]->getVisible())
    {
      gem[i]->render();
    }
  }

  for (int i = 0; i < WIDTH * HEIGHT; i++)
  {
    world[i]->render();
  }

  for (int i = 0; i < MAX_BULLETS; i++)
  {
    if (bullets[i]->getVisible())
    {
      bullets[i]->render();
    }
  }

  flag->render();

  player->render();

  for (int i = 0; i < MAX_ENEMIES; i++)
  {
    if (enemies[i]->getVisible())
    {
      enemies[i]->render();
    }
  }
}
