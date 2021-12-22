#include "Level.h"

// first layer: g - Grass, d - Dirt, a - Asphalt, s - Sand, b GrassBuildPlace, p - sandBuildPlace, x - GrassSpawnPlace, v - AsphaltSpawnPlace, f - Finish
// second layer: t - Three, s - Stone, e - Empty

std::vector<sf::String> map_lvl1_layer1 =
{
	"ggggggggggggggggggggggggg",
	"ggggggggggggggggggggggggg",
	"xdddggggggggggggggdddddgg",
	"ggbdggggggggggggggdgggdgg",
	"gggdggggggggggggggdgggdbg",
	"gggdggggggggggggggdbggddf",
	"gggdggggggggggggggdggggbg",
	"ggbdbggggggggggggbdgggggg",
	"gggdggggbggggbggggdgggggg",
	"gggdggggddddddggggdgggggg",
	"gggdbgggdbggbdgggbdgggggg",
	"gggddddddggggddddddgggggg",
	"ggggggggggggggggggggggggg",
	"ggggggggggggggggggggggggg",
	"ggggggggggggggggggggggggg",
	"ggggggggggggggggggggggggg",
};

std::vector<sf::String> map_lvl1_layer2 =
{
	"eteeeeseeeeeeeeeeeeeeseee",
	"eeeeeeeeeeeeeeteeeeeeeeet",
	"eeeeeeeeeteeeeeeeeeeeeeee",
	"eeeeeeeseeeteeeeeeeeeeees",
	"eeeeeeeeeeeeeeeseeeeeeeee",
	"eeeeeeseeeeeeteeeeeeeeeee",
	"eeeeeeetseeeeeseeeeeeeeee",
	"eeeeeeeeeeeeeeeeeeeeeseee",
	"eteeeeeeeeeeeeeeeeeeeeeee",
	"eeeeeeeeeeeeeeeeeeeeeetee",
	"eeeeeeeeeeeeeeeeeeeeeeeee",
	"eeeeeeeeeeeeeeeeeeeeteeee",
	"eeeeeeeeeeeeeeeeeeeeeeese",
	"eeeeeeeeeeeeeeeeeeeeeteee",
	"eeeeteesseeeeeeeseeeeseee",
	"eteeeeeeeeeeteeeeeeeseeet",
};

std::vector<sf::String> map_lvl2_layer1 =
{
	"sssssssssssssssssssssssss",
	"sssssssaaaaaaaaaaaassssss",
	"sssssssapsssssssspaaaaaaf",
	"sssssssassssssssssspspsps",
	"sssssssasssssssaaaaaaaaaf",
	"sssssssasssssssasssssssss",
	"sspssssasssssssasssssssss",
	"vaaaaaaasssssssapssssssss",
	"sssspssssssssssasssssssss",
	"spsssssssssssssasssssssss",
	"vaaaaaaaaaaapspasssssssss",
	"sssspssssssaaaaasssssssss",
	"sssssssssssssssssssssssss",
	"sssssssssssssssssssssssss",
	"sssssssssssssssssssssssss",
	"sssssssssssssssssssssssss"
};

std::vector<sf::String> map_lvl2_layer2 =
{
	"eeeseeeeeeeeeeeeeeeetesee",
	"seteeeeeeeeeeeeeeeeeeeeee",
	"eeeeeeeeeeeeeeeeeeeeeeeee",
	"eeeeeeeeeeeeeeeeeeeeeeeee",
	"teeeeeeeeeeeeeeeeeeeeeeee",
	"eeeeeteeeeeeeeeeeeeeeeeee",
	"eeeeeeeeeeeeeeeeeeeeeeeee",
	"eeeeeeeeeeetseeeeeeeeeeee",
	"eeeeeeeeeeeeeeeeeeeeeeeee",
	"eeeeeeeeeeeeeeeeeeeeeeeee",
	"eeeeeeeeeeeeeeeeeeeeeeese",
	"eeeeeeeeeeeeeeeeeeeeeeeee",
	"teseeeeeeeeeeeeeeteeeeese",
	"eeeeeeeeeeeeeeeseeeeeteee",
	"eeeeteeeeeeeeeeeeeeeeeeee",
	"eeeeeeeeeeeeeteeeeeseeeee",
};

