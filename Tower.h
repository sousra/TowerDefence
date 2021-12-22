#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Enemy.h"
#include "Projectile.h"
#include <list>
#include <cmath>

enum TowerType { Cannon, DoubleCannon, RocketLauncher, DoubleRocketLauncher };

class Tower : public Entity
{
public:
	Tower(float x, float y, const sf::Image& image, TowerType type);

	void update(float time, float timer, std::list<Enemy*>& enemies, std::list<Projectile*>& projectiles, sf::Image& projectile_image);

	int get_price() const noexcept;

private:
	float _range;
	float _recharge_time;
	float _last_shoot_time;
	int _price;
	TowerType _type;
	ProjectileType _projectile_type;
};