#include "Entity.h"

Entity::Entity(float x, float y, const sf::Image& image)
	: _x(x), _y(y), _alive(true)
{
	_texture.loadFromImage(image);
	_sprite.setTexture(_texture);
}

bool Entity::is_alive() const noexcept
{
	return _alive;
}

const sf::Sprite& Entity::get_sprite() const noexcept
{
	return _sprite;
}

sf::Vector2f Entity::get_pos() const noexcept
{
	return sf::Vector2f(_x, _y);
}

int Entity::get_damage() const noexcept
{
	return _damage;
}

float Entity::get_width() const noexcept
{
	return _width;
}

float Entity::get_height() const noexcept
{
	return _height;
}