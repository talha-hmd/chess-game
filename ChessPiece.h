#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
using namespace std;

// Forward declaration of ChessBoard (needed for canMoveTo)
class ChessBoard;

// Abstract base class for all chess pieces
class ChessPiece {
protected:
    string color;
    int row, col;
public:
    ChessPiece(string pieceColor, int initialRow, int initialCol);
    virtual ~ChessPiece();

    virtual bool canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow, int enPassantCol) const = 0;

    string getColor() const;
    int getRow() const;
    int getCol() const;
    void setRow(int newRow);
    void setCol(int newCol);
    virtual char getSymbol() const = 0;
};

// Pawn class
class Pawn : public ChessPiece {
public:
    Pawn(string pieceColor, int initialRow, int initialCol);
    bool canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow, int enPassantCol) const override;
    char getSymbol() const override;
};

// Rook class
class Rook : public ChessPiece {
public:
    Rook(string pieceColor, int initialRow, int initialCol);
    bool canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow = -1, int enPassantCol = -1) const override;
    char getSymbol() const override;
};

// Knight class
class Knight : public ChessPiece {
public:
    Knight(string pieceColor, int initialRow, int initialCol);
    bool canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow = -1, int enPassantCol = -1) const override;
    char getSymbol() const override;
};

// Bishop class
class Bishop : public ChessPiece {
public:
    Bishop(string pieceColor, int initialRow, int initialCol);
    bool canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow = -1, int enPassantCol = -1) const override;
    char getSymbol() const override;
};

// Queen class
class Queen : public ChessPiece {
public:
    Queen(string pieceColor, int initialRow, int initialCol);
    bool canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow = -1, int enPassantCol = -1) const override;
    char getSymbol() const override;
};

// King class
class King : public ChessPiece {
public:
    King(string pieceColor, int initialRow, int initialCol);
    bool canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow = -1, int enPassantCol = -1) const override;
    char getSymbol() const override;
};

#endif