// test_SFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
#include <iostream>

int main()
{
	std::cout << "Hello World!\n";
}*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include <SFML/Graphics.hpp>



#include <array>
#include <iostream>
#include <iterator>
#include <string>

#include "test_SFML.h"
#include "State.hpp"
#include "Scene.hpp"

Scene scene = {};
State state = {};


void renderingThread(sf::RenderWindow* window)
{
	// activate the window's context
	window->setActive(true);

	// the rendering loop
	while (window->isOpen())
	{
		window->clear();

		state.draw(*window);

		scene.draw(*window, scene);

		// end the current frame
		window->display();
	}

}

int main()
{
	sf::RenderWindow window(sf::VideoMode(SIZE_C, SIZE_R), "MAPF LOL");

	scene.init(NUM_AGENTS);

	// Deactivate its OpenGL context
	window.setActive(false);

	// Launch the rendering thread
	sf::Thread thread(&renderingThread, &window);

	thread.launch();
	while (window.isOpen())
	{
		sf::Event event;
		window.setKeyRepeatEnabled(false);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.KeyReleased && event.key.code == sf::Keyboard::Space) {
				scene.init_agents(NUM_AGENTS);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

				state.set_state_data_px(mouse_pos.x, mouse_pos.y, OBSTACLE);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

				state.set_state_data_px(mouse_pos.x, mouse_pos.y, EMPTY);
			}
		}

	}

	return 0;
}
