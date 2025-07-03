#include "GameController.hpp"
#include <cmath>
#include <iostream>

GameController::GameController(GameModel &m)
  : model(m)
{}

void GameController::handleMousePressed(
        const sf::Vector2i &mousePos,
        int marginLeft, int marginTop,
        int tileSize)
{
    mousePressed = true;
    didMove = false;
    int gx = (mousePos.x - marginLeft) / tileSize;
    int gy = (mousePos.y - marginTop) / tileSize;
    currentPiece = model.getPieceAt(gx, gy);
    lastGridPos = sf::Vector2i(gx, gy);
}

void GameController::handleMouseReleased(const sf::Vector2i &mousePos, int marginLeft, int marginTop) {
    mousePressed = false;

    float mxUI = static_cast<float>(mousePos.x);
    float myUI = static_cast<float>(mousePos.y);
    if (mxUI >= 10.f && mxUI <= 70.f && myUI >= 555.f && myUI <= 585.f) {
        model.popState();
        currentPiece = nullptr;
        return;
    }

    if (currentPiece && !didMove) {
        if (!currentPiece->coordinates.empty()) {
            auto pivot = currentPiece->coordinates[0];
            if (pivot.first == lastGridPos.x && pivot.second == lastGridPos.y) {
                if (model.rotatePiece(currentPiece)) {
                } else {
                }
            }
        }
    }

    currentPiece = nullptr;
    lastGridPos = sf::Vector2i(-1, -1);
}

void GameController::handleMouseMoved(const sf::Vector2i &mousePos, int marginLeft, int marginTop, int tileSize) {
    if (!mousePressed || !currentPiece) return;

    int gx = (mousePos.x - marginLeft) / tileSize;
    int gy = (mousePos.y - marginTop) / tileSize;

    if (gx != lastGridPos.x || gy != lastGridPos.y) {
        didMove = true;

        int dx = gx - lastGridPos.x;
        int dy = gy - lastGridPos.y;

        switch (currentPiece->orientation) {
            case 0: 
                if (std::abs(dx) >= std::abs(dy)) {
                    dx = (dx > 0) ? 1 : -1;
                    dy = 0;
                } else {
                    dx = 0;
                    dy = 0;
                }
                break;
            case 1: 
                if (std::abs(dy) >= std::abs(dx)) {
                    dy = (dy > 0) ? 1 : -1;
                    dx = 0;
                } else {
                    dx = 0;
                    dy = 0;
                }
                break;
            case 2: 
                if (std::abs(dx) > std::abs(dy)) {
                    dx = (dx > 0) ? 1 : -1;
                    dy = 0;
                } else {
                    dy = (dy > 0) ? 1 : -1;
                    dx = 0;
                }
                break;
        }

        if (dx != 0 || dy != 0) {
            model.movePiece(currentPiece, dx, dy);
            lastGridPos.x += dx;
            lastGridPos.y += dy;
        }
    }
}


void GameController::undo() {
    model.popState();
}
