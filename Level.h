#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Map.h"
#include "Enemy.h"

enum class LevelNumber { Level1 = 1, Level2 };

class Level {
public:
	Level(sf::Image& map_image, sf::Image& enemy_image);
	void set_level(LevelNumber level_number);

	Map map;
	std::list<Enemy*> enemies;
	int _health, _money;
	
private:
	LevelNumber _level_number;
	sf::Image _map_image;
	sf::Image _enemy_image;
};