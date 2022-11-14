//
// Created by MLG Erwich on 04/03/2022.
//

#include "GameObject.h"
GameObject::GameObject(sf::RenderWindow& game_window) : window(game_window)
{
  texture = new sf::Texture();
  sprite = new sf::Sprite();
  visible = true;
  width = 0;
  height = 0;
}

GameObject::~GameObject()
{
  delete texture;
  delete sprite;
}

bool GameObject::init() { return true; }

sf::Sprite* GameObject::getSprite() { return sprite; }

bool GameObject::getVisible() const { return visible; }

void GameObject::setVisible(bool visibility) { visible = visibility; }

void GameObject::update(float dt) {}

void GameObject::render() { window.draw(*sprite); }

void GameObject::setMin()
{
  min.x = sprite->getPosition().x;
  min.y = sprite->getPosition().y;
}

Vector2 GameObject::getMin() { return min; }

void GameObject::calculateMax()
{
  max.x = min.x + width;
  max.y = min.y + height;
}

Vector2 GameObject::getMax() { return max; }

float GameObject::getWidth() const { return width; }
float GameObject::getHeight() const { return height; }

void GameObject::setWidth(float _width) { width = _width; }
void GameObject::setHeight(float _height) { height = _height; }

Vector2 GameObject::getMovement() { return movement; }

void GameObject::setMovement(Vector2 move) { movement = move; }

bool GameObject::AABB(GameObject* collider) const
{
  if(max.x < collider->min.x || min.x > collider->max.x) return false;

  if(max.y < collider->min.y || min.y > collider->max.y) return false;


  return true;
}
