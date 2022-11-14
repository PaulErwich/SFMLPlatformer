//
// Created by MLG Erwich on 01/04/2022.
//

#include "UI.h"
UI::UI(sf::RenderWindow& game_window, Player* plr) : window(game_window)
{
  player = plr;
  score = 0;
}

UI::~UI() = default;

bool UI::init()
{
  if (!heart_textures[0].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0044.png"))
  {
    std::cout << "Full heart didn't load\n";
    return false;
  }
  if (!heart_textures[1].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0045.png"))
  {
    std::cout << "Half heart didn't load\n";
    return false;
  }
  if (!heart_textures[2].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0046.png"))
  {
    std::cout << "Empty heart didn't load\n";
    return false;
  }

  for (int i = 0; i < 10; i++)
  {
    int tile = 170 + i;
    if (!score_textures[i].loadFromFile("Data/Images/kenney_pixelplatformer/Tiles/tile_0" + std::to_string(tile) + ".png"))
    {
      return false;
    }
  }
  float scale = 60.0f / 18.0f;
  for (int i = 0; i < SCORE_SPRITES; i++)
  {
    score_sprites[i].setTexture(score_textures[0]);
    score_sprites[i].setScale(scale, scale);
    score_sprites[i].setPosition(window.getSize().x - 70 - i * 50, 10);
  }

  for (int i = 0; i < MAX_HEARTS; i++)
  {
    hearts[i].setTexture(heart_textures[0]);
    hearts[i].scale(scale, scale);
    hearts[i].setPosition(10 + i * 60, 10);
  }
  return true;
}

void UI::reset()
{
  current_health = MAX_HEALTH;
  score = 0;
  healthUpdate();
  scoreUpdate();
}

int UI::getScore() const { return score; }
void UI::changeScore(int change) { score += change; }

void UI::update(float dt)
{
  current_health = player->getHp();
  healthUpdate();
  scoreUpdate();
}

void UI::render()
{
  sf::View basic;
  basic.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
  basic.setViewport(sf::FloatRect(0, 0, 1, 1));
  window.setView(basic);
  for (int i = 0; i < MAX_HEARTS; i++)
  {
    window.draw(hearts[i]);
  }

  for (int i = 0; i < SCORE_SPRITES; i++)
  {
    window.draw(score_sprites[i]);
  }

  window.setView(window.getDefaultView());
}

void UI::healthUpdate()
{
  if (current_health % 2 == 0)
  {
    switch(current_health)
    {
      case 10:
        hearts[4].setTexture(heart_textures[0]);
        hearts[3].setTexture(heart_textures[0]);
        hearts[2].setTexture(heart_textures[0]);
        hearts[1].setTexture(heart_textures[0]);
        hearts[0].setTexture(heart_textures[0]);
        break;
      case 8:
        hearts[4].setTexture(heart_textures[2]);
        hearts[3].setTexture(heart_textures[0]);
        hearts[2].setTexture(heart_textures[0]);
        hearts[1].setTexture(heart_textures[0]);
        hearts[0].setTexture(heart_textures[0]);
        break;
      case 6:
        hearts[4].setTexture(heart_textures[2]);
        hearts[3].setTexture(heart_textures[2]);
        hearts[2].setTexture(heart_textures[0]);
        hearts[1].setTexture(heart_textures[0]);
        hearts[0].setTexture(heart_textures[0]);
        break;
      case 4:
        hearts[4].setTexture(heart_textures[2]);
        hearts[3].setTexture(heart_textures[2]);
        hearts[2].setTexture(heart_textures[2]);
        hearts[1].setTexture(heart_textures[0]);
        hearts[0].setTexture(heart_textures[0]);
        break;
      case 2:
        hearts[4].setTexture(heart_textures[2]);
        hearts[3].setTexture(heart_textures[2]);
        hearts[2].setTexture(heart_textures[2]);
        hearts[1].setTexture(heart_textures[2]);
        hearts[0].setTexture(heart_textures[0]);
        break;
      case 0:
        hearts[4].setTexture(heart_textures[2]);
        hearts[3].setTexture(heart_textures[2]);
        hearts[2].setTexture(heart_textures[2]);
        hearts[1].setTexture(heart_textures[2]);
        hearts[0].setTexture(heart_textures[2]);
    }
  }
  else
  {
    switch(current_health)
    {
      case 9:
        hearts[4].setTexture(heart_textures[1]);
        hearts[3].setTexture(heart_textures[0]);
        hearts[2].setTexture(heart_textures[0]);
        hearts[1].setTexture(heart_textures[0]);
        hearts[0].setTexture(heart_textures[0]);
        break;
      case 7:
        hearts[4].setTexture(heart_textures[2]);
        hearts[3].setTexture(heart_textures[1]);
        hearts[2].setTexture(heart_textures[0]);
        hearts[1].setTexture(heart_textures[0]);
        hearts[0].setTexture(heart_textures[0]);
        break;
      case 5:
        hearts[4].setTexture(heart_textures[2]);
        hearts[3].setTexture(heart_textures[2]);
        hearts[2].setTexture(heart_textures[1]);
        hearts[1].setTexture(heart_textures[0]);
        hearts[0].setTexture(heart_textures[0]);
        break;
      case 3:
        hearts[4].setTexture(heart_textures[2]);
        hearts[3].setTexture(heart_textures[2]);
        hearts[2].setTexture(heart_textures[2]);
        hearts[1].setTexture(heart_textures[1]);
        hearts[0].setTexture(heart_textures[0]);
        break;
      case 1:
        hearts[4].setTexture(heart_textures[2]);
        hearts[3].setTexture(heart_textures[2]);
        hearts[2].setTexture(heart_textures[2]);
        hearts[1].setTexture(heart_textures[2]);
        hearts[0].setTexture(heart_textures[1]);
        break;
    }
  }
}

void UI::scoreUpdate()
{
  // Change textures of score depending on what the score is
  int temp = score;
  int s1, s2, s3, s4, s5;
  switch (temp)
  {
    case 1 ... 9:
      score_sprites[0].setTexture(score_textures[temp]);
      break;
    case 10 ... 99:
      s1 = temp % 10;
      temp /= 10;
      s2 = temp % 10;
      score_sprites[0].setTexture(score_textures[s1]);
      score_sprites[1].setTexture(score_textures[s2]);
      break;
    case 100 ... 999:
      s1 = temp % 10;
      temp /= 10;
      s2 = temp % 10;
      temp /= 10;
      s3 = temp % 10;

      score_sprites[0].setTexture(score_textures[s1]);
      score_sprites[1].setTexture(score_textures[s2]);
      score_sprites[2].setTexture(score_textures[s3]);
      break;
    case 1000 ... 9999:
      s1 = temp % 10;
      temp /= 10;
      s2 = temp % 10;
      temp /= 10;
      s3 = temp % 10;
      temp /= 10;
      s4 = temp % 10;

      score_sprites[0].setTexture(score_textures[s1]);
      score_sprites[1].setTexture(score_textures[s2]);
      score_sprites[2].setTexture(score_textures[s3]);
      score_sprites[3].setTexture(score_textures[s4]);
      break;
    case 10000 ... 99999:
      s1 = temp % 10;
      temp /= 10;
      s2 = temp % 10;
      temp /= 10;
      s3 = temp % 10;
      temp /= 10;
      s4 = temp % 10;
      temp /= 10;
      s5 = temp % 10;

      score_sprites[0].setTexture(score_textures[s1]);
      score_sprites[1].setTexture(score_textures[s2]);
      score_sprites[2].setTexture(score_textures[s3]);
      score_sprites[3].setTexture(score_textures[s4]);
      score_sprites[4].setTexture(score_textures[s5]);
      break;
    default:
      score_sprites[0].setTexture(score_textures[0]);
      score_sprites[1].setTexture(score_textures[0]);
      score_sprites[2].setTexture(score_textures[0]);
      score_sprites[3].setTexture(score_textures[0]);
      score_sprites[4].setTexture(score_textures[0]);
      break;
  }
}