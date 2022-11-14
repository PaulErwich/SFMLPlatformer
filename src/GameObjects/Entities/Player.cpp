//
// Created by MLG Erwich on 08/03/2022.
//

#include "Player.h"
#include <cmath>

Player::Player(sf::RenderWindow& game_window) : Entity(game_window)
{
  on_ground = true;
}

bool Player::init()
{
  if (!texture->loadFromFile("Data/Images/AnimationStrips/Idle.png"))
  {
    std::cout << "player idle didn't load" << std::endl;
    return false;
  }
  idle_rect = sf::IntRect (0, 0, 24, 24);

  if (!running.loadFromFile("Data/Images/AnimationStrips/Runningmk3.png"))
  {
    std::cout << "player running didn't load" << std::endl;
    return false;
  }

  if (!gun_texture.loadFromFile("Data/Images/Extra/gun.png"))
  {
    std::cout << "gun didn't load" << std::endl;
    return false;
  }

  running_rect = sf::IntRect (0, 0, 24, 24);

  sprite->setTextureRect(idle_rect);
  sprite->setTexture(*texture);
  sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);
  sprite->setScale(-2, 2);

  width = sprite->getGlobalBounds().width;
  height = sprite->getGlobalBounds().height;

  sprite->setPosition(60 + width / 2, window.getSize().y - 180 - height / 2);
  setMin();
  calculateMax();

  gun.setTexture(gun_texture);
  gun.setOrigin(gun.getLocalBounds().width / 2, gun.getLocalBounds().height / 2);
  gun.setPosition(sprite->getPosition().x, sprite->getPosition().y);
  gun.rotate(45);
  gun.scale(1.5, 1.5);

  return true;
}

void Player::reset()
{
  current_hp = MAX_HP;

  sprite->setPosition(60 + width / 2, window.getSize().y - 180 - height / 2);
  setMin();
  calculateMax();
  movement = Vector2();
}

void Player::setOnGround(bool _on_ground) { on_ground = _on_ground; }

void Player::setMin()
{
  min.x = sprite->getPosition().x - width / 2;
  min.y = sprite->getPosition().y - height / 2;
}

void Player::calculateMax()
{
  max.x = sprite->getPosition().x + width / 2;
  max.y = sprite->getPosition().y + height / 2;
}

void Player::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::D)
  {
    movement.x = 1.5;
    sprite->setScale(-2, 2);
    animation = ANIM_STATE::RUNNING;
  }

  if (event.key.code == sf::Keyboard::A)
  {
    movement.x = -1.5;
    sprite->setScale(2, 2);
    animation = ANIM_STATE::RUNNING;
  }

  if (event.key.code == sf::Keyboard::Space && on_ground)
  {
    movement.y = -5;
    on_ground = false;
  }
}

void Player::keyReleased(sf::Event event)
{
  if (event.key.code == sf::Keyboard::D)
  {
    movement.x = 0;
    animation = ANIM_STATE::IDLE;
  }

  if (event.key.code == sf::Keyboard::A)
  {
    movement.x = 0;
    animation = ANIM_STATE::IDLE;
  }
}

void Player::update(float dt)
{
  movement.y += 5 * dt;

  animation_handler();

  if (on_ground)
  {
    movement.y = 0;
  }

  // Contingency movement
  // For when player is holding A/D then presses the other,
  // Then lets go of the other whilst still holding the original
  if (movement.x == 0)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
      movement.x = 1.5;
      sprite->setScale(-2, 2);
      animation = ANIM_STATE::RUNNING;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
      movement.x = -1.5;
      sprite->setScale(2, 2);
      animation = ANIM_STATE::RUNNING;
    }
  }

  // Rotate gun based on mouse position
  sf::Vector2f gun_pos = gun.getPosition();
  sf::Vector2i position = sf::Mouse::getPosition(window);
  gun_pos.x -= window.getView().getCenter().x - window.getDefaultView().getCenter().x;
  gun_pos.y -= window.getView().getCenter().y - window.getDefaultView().getCenter().y;

  float dx = gun_pos.x - position.x;
  float dy = gun_pos.y - position.y;

  float rotation = (std::atan2(dy, dx)) * 180 / M_PI;
  gun.setRotation(rotation + 180 + 45);

  if (gun.getRotation() < 315 && gun.getRotation() > 135)
  {
    gun.setScale(-1.5, 1.5);
    gun.rotate(90);
  }
  else
  {
    gun.setScale(1.5, 1.5);
  }

  sprite->move(movement.x * SPEED * dt, movement.y * SPEED * dt);
  gun.setPosition(sprite->getPosition().x, sprite->getPosition().y);
  setMin();
  calculateMax();
}

void Player::render()
{
  window.draw(*sprite);
  window.draw(gun);
}
