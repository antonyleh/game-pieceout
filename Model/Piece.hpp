#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

typedef std::pair<int, int> Position;

class Piece {
public:
    virtual ~Piece() {}

    virtual void trigger(const Position &coord, Piece &origin) = 0;

    virtual const std::vector<Position>& getCoordinates() const = 0;
    virtual sf::Color getColor() const = 0;

    virtual Piece* clone() const = 0;

    virtual void accept(const class PieceOperateur &op) = 0;
    
    virtual std::vector<Position> getCoordinatesCopy() const = 0;

    virtual bool operator==(const Piece &other) const;
    virtual bool operator!=(const Piece &other) const;
};

#endif
