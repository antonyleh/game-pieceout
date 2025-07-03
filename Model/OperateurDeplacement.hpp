#ifndef OPERATEURDEPLACEMENT_HPP
#define OPERATEURDEPLACEMENT_HPP

#include "PieceOperateur.hpp"
#include <iostream>

enum OrientationDeplacement { NORD, SUD, EST, OUEST };

class OperateurDeplacement : public PieceOperateur {
public:
    OperateurDeplacement(Piece &src, const Position &pos, OrientationDeplacement sens);
    ~OperateurDeplacement() override = default;

    void visit(PieceConcrete &) const override;
    void visit(OperateurDeplacement &) const override;
    void visit(OperateurRotation &) const override;
    void visit(OperateurSymetrie &) const override;

    void accept(const PieceOperateur &op) override;

    void mapPosition(Position &) const override;

    Piece* clone() const override;

    OrientationDeplacement getSens() const;
    void setSens(OrientationDeplacement sens);

private:
    OrientationDeplacement sens;
};

#endif
