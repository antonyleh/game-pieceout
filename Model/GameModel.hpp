#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "Piece.hpp"
#include "PieceConcrete.hpp"
#include <vector>
#include <memory>

struct PieceState {
    std::vector<Position> coords;
    int orientation;
};

class GameModel {
public:
    GameModel();

    void clear(); 
    void addPiece(const std::shared_ptr<PieceConcrete> &p);
    const std::vector<std::shared_ptr<Piece>>& getPieces() const;
    std::vector<std::shared_ptr<Piece>>& getPieces();

    
    int getLevelNumber() const;
    void setLevelNumber(int lvl);

    
    void pushState();
    void popState();

    
    std::shared_ptr<PieceConcrete> getPieceAt(int x, int y);
    bool isColliding(const std::vector<Position> &coords,
                    std::shared_ptr<PieceConcrete> pieceMoving);
    void triggerPiece(int x, int y);

    
    void movePiece(std::shared_ptr<PieceConcrete> piece,
                  int dx, int dy);
    bool rotatePiece(std::shared_ptr<PieceConcrete> piece);

    
    bool isTileWalkable(int x, int y);

    
    void initLevel1();
    void initLevel2();
    void initLevel3();
    void initLevel4();

private:
    int levelNumber; 
    std::vector<std::shared_ptr<Piece>> pieces; 
    std::vector<std::vector<PieceState>> history; 
};

#endif
