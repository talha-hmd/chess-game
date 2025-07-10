#ifndef PIECEMOVE_H
#define PIECEMOVE_H

class ChessPiece;
class ChessBoard;

class PieceMove {
public:
    int startRow, startCol, endRow, endCol;
    ChessPiece* pieceMoved;
    ChessPiece* pieceCaptured;

    PieceMove(int sR, int sC, int eR, int eC, ChessPiece* p);
    bool isLegal(const ChessBoard& board) const;
};

#endif