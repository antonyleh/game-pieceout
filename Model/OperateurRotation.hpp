#ifndef OPERATEURROTATION_HPP
#define OPERATEURROTATION_HPP
#include "PieceOperateur.hpp"

enum OrientationRotation { HORAIRE, ANTI_HORAIRE };

class OperateurRotation : public PieceOperateur {
public:
    OperateurRotation(Piece &src, const Position &pos, OrientationRotation sens);
    ~OperateurRotation() override = default;

    void visit(PieceConcrete &) const override;
    void visit(OperateurDeplacement &) const override;
    void visit(OperateurRotation &) const override;
    void visit(OperateurSymetrie &) const override;

    void accept(const PieceOperateur &op) override;

    void mapPosition(Position &) const override;

    Piece* clone() const override;

    OrientationRotation getSens() const;
    void setSens(OrientationRotation sens);

private:
    OrientationRotation sens;
};

#endif
