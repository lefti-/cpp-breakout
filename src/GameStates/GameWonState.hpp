/*
    This software uses The MIT License (MIT). See license agreement LICENSE for full details.
*/


#ifndef GAMEWONSTATE_HPP
#define GAMEWONSTATE_HPP

#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "../MenuButtons/TextButton.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class StateMachine;

namespace sf {
    class RenderWindow;
}

class GameWonState : public GameState {
public:
    GameWonState(int levelNumber, StateMachine& machine, sf::RenderWindow& window, bool replace = true);
    void checkHighscore();
    void processEvents();
    void update(sf::Time deltaTime);
    void draw();
private:
    int alphaCounter = 0;
    sf::RectangleShape introFader;
    sf::Color introAlpha;
    TextButton congratulations;
    TextButton completed;
    TextButton OK;
};
#endif