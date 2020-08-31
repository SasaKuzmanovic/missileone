/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// 
/// project comment in main.cpp
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	int altitudeBar = 0;
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void squareSetup(); // setting up the square at the middle of the screen
	void groundSetup();
	void altitudeBarSetup();
	void altitudeBarLoading();
	void processMouseClick(sf::Event t_bestEvent);
	void processMousePress(sf::Event t_bestEvent);
	void laser();
	void lineExplosion();
	float explosion = 0;
	
	bool explode = false;
	bool shot = false;
	float speed = 4.0f;
	sf::Vector2f headVector;
	sf::Vector2f velocity;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	sf::RectangleShape square; // square at the bottom middle of the screen
	sf::RectangleShape rectangle; // rectangle acting as a ground in the game
	sf::RectangleShape altitude; // acts as a altitude bar
	sf::Vertex lineStart;
	sf::Vertex lineEnd;
	sf::Vector2f mouseClick{ 0.0f, 0.0f };
	bool m_exitGame; // control exiting game


};

#endif // !GAME_HPP

