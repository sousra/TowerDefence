#pragma once
#include <SFML/Graphics.hpp>

class Entity 
{
public:
	Entity(float x, float y, const sf::Image& image);

	bool is_alive() const noexcept;

	const sf::Sprite& get_sprite() const noexcept;
	sf::Vector2f get_pos() const noexcept;
	int get_damage() const noexcept;
	float get_width() const noexcept;
	float get_height() const noexcept;

protected:
	float _x, _y, _width, _height, _first_width, _first_height;
	int _damage;
	bool _alive;
	sf::Texture _texture;
	sf::Sprite _sprite;
};