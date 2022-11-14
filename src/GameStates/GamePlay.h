//
// Created by MLG Erwich on 04/03/2022.
//

#ifndef PLATFORMERSFML_GAMEPLAY_H
#define PLATFORMERSFML_GAMEPLAY_H

#include "../GameObjects/Entities/Player.h"
#include "../GameObjects/Levels/Level.h"
#include "../GameObjects/Levels/LevelOne.h"
#include "../GameObjects/Levels/LevelTwo.h"
#include "../GameObjects/Levels/LevelThree.h"
#include "../PhysicsEngine/PhysicsEngine.h"
#include "GameStateBase.h"

class GamePlay : public GameStateBase
{
 public:
  GamePlay(STATE stateId, sf::RenderWindow& gameWindow, sf::Font& gameFont);
  ~GamePlay();

  bool init() override;

  void reset() override;

  int getScore();

  void setPause(bool pause);

  void setLevel(int level_num);

  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  void input(sf::Event event) override;
  STATE update(float dt) override;
  void render() override;

 private:
  Player *player;

  // Physics testing, wasn't used in final version as
  // couldn't get it to work properly / need to look into / test it more
  //Body *player_body;
  //Block *test_square;
  //Body *test_body;
  //Block *test_square2;
  //Body *test_body2;
  // Should just be the textures for blocks
  static const int MAX_LEVELS = 3;
  Level* current_level;
  Level* levels[MAX_LEVELS];
  sf::View new_view;

  bool paused;

  //PhysicsEngine physics_engine;
  UI* ui;
};

#endif // PLATFORMERSFML_GAMEPLAY_H
