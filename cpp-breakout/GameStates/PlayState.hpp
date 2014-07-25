#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "../Levels//Level.hpp"
#include "../Entities/Ball.hpp"
#include "../Entities/Tile.hpp"
#include "../Entities/Paddle.hpp"
#include "../Collision/MyContactListener.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <utility>

class StateMachine;

// Score and lives are global variables, so they don't change across multiple playstates (levels).
// Will only be reset when starting a new game.
namespace GlobalVar {
    extern int score;
    extern int lives;
}

class PlayState : public GameState {
public:
    PlayState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    void createUITexts();
    void createBordersAroundScreen();
    void removeTileBodies();
    void removeTiles();
    void processEvents();
    void update(sf::Time deltaTime);
    void draw();
private:
    const float PTM_RATIO = 32.f;
    int currentLevel;
    b2World* world;
    b2Body* borderBody;
    b2MouseJointDef md;
    b2MouseJoint* m_mouseJoint;
    sf::Vector2f depth;
    sf::Font font;
    sf::Text fpsText;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Time deltaTime;
    sf::Clock fpsClock;
    sf::Time time;
    sf::Sprite tileSprite;
    sf::Vector2u windowSize;
    MyContactListener m_contactListener;
    Paddle paddle;
    Ball ball;
    Level level;
};
#endif // PLAYSTATE_HPP