//
// Created by MLG Erwich on 01/04/2022.
//

#ifndef PLATFORMERSFML_UI_H
#define PLATFORMERSFML_UI_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../GameObjects/Entities/Player.h"
#include "Helper.h"
#include <string>

class UI
{
 public:
  UI(sf::RenderWindow& game_window, Player *plr);
  ~UI();

  bool init();
  void reset();

  int getScore() const;
  void changeScore(int change);

  void update(float dt);
  void render();

 private:
  sf::RenderWindow& window;

  Player *player;

  sf::Texture heart_textures[3];

  sf::Texture score_textures[10];

  static const int SCORE_SPRITES = 5;
  sf::Sprite score_sprites[SCORE_SPRITES];
  int score;

  static const int MAX_HEARTS = 5;
  sf::Sprite hearts[MAX_HEARTS];
  const int MAX_HEALTH = 10;
  int current_health = 10;



  void healthUpdate();
  void scoreUpdate();
};

#endif // PLATFORMERSFML_UI_H
