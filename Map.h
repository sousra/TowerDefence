#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum Block { Grass = 0, Dirt, Asphalt, Sand, GrassBuildPlace, SandBuildPlace, AsphaltSpawnPlace, GrassSpawnPlace, Finish, Three, Stone, Empty };

class Map {
public:
	Map() = default;
	Map(const sf::Image& image, const std::vector<sf::String>& layer1, const std::vector<sf::String>& layer2 = {});
	void set_map(const sf::Image& image, const std::vector<sf::String>& layer1, const std::vector<sf::String>& layer2);
	void draw(sf::RenderWindow& window);

	sf::Sprite get_sprite(int x, int y, int layer = 1);
	void set_block(int x, int y, Block block);
	Block get_block(int x, int y) const;

private:
	std::vector<std::vector<Block>> _layer1, _layer2;
	sf::Texture _texture;
	sf::Sprite _sprite;
};