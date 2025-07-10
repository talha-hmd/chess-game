#ifndef GAME_H
#define GAME_H

#include <string>
using namespace std;

class ChessBoard;
class Player;

class Game {
private:
    ChessBoard board;
    Player white;
    Player black;
    string currentTurn; // "White" or "Black"
    int enPassantRow = -1;
    int enPassantCol = -1;

public:
    Game();
    int getEnPassantRow() const { return enPassantRow; }
    int getEnPassantCol() const { return enPassantCol; }
    void displayBoard();
    bool makeMove(int startRow, int startCol, int endRow, int endCol);
    ChessBoard& getBoard() { return board; }
    const ChessBoard& getBoard() const { return board; }
    string getCurrentTurn() const;
    bool hasAnyLegalMove(string color);
    bool isKingInCheck(string color);
    bool canCastle(string color, int row, int kingCol, int targetCol);
};

#endif 