#ifndef CHESSBOARD_H
#define CHESSBOARD_H

// Forward declaration for chess piece...
class ChessPiece;

class ChessBoard {
private:
    ChessPiece* board[8][8];

public:
    ChessBoard();
    ChessPiece* getPiece(int row, int col) const;
    void setPiece(int row, int col, ChessPiece* piece);
    void clearPiece(int row, int col);
    void display() const; // Declaration only bcz defined in ChessGame.cpp
};

#endif