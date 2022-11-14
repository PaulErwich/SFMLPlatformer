//
// Created by MLG Erwich on 04/03/2022.
//

#include "GamePlay.h"
GamePlay::GamePlay(
  STATE stateId, sf::RenderWindow& gameWindow, sf::Font& gameFont) :
  GameStateBase(stateId, gameWindow, gameFont)
{
  player = new Player(window);

  /*
  test_square = new Block(window);
  test_square2 = new Block(window);

  test_body = nullptr;
  test_body2 = nullptr;
   */

  ui = new UI(window, player);

  for (int i = 0; i < MAX_LEVELS; i += MAX_LEVELS)
  {
    levels[i] = new LevelOne(window);
    levels[i + 1] = new LevelTwo(window);
    levels[i + 2] = new LevelThree(window);
  }
  current_level = levels[1];
}

GamePlay::~GamePlay()
{
  /*
  delete test_square;
  delete test_square2;

  delete test_body;
  delete test_body2;
   */

  delete player;
  delete ui;

  for (int i = 0; i < MAX_LEVELS; i++)
  {
    delete levels[i];
  }
}

bool GamePlay::init()
{
  player->init();

  if (!Level::loadAssets()) return false;

  /*
  player_body = new Body(player, 0.1, 0.5);
  player_body->mass_data = MassData(1);

  test_square->init(test_texture, window.getSize().x / 2 + 20, 200);
  test_square2->init(test_texture, window.getSize().x / 2, window.getSize().y / 2);

  test_body = new Body(test_square, 0.3, 0.2);
  test_body2 = new Body(test_square2, 1.2, 0.05);

  test_body->force = Vector2(0, 50);

  test_body2->mass_data = MassData(0);

  //physics_engine.setObject(test_body, 0);
  physics_engine.setObject(test_body2, 1);
  physics_engine.setObject(player_body, 0);
  physics_engine.setObject(level->getFloorBody(), 2);
  */

  if (!ui->init()) return false;

  int count = 0;
  for (int i = 0; i < MAX_LEVELS; i++)
  {
    if (!levels[i]->init(player, ui))
    {
      count++;
    }
  }

  if (count == MAX_LEVELS)
  {
    return false;
  }

  return true;
}

void GamePlay::reset()
{
  player->reset();
  ui->reset();
  paused = false;

  for (int i = 0; i < MAX_LEVELS; i++)
  {
    levels[i]->reset();
  }
}

int GamePlay::getScore() { return ui->getScore(); }
void GamePlay::setPause(bool pause) { paused = pause; }

void GamePlay::setLevel(int level_num)
{
  current_level = levels[level_num - 1];
}

void GamePlay::keyPressed(sf::Event event)
{
  player->keyPressed(event);

  if (event.key.code == sf::Keyboard::Enter)
  {
    player->changeHp(-1);
  }

  if (event.key.code == sf::Keyboard::Escape)
  {
    paused = true;
  }
}

void GamePlay::keyReleased(sf::Event event)
{
  player->keyReleased(event);
}

void GamePlay::input(sf::Event event)
{
  current_level->input(event);

  if (event.type == sf::Event::KeyPressed)
  {
    keyPressed(event);
  }

  if (event.type == sf::Event::KeyReleased)
  {
    keyReleased(event);
  }
}

STATE GamePlay::update(float dt)
{
  //physics_engine.update(dt);

  sf::Vector2f player_pos(player->getSprite()->getPosition().x, window.getSize().y / 2);
  if (player_pos.x < window.getSize().x / 2)
  {
    player_pos.x = window.getSize().x / 2;
  }
  else if (player_pos.x + window.getSize().x / 2 > current_level->getWidth() * 60)
  {
    player_pos.x = current_level->getWidth() * 60 - window.getSize().x / 2;
  }
  new_view.setCenter(player_pos);
  new_view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
  ui->update(dt);

  if (paused)
  {
    return STATE::GAME_PAUSED;
  }

  return current_level->update(dt);
}

void GamePlay::render()
{
  ui->render();
  window.setView(new_view);
  current_level->render();

  //physics_engine.render();
}
