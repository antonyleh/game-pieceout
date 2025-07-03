#ifndef PIECECONCRETE_HPP
#define PIECECONCRETE_HPP

#include "Piece.hpp"
#include "PieceOperateur.hpp"

class PieceConcrete : public Piece {
public:
    PieceConcrete(const std::vector<Position> &coords, sf::Color c, bool hasGoal);
    
    void trigger(const Position &coord, Piece &origin) override;
    const std::vector<Position>& getCoordinates() const override;
    sf::Color getColor() const override;
    Piece* clone() const override;
    void accept(const PieceOperateur &op) override;
    
    void setOrientation(int ori);
    
    friend class OperateurRotation;

    protected:
    std::vector<Position> getCoordinatesCopy() const override;

public:
    std::vector<Position> coordinates; 
    bool hasgoal;                      
    sf::Color color;                   
    bool immovable;                   
    bool canRotate;      
    bool hasArrows;             
    bool showRotateIcon;          
    int orientation;                  
};

#endif
