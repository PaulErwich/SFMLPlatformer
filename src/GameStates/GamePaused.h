//
// Created by MLG Erwich on 04/03/2022.
//

#ifndef PLATFORMERSFML_GAMEPAUSED_H
#define PLATFORMERSFML_GAMEPAUSED_H

#include "GameStateBase.h"
#include "GamePlay.h"

class GamePaused : public GameStateBase
{
 public:
  GamePaused(STATE stateId, sf::RenderWindow& gameWindow, sf::Font& gameFont);
  ~GamePaused();
  bool init() override;

  void reset() override;

  void setGamePlay(GamePlay &game);

  bool getPaused() const;

  void input(sf::Event event) override;
  STATE update(float dt) override;
  void render() override;

 private:
  GamePlay* game_play;
  sf::Text text_paused;
  sf::Text text_unpause;

  bool unpause;
};

#endif // PLATFORMERSFML_GAMEPAUSED_H
