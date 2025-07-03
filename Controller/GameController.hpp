#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "../Model/GameModel.hpp"
#include <memory>

class GameController {
public:
    explicit GameController(GameModel &m);

    void handleMousePressed(const sf::Vector2i &mousePos,
                            int marginLeft, int marginTop,
                            int tileSize);
    void handleMouseReleased(const sf::Vector2i &mousePos,
                             int marginLeft, int marginTop);
    void handleMouseMoved(const sf::Vector2i &mousePos,
                          int marginLeft, int marginTop,
                          int tileSize);

    void undo();

    std::shared_ptr<PieceConcrete> getCurrentPiece() const {
        return currentPiece;
    }
    bool getDidMove() const { return didMove; }
    sf::Vector2i getLastGridPos() const { return lastGridPos; }
    void resetDidMove() { didMove = false; }

private:
    GameModel &model; 
    std::shared_ptr<PieceConcrete> currentPiece{nullptr};
    bool mousePressed{false};
    bool didMove{false}; 
    sf::Vector2i lastGridPos{-1,-1};
};

#endif
