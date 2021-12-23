#include <SFML/Graphics.hpp>

#include <iostream>
#include <list>
#include "Entity.h"
#include "Enemy.h"
#include "Tower.h"
#include "Projectile.h"
#include "Map.h"
#include "Level.h"

int main()
{
	/* ////////////////////////////// Window settings /////////////////////////////////////////////////////////////////////////////////// */
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tower Defence");
	sf::View view(sf::FloatRect(0, 0, 1920, 1080));
	window.setView(view);

	sf::Clock clock, timer;
	
	/* ////////////////////////////// Image ///////////////////////////////////////////////////////////////////////////////////////////// */
	sf::Image mapimage, enemyimage, towerimage, projectileimage;
	mapimage.loadFromFile("source\\map.png");
	enemyimage.loadFromFile("source\\enemies.png");
	towerimage.loadFromFile("source\\towers.png");
	projectileimage.loadFromFile("source\\projectile.png");
	
	/* ////////////////////////////// Level ///////////////////////////////////////////////////////////////////////////////////////////// */
	Level level(mapimage, enemyimage);

	/* ////////////////////////////// All towers and projectiles on level /////////////////////////////////////////////////////////////// */
	std::list<Tower*> towers{};
	std::list<Projectile*> projectiles{};

	/* ////////////////////////////// Tower upgrade and buy textures and sprites //////////////////////////////////////////////////////// */
	sf::Texture tower_buy_texture, tower_upgrade_texture, background_texture;
	tower_buy_texture.loadFromFile("source\\towerbuy.png");
	tower_upgrade_texture.loadFromFile("source\\towerupgrade.png");
	background_texture.loadFromFile("source\\background.png");
	background_texture.setRepeated(true);
	sf::Sprite tower_buy_sprite(tower_buy_texture);
	sf::Sprite tower_upgrade_sprite(tower_upgrade_texture);
	sf::Sprite background_sprite(background_texture, sf::IntRect(0, 0, 1920, 1080));
	background_sprite.setPosition(0, 0);
	bool tower_buy_open = false;
	bool tower_upgrade_open = false;

	/* ////////////////////////////// Text ////////////////////////////////////////////////////////////////////////////////////////////// */
	sf::Font font;
	font.loadFromFile("source\\PixeloidSans.ttf");
	// money and health state
	sf::Text values_state("", font, 40);
	values_state.setPosition(1620, 5);
	values_state.setFillColor(sf::Color::Red);
	values_state.setStyle(sf::Text::Bold);
	// text in menu
	sf::Text text_play("PLAY", font, 120);
	sf::Text text_exit("EXIT", font, 120);
	text_play.setPosition(800, 300); text_exit.setPosition(800, 450);
	// text in level choice
	sf::Text text_level1("Level 1", font, 100);
	sf::Text text_level2("Level 2", font, 100);
	text_level1.setPosition(20, 0); text_level2.setPosition(20, 120);
	// text in game end
	sf::Text text_victory("Victory!", font, 200);
	sf::Text text_defeat("Defeat", font, 200);
	sf::Text text_menu("MENU", font, 100);
	text_victory.setFillColor(sf::Color::Green);  text_defeat.setFillColor(sf::Color::Red);
	text_victory.setPosition(550, 300); text_defeat.setPosition(600, 300);
	text_menu.setPosition(800, 800);

	/* ////////////////////////////// Mouse position and previous click position //////////////////////////////////////////////////////// */
	sf::Vector2f prev_mouse_click_pos(-1, -1), mouse_pos;

	/* ////////////////////////////// Game state //////////////////////////////////////////////////////////////////////////////////////// */
	bool in_menu = true;
	bool in_level_choice = false;
	bool in_game = false;
	bool in_game_end = false;
	
	/* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
	/* ////////////////////////////// Gameloop ////////////////////////////////////////////////////////////////////////////////////////// */
	/* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
	while (window.isOpen())
	{
		float time = clock.restart().asMicroseconds() / 800.0;
		// mouse coords
		sf::Vector2i mouse_pixel_pos = sf::Mouse::getPosition(window);
		mouse_pos = window.mapPixelToCoords(mouse_pixel_pos);

		/* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
		/* ////////////////////////////// Events processing ///////////////////////////////////////////////////////////////// */
		/* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
		sf::Event event;
		while (window.pollEvent(event))
		{
			/* ////////////////////////////// Common events /////////////////////////////////////////////// */
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			/* ////////////////////////////// Events in menu ////////////////////////////////////////////// */
			if (event.type == sf::Event::MouseButtonPressed && in_menu) 
			{
				if (event.key.code == sf::Mouse::Left) {
					if (text_play.getGlobalBounds().contains(mouse_pos)) {
						in_menu = false;
						in_level_choice = true;
					}
					if (text_exit.getGlobalBounds().contains(mouse_pos)) {
						window.close();
					}
				}
			}
			/* ////////////////////////////// Events in level choice ////////////////////////////////////// */
			if (event.type == sf::Event::MouseButtonPressed && in_level_choice)
			{
				if (event.key.code == sf::Mouse::Left) {
					if (text_level1.getGlobalBounds().contains(mouse_pos)) {
						in_level_choice = false;
						in_game = true;
						clock.restart(); timer.restart();
						projectiles.clear();
						towers.clear();
						level.set_level(LevelNumber::Level1);
					}
					if (text_level2.getGlobalBounds().contains(mouse_pos)) {
						in_level_choice = false;
						in_game = true;
						clock.restart(); timer.restart();
						projectiles.clear();
						towers.clear();
						level.set_level(LevelNumber::Level2);
					}
				}
			}

			/* ////////////////////////////// Events in game ////////////////////////////////////////////// */
			if (event.type == sf::Event::MouseButtonPressed && in_game)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					if (mouse_pos.x / 64 < 0 || mouse_pos.x / 64 > 25 || mouse_pos.y / 64 < 0 || mouse_pos.y / 64 > 16) {
					
					}
					else if (tower_buy_open) {
						int temp_x = int(prev_mouse_click_pos.x) / 64 * 64, temp_y = int(prev_mouse_click_pos.y) / 64 * 64;
						sf::FloatRect cannon_choice(temp_x - 64, temp_y - 64, 80, 80);
						sf::FloatRect double_cannon_choice(temp_x + 127, temp_y - 64, -80, 80);
						sf::FloatRect rocket_launcher_choice(temp_x - 64, temp_y + 127, 80, -80);
						sf::FloatRect double_rocket_launcher_choice(temp_x + 127, temp_y + 127, -80, -80);
						if (cannon_choice.contains(mouse_pos) && level._money >= 60) {
							towers.push_back(new Tower(temp_x, temp_y, towerimage, TowerType::Cannon));
							level._money -= 60;
						}
						else if (double_cannon_choice.contains(mouse_pos) && level._money >= 110) {
							towers.push_back(new Tower(temp_x, temp_y, towerimage, TowerType::DoubleCannon));
							level._money -= 110;
						}
						else if (rocket_launcher_choice.contains(mouse_pos) && level._money >= 65) {
							towers.push_back(new Tower(temp_x, temp_y, towerimage, TowerType::RocketLauncher));
							level._money -= 65;
						}
						else if (double_rocket_launcher_choice.contains(mouse_pos) && level._money >= 120) {
							towers.push_back(new Tower(temp_x, temp_y, towerimage, TowerType::DoubleRocketLauncher));
							level._money -= 120;
						}
						tower_buy_open = false;
					}
					else if (tower_upgrade_open) {
						int temp_x = int(prev_mouse_click_pos.x) / 64 * 64, temp_y = int(prev_mouse_click_pos.y) / 64 * 64;
						sf::FloatRect sell_choise(temp_x + 127, temp_y + 127, -80, -80);
						if (sell_choise.contains(mouse_pos)) {
							for (auto it = towers.begin(); it != towers.end(); ++it) {
								if ((*it)->get_pos() == sf::Vector2f(int(prev_mouse_click_pos.x) / 64 * 64, int(prev_mouse_click_pos.y) / 64 * 64)) {
									level._money += int((*it)->get_price() / 100.0 * 66);
									it = towers.erase(it);
									break;
								}
							}
						}
						tower_upgrade_open = false;
					}
					else if (level.map.get_block(mouse_pos.x / 64, mouse_pos.y / 64) == Block::GrassBuildPlace
						|| level.map.get_block(mouse_pos.x / 64, mouse_pos.y / 64) == Block::SandBuildPlace)
					{
						for (auto it = towers.begin(); it != towers.end(); ++it) {
							if ((*it)->get_pos() == sf::Vector2f(int(mouse_pos.x) / 64 * 64, int(mouse_pos.y) / 64 * 64)) {
								tower_upgrade_open = true;
								break;
							}
						}
						if (tower_upgrade_open) {
							tower_upgrade_sprite.setPosition(int(mouse_pos.x) / 64 * 64 - 64, int(mouse_pos.y) / 64 * 64 - 64);
						}
						else {
							tower_buy_open = true;
							tower_buy_sprite.setPosition(int(mouse_pos.x) / 64 * 64 - 64, int(mouse_pos.y) / 64 * 64 - 64);
						}
					}
					prev_mouse_click_pos = mouse_pos;
				}
			}

			/* ////////////////////////////// Events in game end ////////////////////////////////////////// */
			if (event.type == sf::Event::MouseButtonPressed && in_game_end)
			{
				if (event.key.code == sf::Mouse::Left) {
					if (text_menu.getGlobalBounds().contains(mouse_pos)) {
						in_game_end = false;
						in_menu = true;
					}
				}
			}
		}
		
		window.clear(sf::Color::White);
		window.draw(background_sprite);
		
		/* ////////////////////////////// In menu /////////////////////////////////////////////////////////////////////////// */
		if (in_menu)
		{
			text_play.setFillColor(sf::Color::Blue);
			text_exit.setFillColor(sf::Color::Blue);
			if (text_play.getGlobalBounds().contains(mouse_pos)) {
				text_play.setFillColor(sf::Color::Red);
			}
			if (text_exit.getGlobalBounds().contains(mouse_pos)) {
				text_exit.setFillColor(sf::Color::Red);
			}
			window.draw(text_play);
			window.draw(text_exit);
		}

		/* ////////////////////////////// In level choice /////////////////////////////////////////////////////////////////// */
		if (in_level_choice)
		{
			text_level1.setFillColor(sf::Color::Blue);
			text_level2.setFillColor(sf::Color::Blue);
			if (text_level1.getGlobalBounds().contains(mouse_pos)) {
				text_level1.setFillColor(sf::Color::Red);
			}
			if (text_level2.getGlobalBounds().contains(mouse_pos)) {
				text_level2.setFillColor(sf::Color::Red);
			}
			window.draw(text_level1);
			window.draw(text_level2);
		}

		/* ////////////////////////////// In game /////////////////////////////////////////////////////////////////////////// */
		if (in_game)
		{
			level.map.draw(window);

			for (auto it = level.enemies.begin(); it != level.enemies.end();) {
				if ((*it)->is_alive()) {
					if ((*it)->get_spawn_time() <= timer.getElapsedTime().asSeconds()) {
						(*it)->update(time, level.map);
						window.draw((*it)->get_sprite());
					}
					++it;
				}
				else {
					if ((*it)->reach_finish()) {
						level._health -= (*it)->get_damage();
					}
					else {
						level._money += (*it)->give_money();
					}
					it = level.enemies.erase(it);
				}
			}
			for (auto it = towers.begin(); it != towers.end();) {
				if ((*it)->is_alive()) {
					(*it)->update(time, timer.getElapsedTime().asSeconds(), level.enemies, projectiles, projectileimage);
					window.draw((*it)->get_sprite());
					++it;
				}
				else {
					it = towers.erase(it);
				}
			}
			for (auto it = projectiles.begin(); it != projectiles.end();) {
				if ((*it)->is_alive()) {
					(*it)->update(time, level.enemies);
					window.draw((*it)->get_sprite());
					++it;
				}
				else {
					it = projectiles.erase(it);
				}
			}

			if (tower_buy_open) {
				window.draw(tower_buy_sprite);
			}
			if (tower_upgrade_open) {
				window.draw(tower_upgrade_sprite);
			}

			values_state.setString("Money " + std::to_string(level._money) + "\nHealth " + std::to_string(level._health));
			window.draw(values_state);

			if (level._health <= 0 || level.enemies.empty()) {
				in_game = false;
				in_game_end = true;
			}
		}
		
		/* ////////////////////////////// In game end /////////////////////////////////////////////////////////////////////// */
		if (in_game_end)
		{
			level.map.draw(window);
			for (auto it = level.enemies.begin(); it != level.enemies.end(); ++it) {
				window.draw((*it)->get_sprite());
			}
			for (auto it = towers.begin(); it != towers.end(); ++it) {
				window.draw((*it)->get_sprite());
			}
			values_state.setString("Money " + std::to_string(level._money) + "\nHealth " + std::to_string(level._health));
			window.draw(values_state);

			if (level._health > 0) {
				window.draw(text_victory);
			}
			else {
				window.draw(text_defeat);
			}
			text_menu.setFillColor(sf::Color::Red);
			if (text_menu.getGlobalBounds().contains(mouse_pos)) {
				text_menu.setFillColor(sf::Color::Green);
			}
			window.draw(text_menu);
		}
		window.display();
	}
	return 0;
}