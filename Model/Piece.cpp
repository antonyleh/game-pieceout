#include "Piece.hpp"
#include <algorithm>

bool Piece::operator==(const Piece &other) const {
    auto c1 = getCoordinatesCopy();
    auto c2 = other.getCoordinatesCopy();
    std::sort(c1.begin(), c1.end());
    std::sort(c2.begin(), c2.end());
    return (c1 == c2);
}

bool Piece::operator!=(const Piece &other) const {
    return !(*this == other);
}
