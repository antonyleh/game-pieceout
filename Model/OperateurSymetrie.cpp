#include "OperateurSymetrie.hpp"
#include "OperateurDeplacement.hpp"
#include "OperateurRotation.hpp"
#include "PieceConcrete.hpp"
#include <iostream>

OperateurSymetrie::OperateurSymetrie(Piece &src, const Position &pos, OrientationSymetrie s)
 : PieceOperateur(src, pos), sens(s)
{}

void OperateurSymetrie::visit(PieceConcrete &p) const {
    auto coords = p.getCoordinates();
    for(auto &xy : coords) {
        mapPosition(xy);
    }
    p.coordinates = coords;
}

void OperateurSymetrie::visit(OperateurDeplacement &op) const {
    OrientationDeplacement sd = op.getSens();
    if(sens == HORIZONTAL) {
        if(sd == EST) {
            op.setSens(OUEST);
        }
        else if(sd == OUEST) {
            op.setSens(EST);
        }
    }
    else { 
        if(sd == NORD) {
            op.setSens(SUD);
        }
        else if(sd == SUD) {
            op.setSens(NORD);
        }
    }
    mapPosition(op.position);
    op.source.accept(*this);
}

void OperateurSymetrie::visit(OperateurRotation &op) const {
    mapPosition(op.position);
    op.source.accept(*this);
}

void OperateurSymetrie::visit(OperateurSymetrie &op) const {
    mapPosition(op.position);
    op.source.accept(*this);
}

void OperateurSymetrie::accept(const PieceOperateur &op) {
    op.visit(*this);
}

void OperateurSymetrie::mapPosition(Position &pos) const {
    int px = position.first;
    int py = position.second;
    if(sens == HORIZONTAL) {
        int ry = pos.second - py;
        pos.second = py - ry;
    }
    else {
        int rx = pos.first - px;
        pos.first = px - rx;
    }
}

Piece* OperateurSymetrie::clone() const {
    return new OperateurSymetrie(*this);
}

OrientationSymetrie OperateurSymetrie::getSens() const {
    return sens;
}

void OperateurSymetrie::setSens(OrientationSymetrie s) {
    sens = s;
}
