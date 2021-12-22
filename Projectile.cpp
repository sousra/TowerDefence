#include "Projectile.h"

Projectile::Projectile(float x, float y, sf::Image& image, ProjectileType type, sf::Vector2f target)
	: Entity(x, y, image), _type(type), _target(target)
{
	_sprite.setPosition(_x, _y);
	_speed = 0.1;
	if (_type == ProjectileType::BigRocket) {
		_damage = 130;
		_sprite.setTextureRect(sf::IntRect(0, 0, 19, 40));
		_width = 19;
		_height = 40;
	}
	else if (_type == ProjectileType::DoubleRocket) {
		_damage = 260;
		_sprite.setTextureRect(sf::IntRect(0, 40, 27, 35));
		_width = 27;
		_height = 35;
	}
	else if (_type == ProjectileType::CannonBall) {
		_damage = 40;
		_sprite.setTextureRect(sf::IntRect(0, 75, 16, 16));
		_width = 16;
		_height = 16;
	}
	else if (_type == ProjectileType::DoubleCannonBall) {
		_damage = 80;
		_sprite.setTextureRect(sf::IntRect(0, 91, 33, 16));
		_width = 33;
		_height = 16;
	}
}

void Projectile::update(float time, std::list<Enemy*>& enemies)
{
	for (auto it = enemies.begin(); it != enemies.end(); ++it) {
		if ((*it)->get_sprite().getGlobalBounds().intersects(_sprite.getGlobalBounds())) {
			(*it)->reduce_health(_damage);
			_alive = false;
			return;
		}
	}
	float distance = sqrt((_target.x - (_x + _width / 2)) * (_target.x - (_x + _width / 2)) + (_target.y - (_y + _height / 2)) * (_target.y - (_y + _height / 2)));
	if (distance < 20) {
		_alive = false;
		return;
	}
	_x += _speed * time * (_target.x - _x) / distance * 7;
	_y += _speed * time * (_target.y - _y) / distance * 7;
	float dx = _target.x - _x;
	float dy = _target.y - _y;
	float rotation = (atan2(dy, dx)) * 180 / 3.14159265;
	_sprite.setRotation(rotation + 90);
	_sprite.setPosition(_x, _y);
}