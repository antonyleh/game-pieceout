#include "PieceOperateur.hpp"
#include "PieceConcrete.hpp"
#include "OperateurDeplacement.hpp"
#include "OperateurRotation.hpp"
#include "OperateurSymetrie.hpp"
#include <iostream>

PieceOperateur::PieceOperateur(Piece &src, const Position &pos)
 : source(src), position(pos)
{}

PieceOperateur::~PieceOperateur() {}

void PieceOperateur::trigger(const Position &coord, Piece &origin) {
    if(coord == position) {
        origin.accept(*this);
    } else {
        source.trigger(coord, origin);
    }
}
