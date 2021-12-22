#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"

enum Direction { Left = 0, Right, Up, Down };
enum EnemyType { Soldier = 0, Officer, ZombiSoldier, ZombiOfficer, Tank, SandTank, Airplane, SandAirplane };

class Enemy : public Entity
{
public:
	Enemy(float x, float y, const sf::Image& image, EnemyType type, Direction direction, float spawn_time);

	void update(float time, const Map& map);
	void check_collision_with_map(const Map& map);

	int give_money() const noexcept;
	bool reach_finish() const noexcept;
	float get_spawn_time() const noexcept;
	void reduce_health(int value) noexcept;

private:
	int _health;
	int _give_money;
	float _speed;
	bool _reach_finish;
	float _spawn_time;
	Direction _direction;
	EnemyType _type;
};