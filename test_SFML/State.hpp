#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "scene_config.hpp"

enum STATE_VAL {
	EMPTY = 0,
	OBSTACLE = 2
};

class State {
	uint8_t state_data[NUMCELLS_C * NUMCELLS_R];
	uint8_t has_obstacle = false;
public:

	State() {
		// It should not be needed.
		//std::fill(state_data, state_data + (NUMCELLS_C * NUMCELLS_R), EMPTY);
	}

	uint16_t get_idx(uint16_t x, uint16_t y) {
		// Other indicization, the other seems more intuitive, but shouldn't change
		// return x * NUMCELLS_R + y;

		return x + y * NUMCELLS_C;
	}

	uint8_t get_state_data(uint8_t x, uint8_t y)
	{
#if VERBOSE == 3
		printf_s("getting state data for (%d,%d) => idx %d\n", x, y, x * NUMCELLS_C + y);
#endif
		return state_data[get_idx(x, y)];
	}

	void set_state_data(uint16_t x, uint16_t y, STATE_VAL value) {
#if VERBOSE >= 1
		printf_s("Setting state at pos (%d,%d)\n", x, y);
#endif
		if (state_data[get_idx(x, y)] == value) return;

		if (value == OBSTACLE) has_obstacle++;
		else if (value == EMPTY) has_obstacle--;

		state_data[get_idx(x, y)] = value;
	}

	void set_state_data_px(uint32_t x, uint32_t y, STATE_VAL value) {
		if (x <= GRID_PADDING || x >= SIZE_C - GRID_PADDING) return;
		if (y <= GRID_PADDING || y >= SIZE_R - GRID_PADDING) return;

#if VERBOSE >= 2
		printf_s("Setting state at pxl (%d,%d)\n", x, y);
#endif
		set_state_data(PXL2POS_XY_SEPARATE(x, y), value);
	}

	void draw(sf::RenderWindow& window) {

		for (int c = 0; c < NUMCELLS_C; c++)
			for (int r = 0; r < NUMCELLS_R; r++)
			{
				auto sh = sf::RectangleShape(sf::Vector2f(CELLSIZE_C - 1, CELLSIZE_R - 1));
				sh.setPosition(POS2PXL_XY_SEPARATE(c, r));
				switch (get_state_data(c, r))
				{

				case EMPTY:
					sh.setFillColor(sf::Color(25U, 25U, 25U));
					break;

				case OBSTACLE:
					sh.setFillColor(sf::Color(150U, 50U, 50U));
					break;

				default:
					sh.setFillColor(sf::Color(50U, 50U, 150U));
					break;
				}
				window.draw(sh);
			}
	}
};