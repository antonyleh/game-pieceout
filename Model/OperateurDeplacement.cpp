#include "OperateurDeplacement.hpp"
#include "OperateurSymetrie.hpp"
#include "OperateurRotation.hpp"
#include "PieceConcrete.hpp"
#include <iostream>

OperateurDeplacement::OperateurDeplacement(
        Piece &src, const Position &pos, OrientationDeplacement s)
 : PieceOperateur(src, pos), sens(s)
{
}

void OperateurDeplacement::visit(PieceConcrete &p) const {
    auto coords = p.getCoordinates();
    for(auto &xy : coords) {
        mapPosition(xy);
    }
    p.coordinates = coords;
}

void OperateurDeplacement::visit(OperateurDeplacement &op) const {
    mapPosition(op.position);
    op.source.accept(*this);
}

void OperateurDeplacement::visit(OperateurRotation &op) const {
    mapPosition(op.position);
    op.source.accept(*this);
}

void OperateurDeplacement::visit(OperateurSymetrie &op) const {
    mapPosition(op.position);
    op.source.accept(*this);
}

void OperateurDeplacement::accept(const PieceOperateur &op) {
    op.visit(*this);
}

void OperateurDeplacement::mapPosition(Position &pos) const {
    switch(sens) {
        case NORD:  pos.second -= 1; break;
        case SUD:   pos.second += 1; break;
        case EST:   pos.first  += 1; break;
        case OUEST: pos.first  -= 1; break;
    }
}

Piece* OperateurDeplacement::clone() const {
    return new OperateurDeplacement(*this);
}

OrientationDeplacement OperateurDeplacement::getSens() const {
    return sens;
}

void OperateurDeplacement::setSens(OrientationDeplacement s) {
    sens = s;
}
