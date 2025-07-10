#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class ChessPiece;

class Player {
private:
    string color;
    ChessPiece* pieces[16];
    int pieceCount;
public:
    Player(string playerColor);
    ~Player();
    void addPiece(ChessPiece* piece);
    void removePiece(ChessPiece* piece);
    string getColor() const;
};

#endif