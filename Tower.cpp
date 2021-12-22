#include "Tower.h"

Tower::Tower(float x, float y, const sf::Image& image, TowerType type)
	: Entity(x, y, image), _type(type)
{
	_width = 64;
	_height = 64;
	_first_width = 64;
	_first_height = 64;
	_sprite.setOrigin(_width / 2, _height / 2);
	_sprite.setPosition(_x + _width / 2, _y + _height / 2);
	if (_type == TowerType::Cannon) {
		_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
		_damage = 40;
		_range = 240;
		_recharge_time = 1;
		_price = 60;
		_projectile_type = ProjectileType::CannonBall;
	}
	else if (_type == TowerType::DoubleCannon) {
		_sprite.setTextureRect(sf::IntRect(64, 0, 64, 64));
		_damage = 80;
		_range = 240;
		_recharge_time = 1;
		_price = 110;
		_projectile_type = ProjectileType::DoubleCannonBall;
	}
	else if (_type == TowerType::RocketLauncher) {
		_sprite.setTextureRect(sf::IntRect(64, 64, 64, 64));
		_damage = 130;
		_range = 240;
		_recharge_time = 3;
		_price = 65;
		_projectile_type = ProjectileType::BigRocket;
	}
	else if (_type == TowerType::DoubleRocketLauncher) {
		_sprite.setTextureRect(sf::IntRect(0, 64, 64, 64));
		_damage = 260;
		_range = 240;
		_recharge_time = 3;
		_price = 120;
		_projectile_type = ProjectileType::DoubleRocket;
	}
	_last_shoot_time = -_recharge_time;
}

void Tower::update(float time, float timer, std::list<Enemy*>& enemies, std::list<Projectile*>& projectiles, sf::Image& projectile_image)
{
	for (auto it = enemies.begin(); it != enemies.end(); ++it) {
		float distance = sqrt(
			pow(((*it)->get_pos().x + (*it)->get_width() / 2 - (_x + _width / 2)), 2)
			+ pow(((*it)->get_pos().y + (*it)->get_height() / 2 - (_y + _height / 2)), 2)
		);
		if (distance <= _range && timer - _last_shoot_time >= _recharge_time && (*it)->get_spawn_time() <= timer) {
			float target_x = (*it)->get_pos().x + (*it)->get_width() / 2;
			float target_y = (*it)->get_pos().y + (*it)->get_height() / 2;
			projectiles.push_back(new Projectile(_x + _width / 2, _y + _height / 2, projectile_image, _projectile_type, sf::Vector2f(target_x, target_y)));

			float dx = target_x - _x - _width / 2;
			float dy = target_y - _y - _height / 2;
			float rotation = (atan2(dy, dx)) * 180 / 3.14159265;
			_sprite.setRotation(rotation + 90);

			_last_shoot_time = timer;
			break;
		}
	}
}

int Tower::get_price() const noexcept
{
	return _price;
}