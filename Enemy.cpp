#include "Enemy.h"

Enemy::Enemy(float x, float y, const sf::Image& image, EnemyType type, Direction direction, float spawn_time)
	: Entity(x, y, image), _type(type), _direction(direction), _reach_finish(false), _spawn_time(spawn_time)
{
	if (_type == EnemyType::Soldier || _type == EnemyType::ZombiSoldier) {
		_width = 28;
		_height = 28;
		_speed = 0.05;
		_health = 150;
		_give_money = 5;
		_damage = 1;
	}
	else if (_type == EnemyType::Officer || _type == EnemyType::ZombiOfficer) {
		_width = 28;
		_height = 28;
		_speed = 0.05;
		_health = 200;
		_give_money = 7;
		_damage = 1;
	}
	else if (_type == EnemyType::Tank || _type == EnemyType::SandTank) {
		_width = 42;
		_height = 28;
		_speed = 0.04;
		_health = 600;
		_give_money = 10;
		_damage = 2;
	}
	else if (_type == EnemyType::Airplane || _type == EnemyType::SandAirplane) {
		_width = 38;
		_height = 48;
		_speed = 0.06;
		_health = 400;
		_give_money = 11;
		_damage = 2;
	}

	if (_direction == Direction::Left || _direction == Direction::Right) { _y += (64 - _height) / 2; }
	else if (_direction == Direction::Up || _direction == Direction::Down) { _x += (64 - _height) / 2; }

	_first_width = _width;
	_first_height = _height;
}

void Enemy::update(float time, const Map& map)
{
	if (_direction == Direction::Left) {
		_x += -_speed * time;
		_width = _first_width;
		_height = _first_height;
	}
	else if (_direction == Direction::Right) {
		_x += _speed * time;
		_width = _first_width;
		_height = _first_height;
	}
	else if (_direction == Direction::Up) {
		_y += -_speed * time;
		_width = _first_height;
		_height = _first_width;
	}
	else if (_direction == Direction::Down) {
		_y += _speed * time;
		_width = _first_height;
		_height = _first_width;
	}

	if (_type == EnemyType::Soldier || _type == EnemyType::Officer || _type == EnemyType::ZombiSoldier || _type == EnemyType::ZombiOfficer)
	{
		switch (_direction) {
		case Left: _sprite.setTextureRect(sf::IntRect(_width * _type + _width - 1, 0, -_width, _height)); break;
		case Right: _sprite.setTextureRect(sf::IntRect(_width * _type, 0, _width, _height)); break;
		case Up: _sprite.setTextureRect(sf::IntRect(_width * _type, 28 + _height - 1, _width, -_height)); break;
		case Down: _sprite.setTextureRect(sf::IntRect(_width * _type, 28, _width, _height));
		}
	}
	else if (_type == EnemyType::Tank || _type == EnemyType::SandTank)
	{
		switch (_direction) {
		case Left: _sprite.setTextureRect(sf::IntRect(_width * (_type - EnemyType::Tank) + _width - 1, 56, -_width, _height)); break;
		case Right: _sprite.setTextureRect(sf::IntRect(_width * (_type - EnemyType::Tank), 56, _width, _height)); break;
		case Up: _sprite.setTextureRect(sf::IntRect(_width * (_type - EnemyType::Tank), 84 + _height - 1, _width, -_height)); break;
		case Down: _sprite.setTextureRect(sf::IntRect(_width * (_type - EnemyType::Tank), 84, _width, _height));
		}
	}
	else if (_type == EnemyType::Airplane || _type == EnemyType::SandAirplane)
	{
		switch (_direction) {
		case Left: _sprite.setTextureRect(sf::IntRect(_width * (_type - EnemyType::Airplane) + _width - 1, 126, -_width, _height)); break;
		case Right: _sprite.setTextureRect(sf::IntRect(_width * (_type - EnemyType::Airplane), 126, _width, _height)); break;
		case Up: _sprite.setTextureRect(sf::IntRect(_width * (_type - EnemyType::Airplane), 174 + _height - 1, _width, -_height)); break;
		case Down: _sprite.setTextureRect(sf::IntRect(_width * (_type - EnemyType::Airplane), 174, _width, _height));
		}
	}

	_sprite.setPosition(_x, _y);
	check_collision_with_map(map);
}

void Enemy::check_collision_with_map(const Map& map)
{
	for (int i = _y / 64; i < (_y + _height) / 64; ++i) {
		for (int j = _x / 64; j < (_x + _width) / 64; ++j) {
			if (map.get_block(j, i) == Block::Grass || map.get_block(j, i) == Block::Sand
				|| map.get_block(j, i) == Block::GrassBuildPlace || map.get_block(j, i) == Block::SandBuildPlace)
			{
				if (_direction == Direction::Left)
				{
					if (map.get_block(_x / 64 + 1, _y / 64 + 1) == map.get_block(j, i)) { // Если снизу тупик
						_direction = Direction::Up;
					}
					else {
						_direction = Direction::Down;
					}
					_x = j * 64 + 64 + (64 - _height) / 2;
				}
				else if (_direction == Direction::Right)
				{
					if (map.get_block(_x / 64, _y / 64 + 1) == map.get_block(j, i)) { // Если снизу тупик
						_direction = Direction::Up;
					}
					else {
						_direction = Direction::Down;
					}
					_x = j * 64 - _height - (64 - _height) / 2;
				}
				else if (_direction == Direction::Up)
				{
					if (map.get_block(_x / 64 + 1, _y / 64 + 1) == map.get_block(j, i)) { // Если справа тупик
						_direction = Direction::Left;
					}
					else {
						_direction = Direction::Right;
					}
					_y = i * 64 + 64 + (64 - _height) / 2;
				}
				else if (_direction == Direction::Down)
				{
					if (map.get_block(_x / 64 + 1, _y / 64) == map.get_block(j, i)) { // Если справа тупик
						_direction = Direction::Left;
					}
					else {
						_direction = Direction::Right;
					}
					_y = i * 64 - _width - (64 - _width) / 2;
				}
			}
			else if (map.get_block(j, i) == Block::Finish) {
				_reach_finish = true;
				_alive = false;
			}
		}
	}
}

int Enemy::give_money() const noexcept
{
	return _give_money;
}

bool Enemy::reach_finish() const noexcept
{
	return _reach_finish;
}

float Enemy::get_spawn_time() const noexcept
{
	return _spawn_time;
}

void Enemy::reduce_health(int value) noexcept
{
	_health -= value;
	if (_health < 0) { _alive = false; }
}