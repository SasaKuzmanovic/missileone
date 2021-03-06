/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// project comment in main.cpp
/// </summary>

#include "Game.h"
#include "MyVector2.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	squareSetup();
	groundSetup();
	altitudeBarSetup();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{

}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
	if (sf::Event::MouseButtonPressed == newEvent.type)
	{
		processMouseClick(newEvent);
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	squareSetup();
	groundSetup();
	altitudeBarLoading();
	laser();
	asteroidDraw();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_welcomeMessage);
	m_window.draw(square);
	m_window.draw(m_logoSprite);
	m_window.draw(rectangle);
	m_window.draw(altitude);
	m_window.draw(m_line);
	m_window.draw(m_explosion);
	m_window.draw(m_altitude);
	m_window.draw(asteroid);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_altitude.setString("Altitude");
	m_altitude.setFont(m_ArialBlackfont);
	m_altitude.setPosition(50.0f, 550.0f);
	m_altitude.setFillColor(sf::Color::Black);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\base.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(385.0f, 510.0f);
}

// setting up the square in the middle
void Game::squareSetup()
{
	square.setSize(sf::Vector2f(40, 40));
	square.setFillColor(sf::Color::Yellow);
	square.setPosition(385.0f, 510.0f);
}

// setting up the ground level in the game
void Game::groundSetup()
{
	rectangle.setSize(sf::Vector2f(1200, 50));
	rectangle.setFillColor(sf::Color::Cyan);
	rectangle.setPosition(0.0f, 550.0f);
}

// altitude setup
void Game::altitudeBarSetup()
{
	altitude.setSize(sf::Vector2f(0, 15));
	altitude.setFillColor(sf::Color::Yellow);
	altitude.setPosition(0.0f, 585.0f);
}

// loading bar increasing over time
void Game::altitudeBarLoading()
{
	if (altitudeBar <= 500)
	{
		altitudeBar++;
		altitude.setSize(sf::Vector2f(altitudeBar, 10));
	}

}
// code for detecting the mouseclick, and finding positions of the line, also has line speed calculation
void Game::processMouseClick(sf::Event t_bestEvent)
{
	if (sf::Mouse::Left == t_bestEvent.mouseButton.button)
	{
		if (shot == false)
		{

			shot = true;

			mouseClick = sf::Vector2f{ static_cast<float>(t_bestEvent.mouseButton.x), static_cast<float>(t_bestEvent.mouseButton.y) };

			lineEnd = mouseClick;
			lineStart = sf::Vertex{ sf::Vector2f{400.0f,520.0f}, sf::Color::White };

			headVector = mouseClick - lineStart.position;
			headVector = vectorUnitVector(headVector);
			velocity = headVector * speed;

			missileLocation = sf::Vector2f{ 405.0f,500.0f };
		}
	}
}

void Game::laser()
{
	if (shot == true)
	{
		missileLocation += velocity;
		lineEnd.position = missileLocation;
		m_line.clear();

		resetAltitude();

		lineExplosion();

		m_line.append(lineStart);
		m_line.append(lineEnd);
		if (lineEnd.position.y < mouseClick.y)
		{
			explode = true;
			m_line.clear();

			if (explode == true && explosion >= 35.0f)
			{
				explode = false;
				shot = false;

				m_explosion.setRadius(0.0f);

				explosion = 0.0f;
			}
		}
	}
}

void Game::lineExplosion()
{
	m_explosion.setPosition(mouseClick);
	m_explosion.setFillColor(sf::Color::Red);
	m_explosion.setRadius(explosion);
	m_explosion.setOrigin(sf::Vector2f{ explosion, explosion });

	if (explosion >= 35.0f && explode == true)
	{
		explosion = false;
		explosion = 0.0f;
	}


	if (explosion < 35.0f && explode == true)
	{
		explosion += 1.0f;
	}

}

void Game::resetAltitude()
{
	altitudeBar = 0;
}

void Game::asteroidDraw()
{
	if (lineAlive == false)
	{
		lineAlive = true;
		posx = rand() % 800 + 1;
		posy = 0;

		endPointx = rand() % 800 + 1;
		endPointy = 550;

		lineEnd2 = sf::Vector2f{ endPointx, endPointy };


	}
	asteroidLocation = sf::Vector2f{ posx, posy };
	lineStart2 = sf::Vertex{ sf::Vector2f{400.0f,0.0f}, sf::Color::White };

	m_line2.clear();

	headVector2 = lineEnd2.position - lineStart2.position;
	velocity2 = headVector2 * speed;
	asteroidLocation += velocity2;
	lineEnd2.position = asteroidLocation;

	asteroid.setFillColor(sf::Color::Cyan);
	asteroid.setRadius(5.0f);

	m_line2.append(lineStart2);
	m_line2.append(lineEnd2);

}