#include "Map.h"

Map::Map(const sf::Image& image, const std::vector<sf::String>& layer1, const std::vector<sf::String>& layer2)
{
	set_map(image, layer1, layer2);
}

void Map::set_map(const sf::Image& image, const std::vector<sf::String>& layer1, const std::vector<sf::String>& layer2)
{
	_layer1.resize(layer1.size());
	for (int i = 0; i < _layer1.size(); ++i)
	{
		_layer1[i].resize(layer1[i].getSize());
		for (int j = 0; j < _layer1[i].size(); ++j)
		{
			if (layer1[i][j] == 'd') {
				_layer1[i][j] = Block::Dirt;
			}
			else if (layer1[i][j] == 'g') {
				_layer1[i][j] = Block::Grass;
			}
			else if (layer1[i][j] == 's') {
				_layer1[i][j] = Block::Sand;
			}
			else if (layer1[i][j] == 'a') {
				_layer1[i][j] = Block::Asphalt;
			}
			else if (layer1[i][j] == 'b') {
				_layer1[i][j] = Block::GrassBuildPlace;
			}
			else if (layer1[i][j] == 'p') {
				_layer1[i][j] = Block::SandBuildPlace;
			}
			else if (layer1[i][j] == 'x') {
				_layer1[i][j] = Block::GrassSpawnPlace;
			}
			else if (layer1[i][j] == 'v') {
				_layer1[i][j] = Block::AsphaltSpawnPlace;
			}
			else if (layer1[i][j] == 'f') {
				_layer1[i][j] = Block::Finish;
			}
		}
	}
	_layer2.resize(layer2.size());
	for (int i = 0; i < _layer2.size(); ++i)
	{
		_layer2[i].resize(layer1[i].getSize());
		for (int j = 0; j < _layer2[i].size(); ++j)
		{
			if (layer2[i][j] == 't') {
				_layer2[i][j] = Block::Three;
			}
			else if (layer2[i][j] == 's') {
				_layer2[i][j] = Block::Stone;
			}
			else if (layer2[i][j] == 'e') {
				_layer2[i][j] = Block::Empty;
			}
		}
	}
	_texture.loadFromImage(image);
	_sprite.setTexture(_texture);
}

void Map::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < _layer1.size(); ++i) {
		for (int j = 0; j < _layer1[i].size(); ++j) {
			window.draw(get_sprite(j, i));
		}
	}
	for (int i = 0; i < _layer2.size(); ++i) {
		for (int j = 0; j < _layer2[i].size(); ++j) {
			if (_layer2[i][j] == Block::Empty) { continue; }
			window.draw(get_sprite(j, i, 2));
		}
	}
}

sf::Sprite Map::get_sprite(int x, int y, int layer)
{
	if (layer == 1) { _sprite.setTextureRect(sf::IntRect(_layer1[y][x] * 64, 0, 64, 64)); }
	else if (layer == 2) { _sprite.setTextureRect(sf::IntRect(_layer2[y][x] * 64, 0, 64, 64)); }
	_sprite.setPosition(x * 64, y * 64);
	return _sprite;
}

void Map::set_block(int x, int y, Block block)
{
	_layer1[y][x] = block;
}

Block Map::get_block(int x, int y) const
{
	return _layer1[y][x];
}
