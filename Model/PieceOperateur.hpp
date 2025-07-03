#ifndef PIECEOPERATEUR_HPP
#define PIECEOPERATEUR_HPP
#include "Piece.hpp"


class PieceConcrete;
class OperateurDeplacement;
class OperateurRotation;
class OperateurSymetrie;

class PieceOperateur : public Piece {
public:
    PieceOperateur(Piece &src, const Position &pos);
    virtual ~PieceOperateur();

    void trigger(const Position &coord, Piece &origin) override;

    const std::vector<Position>& getCoordinates() const override {
        return source.getCoordinates();
    }
    sf::Color getColor() const override { return source.getColor(); }

    virtual Piece* clone() const override = 0;

    virtual void accept(const PieceOperateur &op) override {}

    virtual void visit(PieceConcrete &) const = 0;
    virtual void visit(OperateurDeplacement &) const = 0;
    virtual void visit(OperateurRotation &) const = 0;
    virtual void visit(OperateurSymetrie &) const = 0;

protected:
    virtual std::vector<Position> getCoordinatesCopy() const override {
        return source.getCoordinatesCopy();
    }
    
    virtual void mapPosition(Position &) const = 0;

public:
    Piece &source;   
    Position position; 
};

#endif
