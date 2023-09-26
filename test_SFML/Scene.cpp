#include "Scene.hpp"
#include <algorithm>
#include <random>



sf::CircleShape sh;
void Scene::draw(sf::RenderWindow& window, Scene& scene)
{

	for (int i = 0; i < lines.size(); i++)
	{
		window.draw(lines[i].data(), 2, sf::Lines);
	}

	for (int i = 0; i < agents.size(); i++)
	{
		//window.draw(agents[i]);
		sh = sf::CircleShape(INCELLSIZE_MIN, 10);
		sh.setPosition(agents[i]);
		window.draw(sh);
	}
}


void Scene::init(uint16_t num_agents)
{
	init_grid(lines);
	init_agents(num_agents);
}


void Scene::init_grid(std::vector<std::array<sf::Vertex, 2Ui64>>& lines)
{
	// Draw the two starting lines
	std::array<sf::Vertex, 2> line;

	line = {
		sf::Vertex(sf::Vector2f(1, 0)),
		sf::Vertex(sf::Vector2f(1, SIZE_R))
	};

	lines.push_back(line);

	line = {
		sf::Vertex(sf::Vector2f(0     , 1)),
		sf::Vertex(sf::Vector2f(SIZE_R, 1))
	};

	lines.push_back(line);

	uint16_t gridspace_x = SIZE_C / NUMCELLS_C;
	for (int x = 0; x < SIZE_C + 1; x += gridspace_x)
	{

		line = {
			sf::Vertex(sf::Vector2f(x, 0)),
			sf::Vertex(sf::Vector2f(x, SIZE_R))
		};

		lines.push_back(line);
	}

	uint16_t gridspace_y = SIZE_R / NUMCELLS_R;
	for (int y = 0; y < SIZE_R + 1; y += gridspace_y)
	{
		line = {
			sf::Vertex(sf::Vector2f(0     , y)),
			sf::Vertex(sf::Vector2f(SIZE_R, y))
		};

		lines.push_back(line);
	}
}

static sf::Vector2f idx_to_pos(uint32_t idx) {
	return sf::Vector2f(idx % NUMCELLS_C, idx / NUMCELLS_C);
}

void Scene::init_agents(const uint16_t num_agents) {

	if (idxs.size() != (NUMCELLS_C * NUMCELLS_R))
	{
		printf_s("Initializing idxs array\n");
		idxs.clear();
		for (int i = 0; i < NUMCELLS_C * NUMCELLS_R; i++)
		{
			idxs.push_back(i);
		}
	}

	std::shuffle(idxs.begin(), idxs.end(), rng_engine);

	sf::Vector2f temp_pos;


	if (agents.size() != num_agents)
	{
		// Initialize agents
		printf_s("Initializing agents array\n");

		for (int i = 0; i < num_agents; i++)
			agents.push_back(sf::Vector2f(0, 0));
		//agents.push_back(sf::CircleShape(INCELLSIZE_MIN, 10));
	}

	for (int i = 0; i < num_agents; i++)
	{
		temp_pos = idx_to_pos(this->idxs[i]);
		//agents[i].setPosition(POS2CELL_XY(temp_pos));
		agents[i] = sf::Vector2f(POS2CELL_XY(temp_pos));

	}
	//printf_s("##############################\n");
}
