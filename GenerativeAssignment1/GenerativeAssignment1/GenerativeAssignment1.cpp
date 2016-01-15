// GenerativeAssignment1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ParticleSystem.h"
#include <SFML/Graphics.hpp>



int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(512, 256), "Particles");

	int numParticles = 100000;
	int currentParticles = 500;

	// create the particle system
	ParticleSystem particles(numParticles);
	TriParticleSystem triParticles(numParticles);
	OrangeParticleSystem orangeParticles(numParticles);

	// create a clock to track the elapsed time
	sf::Clock clock;

	//textures
	sf::Texture tex;
	if (!tex.loadFromFile("C:\\Users\\Jonah\\Documents\\Visual Studio 2015\\Projects\\GenerativeAssignment1\\Debug\\bubble.png")) {
		// Do something
	}

	sf::Texture texTwo;
	if (!texTwo.loadFromFile("C:\\Users\\Jonah\\Documents\\Visual Studio 2015\\Projects\\GenerativeAssignment1\\Debug\\waterdrops.png")) {
		// Do something
	}

	sf::Texture texThree;
	if (!texThree.loadFromFile("C:\\Users\\Jonah\\Documents\\Visual Studio 2015\\Projects\\GenerativeAssignment1\\Debug\\orangedrop.png")) {
		// Do something
	}

	// run the main loop
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			//increase particles
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				currentParticles = currentParticles + 1000;
				if(currentParticles > 100000){
					currentParticles = numParticles;
				}
				particles.setStuff(currentParticles);
				//particles.setParticleCount(numParticles);
			}

			//decrease particles
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				currentParticles = currentParticles - 1000;
				if (currentParticles < 1) {
					currentParticles = 100;
				}
				particles.setStuff(currentParticles);
				//currentParticles = currentParticles - 1000;
				//if (numParticles < 1) {
				//	numParticles = 1;
				//}
				//ParticleSystem particles(numParticles);
			}

			//attractor and repeller set on LMB
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// set attractor at mouse position
				triParticles.setAttractor(sf::Vector2f(localPosition.x,localPosition.y));
				particles.setAttractor(sf::Vector2f(localPosition.x, localPosition.y));
			}


			if (event.type == sf::Event::Closed)
				window.close();
		}

		// make the particle system emitter follow the mouse
		particles.setStuff(currentParticles);
		triParticles.setStuff(currentParticles);
		orangeParticles.setStuff(currentParticles);
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		sf::Vector2f coordsOne = sf::Vector2f(215, -10);
		sf::Vector2f coordsTwo = sf::Vector2f(256, 250);
		sf::Vector2f coordsThree = sf::Vector2f(400, 0);
		//particles.setEmitter(window.mapPixelToCoords(mouse));
		triParticles.setEmitter(coordsOne);
		particles.setEmitter(coordsTwo);
		//orangeParticles.setEmitter(coordsThree);

		// update it
		sf::Time elapsed = clock.restart();
		particles.update(elapsed);
		triParticles.update(elapsed);
		//orangeParticles.update(elapsed);

		sf::RenderStates state = sf::RenderStates();
		state.texture = &tex;

		// draw it
		window.clear();
		window.draw(particles, state);
		state.texture = &texTwo;
		window.draw(triParticles, state);
		//state.texture = &texThree;
		//window.draw(orangeParticles, state);
		window.display();
	}

	return 0;
}

