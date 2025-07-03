#ifndef OPERATEURSYMETRIE_HPP
#define OPERATEURSYMETRIE_HPP

#include "PieceOperateur.hpp"

enum OrientationSymetrie { HORIZONTAL, VERTICAL };

class OperateurSymetrie : public PieceOperateur {
public:
    OperateurSymetrie(Piece &src, const Position &pos, OrientationSymetrie sens);
    ~OperateurSymetrie() override = default;

    void visit(PieceConcrete &) const override;
    void visit(OperateurDeplacement &) const override;
    void visit(OperateurRotation &) const override;
    void visit(OperateurSymetrie &) const override;

    void accept(const PieceOperateur &op) override;

    void mapPosition(Position &) const override;

    Piece* clone() const override;

    OrientationSymetrie getSens() const;
    void setSens(OrientationSymetrie sens);

private:
    OrientationSymetrie sens; 
};

#endif