Level::Level(sf::Image& map_image, sf::Image& enemy_image)
{
	_map_image = map_image;
	_enemy_image = enemy_image;
}

void Level::set_level(LevelNumber level_number) {
	_level_number = level_number;
	if (_level_number == LevelNumber::Level1)
	{
		map.set_map(_map_image, map_lvl1_layer1, map_lvl1_layer2);
		_health = 20;
		_money = 350;
		enemies =
		{
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 0),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 1),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 2),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 3),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Officer, Direction::Right, 4),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Officer, Direction::Right, 7),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 7.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 8),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 8.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 9),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 9.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 10),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Officer, Direction::Right, 10.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Officer, Direction::Right, 11),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 14),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 14.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 15),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 15.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 16),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 16.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 17),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 17.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Officer, Direction::Right, 18),

			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Tank, Direction::Right, 35),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 37),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 37.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 38),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 38.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 39),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 39.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 40),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Tank, Direction::Right, 40),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Tank, Direction::Right, 40.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 40.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 41),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 41.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 42),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 42.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 43),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 43.5),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Soldier, Direction::Right, 44),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Tank, Direction::Right, 44.5),

			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Airplane, Direction::Right, 60),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Airplane, Direction::Right, 62),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Airplane, Direction::Right, 64),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Airplane, Direction::Right, 66),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Airplane, Direction::Right, 68),
			new Enemy(0, 64 * 2, _enemy_image, EnemyType::Airplane, Direction::Right, 60),
		};
	}

	else if (_level_number == LevelNumber::Level2)
	{
		map.set_map(_map_image, map_lvl2_layer1, map_lvl2_layer2);
		_health = 20;
		_money = 400;
		enemies =
		{
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 0),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 0),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 1),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 1),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 2),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 2),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 3),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 3),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::ZombiOfficer, Direction::Right, 4),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiOfficer, Direction::Right, 4),

			new Enemy(0, 64 * 7, _enemy_image, EnemyType::SandTank, Direction::Right, 10),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::SandTank, Direction::Right, 12),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::SandTank, Direction::Right, 14),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::SandTank, Direction::Right, 16),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::SandTank, Direction::Right, 18),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::SandTank, Direction::Right, 20),

			new Enemy(0, 64 * 10, _enemy_image, EnemyType::SandTank, Direction::Right, 25),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 27),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 27.5),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 28),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 28.5),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 29),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 29.5),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 30),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::SandTank, Direction::Right, 30),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::SandTank, Direction::Right, 30.5),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 30.5),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 31),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 31.5),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 32),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 32.5),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 33),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 33.5),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::ZombiSoldier, Direction::Right, 34),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::SandTank, Direction::Right, 34.5),

			new Enemy(0, 64 * 10, _enemy_image, EnemyType::SandAirplane, Direction::Right, 50),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::SandAirplane, Direction::Right, 51),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::SandAirplane, Direction::Right, 52),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::SandAirplane, Direction::Right, 53),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::SandAirplane, Direction::Right, 54),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::SandAirplane, Direction::Right, 55),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::SandAirplane, Direction::Right, 56),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::SandAirplane, Direction::Right, 57),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::SandAirplane, Direction::Right, 58),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::SandAirplane, Direction::Right, 59),
			new Enemy(0, 64 * 10, _enemy_image, EnemyType::SandAirplane, Direction::Right, 60),
			new Enemy(0, 64 * 7, _enemy_image, EnemyType::SandAirplane, Direction::Right, 61),
		};
	}

	else if (_level_number == LevelNumber::Level2)
	{
		map.set_map(_map_image, map_lvl2_layer1, map_lvl2_layer2);
		_health = 20;
		_money = 400;
	}
}