#include "OperateurRotation.hpp"
#include "OperateurDeplacement.hpp"
#include "OperateurSymetrie.hpp"
#include "PieceConcrete.hpp"
#include <iostream>

OperateurRotation::OperateurRotation(Piece &src, const Position &pos, OrientationRotation s)
 : PieceOperateur(src, pos), sens(s)
{
}

void OperateurRotation::visit(PieceConcrete &p) const {
    auto coords = p.getCoordinates();
    for(auto &pos : coords) {
        mapPosition(pos);
    }
    p.coordinates = coords;

    if(p.orientation == 0) {
        p.setOrientation(1);
    }
    else if(p.orientation == 1) {
        p.setOrientation(0);
    }
    else if(p.orientation == 2) {
    }
}

void OperateurRotation::visit(OperateurDeplacement &op) const {
    mapPosition(op.position);
    op.source.accept(*this);
}

void OperateurRotation::visit(OperateurRotation &op) const {
    mapPosition(op.position);
    op.source.accept(*this);
}

void OperateurRotation::visit(OperateurSymetrie &op) const {

    mapPosition(op.position);
    op.source.accept(*this);
}

void OperateurRotation::accept(const PieceOperateur &op) {
    op.visit(*this);
}

void OperateurRotation::mapPosition(Position &pos) const {
    int px = position.first;
    int py = position.second;
    int rx = pos.first - px;
    int ry = pos.second - py;

    if(sens == HORAIRE) {
        // rotation horaire: (x, y) = (y, -x)
        int nx = px + ry;
        int ny = py - rx;
        pos.first = nx;
        pos.second = ny;
    }
    else {
        // rotation anti-horaire: (x, y) = (-y, x)
        int nx = px - ry;
        int ny = py + rx;
        pos.first = nx;
        pos.second = ny;
    }
}

Piece* OperateurRotation::clone() const {
    return new OperateurRotation(*this);
}

OrientationRotation OperateurRotation::getSens() const {
    return sens;
}

void OperateurRotation::setSens(OrientationRotation s) {
    sens = s;
        
}
