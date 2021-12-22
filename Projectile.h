#pragma once
#include <sfml/Graphics.hpp>
#include "Entity.h"
#include "Enemy.h"
#include "Map.h"
#include <list>

enum ProjectileType { BigRocket, DoubleRocket, CannonBall, DoubleCannonBall};

class Projectile : public Entity
{
public:
	Projectile(float x, float y, sf::Image& image, ProjectileType type, sf::Vector2f target);

	void update(float time, std::list<Enemy*>& enemies);

private:
	float _speed;
	sf::Vector2f _target;
	ProjectileType _type;
};
