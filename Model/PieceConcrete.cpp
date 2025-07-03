#include "PieceConcrete.hpp"
#include "PieceOperateur.hpp"
#include "OperateurDeplacement.hpp"
#include "OperateurRotation.hpp"
#include "OperateurSymetrie.hpp"
#include <iostream>

PieceConcrete::PieceConcrete(const std::vector<Position> &coords,
                             sf::Color c, bool hasGoal)
 : coordinates(coords),
   hasgoal(hasGoal),
   color(c),
   immovable(false),
   canRotate(false),
   hasArrows(false),
   showRotateIcon(false),
   orientation(0)
{}

void PieceConcrete::trigger(const Position &coord, Piece &origin) {

    if (coordinates.empty()) return;
    int pivotX = coordinates[0].first;
    int pivotY = coordinates[0].second;

    int dx = coord.first - pivotX;
    int dy = coord.second - pivotY;

    if(dx == -1 && dy == 0 && hasArrows) { 
        OperateurDeplacement op(*this, coord, OUEST);
        accept(op);
    }
    else if(dx == 1 && dy == 0 && hasArrows) { 
        OperateurDeplacement op(*this, coord, EST);
        accept(op);
    }
    else if(dx == 0 && dy == -1 && hasArrows) { 
        OperateurRotation op(*this, coord, HORAIRE);
        accept(op);
    }
    else if(dx == 0 && dy == 1 && hasArrows) { 
        OperateurRotation op(*this, coord, ANTI_HORAIRE);
        accept(op);
    }
    else {
    }
}

const std::vector<Position>& PieceConcrete::getCoordinates() const {
    return coordinates;
}

sf::Color PieceConcrete::getColor() const {
    return color;
}

Piece* PieceConcrete::clone() const {
    PieceConcrete *pc = new PieceConcrete(coordinates, color, hasgoal);
    pc->immovable = immovable;
    pc->canRotate = canRotate;
    pc->hasArrows = hasArrows;
    pc->showRotateIcon = showRotateIcon;
    pc->orientation = orientation;
    return pc;
}

void PieceConcrete::accept(const PieceOperateur &op) {
    op.visit(*this);
}

void PieceConcrete::setOrientation(int ori) {
    orientation = ori;
}

std::vector<Position> PieceConcrete::getCoordinatesCopy() const {
    return coordinates; 
}
