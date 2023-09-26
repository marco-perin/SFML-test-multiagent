#pragma once

#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <random>


#include <SFML/Graphics.hpp>

#include "scene_config.hpp"


class Scene {
private:
	std::vector<uint32_t> idxs;
	std::default_random_engine rng_engine;
public:

	std::vector<std::array<sf::Vertex, 2Ui64>> lines;
	std::vector<sf::Vector2f> agents;

	Scene() : lines(), agents(), rng_engine() {};

	void draw(sf::RenderWindow& window, Scene& scene);

	void init(uint16_t num_agents);
	void init_grid(std::vector<std::array<sf::Vertex, 2Ui64>>& lines);
	void init_agents(const uint16_t num_agents);

	//const sf::Vector2f& get_new_rand_pos();

	bool is_new_pos_valid(const sf::Vector2f new_pos);

};
