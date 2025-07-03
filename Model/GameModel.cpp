#include "GameModel.hpp"
#include "OperateurRotation.hpp"
#include <algorithm>
#include <iostream>

GameModel::GameModel() : levelNumber(0) {
}

void GameModel::clear() { 
    pieces.clear(); 
}

void GameModel::addPiece(const std::shared_ptr<PieceConcrete> &p) {
    pieces.push_back(p);
}

const std::vector<std::shared_ptr<Piece>>& GameModel::getPieces() const {
    return pieces;
}

std::vector<std::shared_ptr<Piece>>& GameModel::getPieces() {
    return pieces;
}

int GameModel::getLevelNumber() const { return levelNumber; }

void GameModel::setLevelNumber(int lvl) { 
    levelNumber = lvl; 
}

void GameModel::pushState() {
    std::vector<PieceState> st;
    for(auto &p : pieces) {
        auto pc = std::dynamic_pointer_cast<PieceConcrete>(p);
        if(pc) {
            st.emplace_back(PieceState{ pc->coordinates, pc->orientation });
        }
    }
    history.push_back(st);
}

void GameModel::popState() {

    if(history.size() < 2) {
        return;
    }
    history.pop_back();
    auto &top = history.back();
    if(top.size() == pieces.size()) {
        for(size_t i = 0; i < top.size(); i++) {
            auto pc = std::dynamic_pointer_cast<PieceConcrete>(pieces[i]);
            if(pc) {
                pc->coordinates = top[i].coords;
                pc->orientation = top[i].orientation;
            }
        }
    }
}

std::shared_ptr<PieceConcrete> GameModel::getPieceAt(int x, int y) {
    for(auto &pp : pieces) {
        auto pc = std::dynamic_pointer_cast<PieceConcrete>(pp);
        if(!pc) continue;
        for(auto &c : pc->coordinates) {
            if(c.first == x && c.second == y) {
                return pc;
            }
        }
    }
    return nullptr;
}

bool GameModel::isColliding(const std::vector<Position> &coords,
                            std::shared_ptr<PieceConcrete> pieceMoving) {
    for(auto &p : pieces) {
        auto pc = std::dynamic_pointer_cast<PieceConcrete>(p);
        if(!pc || pc == pieceMoving) continue;
        for(auto &c1 : coords) {
            for(auto &c2 : pc->coordinates) {
                if(c1 == c2) {
                
                    return true;
                }
            }
        }
    }
    return false;
}

void GameModel::triggerPiece(int x, int y) {
    auto piece = getPieceAt(x, y);
    if(piece) {
        piece->trigger({x, y}, *piece);
        pushState();
    }
}

void GameModel::movePiece(std::shared_ptr<PieceConcrete> piece, int dx, int dy) {
    if (!piece || piece->immovable) return;

    auto oldCoords = piece->coordinates; 
    std::vector<Position> newCoords;

    for (auto &coord : oldCoords) {
        Position newCoord = {coord.first + dx, coord.second + dy};
        newCoords.push_back(newCoord);
    }

    for (auto &coord : newCoords) {
        if (!isTileWalkable(coord.first, coord.second) || isColliding(newCoords, piece)) {
            return;
        }
    }

    piece->coordinates = newCoords;
    pushState();
}


bool GameModel::rotatePiece(std::shared_ptr<PieceConcrete> piece) {
    if (!piece || !piece->canRotate) return false;

    auto oldCoords = piece->coordinates; 
    int oldOrientation = piece->orientation;

    OperateurRotation op(*piece, oldCoords[0], HORAIRE);
    piece->accept(op);

    for (auto &coord : piece->coordinates) {
        if (!isTileWalkable(coord.first, coord.second)) {
            
            piece->coordinates = oldCoords;
            piece->orientation = oldOrientation;
            return false;
        }
    }

    if (isColliding(piece->coordinates, piece)) {
        piece->coordinates = oldCoords;
        piece->orientation = oldOrientation;
        return false;
    }

    if (piece->coordinates != oldCoords || piece->orientation != oldOrientation) {
        pushState();
    }
    return true;
}


bool GameModel::isTileWalkable(int x, int y) {
   
    if(levelNumber == 1) {
        if(y != 0) return false;
        if(x < 0 || x > 5) return false;
        return true;
    }
    else if(levelNumber == 2) {
        if(x < 0 || x > 4 || y < 0 || y > 4) return false;
        return (x == 2 || y == 2);
    }
    else if(levelNumber == 3) {
        if(x < 0 || x > 2 || y < 0 || y > 6) return false;
        if((x == 0 && y == 3)
           || (x == 1 && (y == 2 || y == 3 || y == 4))
           || (x == 2 && (y >= 0 && y <= 6))) {
            return true;
        }
        return false;
    }
    else if(levelNumber == 4) {
        if(x < 0 || x > 2 || y < 0 || y > 6) return false;
        if((x == 0 && (y == 2 || y == 3))
           || (x == 1 && (y >= 0 && y <= 6))
           || (x == 2 && (y >= 2 && y <= 4))) {
            return true;
        }
        return false;
    }
    return false;
}

void GameModel::initLevel1() {
    clear();
    setLevelNumber(1);
    auto red = std::make_shared<PieceConcrete>(
                   std::vector<Position>{{0,0}},
                   sf::Color::Red, false);
    red->immovable = false; 
    red->canRotate = false;
    red->hasArrows = true; 
    red->orientation = 0;
    addPiece(red);
    history.clear(); 
    pushState();
}

void GameModel::initLevel2() {
    clear();
    setLevelNumber(2);
    auto red = std::make_shared<PieceConcrete>(
                    std::vector<Position>{{2,4}},
                    sf::Color::Red, false);
    red->immovable = false; 
    red->canRotate = false;
    red->hasArrows = true; 
    red->orientation = 1;
    addPiece(red);

    auto blue = std::make_shared<PieceConcrete>(
                    std::vector<Position>{{2,2},{3,2}},
                    sf::Color::Blue, false);
    blue->immovable = false; 
    blue->canRotate = false;
    blue->hasArrows = true; 
    blue->orientation = 0;
    addPiece(blue);
    history.clear(); 
    pushState();
}

void GameModel::initLevel3() {
    clear();
    setLevelNumber(3);
    auto red = std::make_shared<PieceConcrete>(
                   std::vector<Position>{{2,6}},
                   sf::Color::Red, false);
    red->immovable = false; 
    red->canRotate = false;
    red->hasArrows = true; 
    red->orientation = 1;
    addPiece(red);

    auto green = std::make_shared<PieceConcrete>(
                     std::vector<Position>{{1,3},{1,2},{2,3},{1,4}},
                     sf::Color::Green, false);
    green->immovable = true; 
    green->canRotate = true;
    green->hasArrows = false; 
    green->showRotateIcon = true;
    addPiece(green);
    history.clear(); 
    pushState();
}

void GameModel::initLevel4() {
    clear();
    setLevelNumber(4);
    auto red = std::make_shared<PieceConcrete>(
                   std::vector<Position>{{1,6}},
                   sf::Color::Red, false);
    red->immovable = false; 
    red->canRotate = false;
    red->hasArrows = true; 
    red->orientation = 2;
    addPiece(red);

    auto purple = std::make_shared<PieceConcrete>(
                     std::vector<Position>{{1,3},{0,3},{2,3},{2,2}},
                     sf::Color(128,0,128), false);
    purple->immovable = false; 
    purple->canRotate = true;
    purple->hasArrows = true; 
    purple->showRotateIcon = true;
    purple->orientation = 0;
    addPiece(purple);

    history.clear(); 
    pushState();
}
