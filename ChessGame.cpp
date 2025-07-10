#include <iostream>
#include <cmath>
#include "ChessPiece.h"
#include "ChessBoard.h"
#include "PieceMove.h"
#include "Player.h"
#include "Game.h"
using namespace std;

// ChessPiece method definitionsss
ChessPiece::ChessPiece(string pieceColor, int initialRow, int initialCol)
    : color(pieceColor), row(initialRow), col(initialCol) {
}

ChessPiece::~ChessPiece() {}

string ChessPiece::getColor() const { return color; }
int ChessPiece::getRow() const { return row; }
int ChessPiece::getCol() const { return col; }
void ChessPiece::setRow(int newRow) { row = newRow; }
void ChessPiece::setCol(int newCol) { col = newCol; }

// Pawn method definitions
Pawn::Pawn(string pieceColor, int initialRow, int initialCol)
    : ChessPiece(pieceColor, initialRow, initialCol) {
}

bool Pawn::canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow, int enPassantCol) const {
    int direction = (color == "White") ? 1 : -1;
    int startRow = (color == "White") ? 1 : 6;

    if (newCol == col) {
        if (newRow == row + direction && board.getPiece(newRow, newCol) == nullptr) {
            return true;
        }
        if (row == startRow && newRow == row + 2 * direction &&
            board.getPiece(row + direction, col) == nullptr &&
            board.getPiece(newRow, newCol) == nullptr) {
            return true;
        }
    }
    if (abs(newCol - col) == 1 && newRow == row + direction) {
        ChessPiece* target = board.getPiece(newRow, newCol);
        if (target != nullptr && target->getColor() != color) {
            return true;
        }
    }

    // En Passant special capture
    if (abs(newCol - col) == 1 && newRow == row + direction) {
        if (board.getPiece(newRow, newCol) == nullptr) { // MUAST be an empty square
            // Check if enPassant is available..
            if (newRow == enPassantRow && newCol == enPassantCol) {
                return true;
            }
        }
    }

    return false;
}


char Pawn::getSymbol() const { return color == "White" ? 'P' : 'p'; }

// Rook method definitions
Rook::Rook(string pieceColor, int initialRow, int initialCol)
    : ChessPiece(pieceColor, initialRow, initialCol) {
}

bool Rook::canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow, int enPassantCol) const {
    if (newRow == row && newCol != col) {
        int step = (newCol > col) ? 1 : -1;
        for (int c = col + step; c != newCol; c += step) {
            if (board.getPiece(row, c) != nullptr) return false;
        }
        ChessPiece* target = board.getPiece(newRow, newCol);
        return target == nullptr || target->getColor() != color;
    }
    else if (newCol == col && newRow != row) {
        int step = (newRow > row) ? 1 : -1;
        for (int r = row + step; r != newRow; r += step) {
            if (board.getPiece(r, col) != nullptr) return false;
        }
        ChessPiece* target = board.getPiece(newRow, newCol);
        return target == nullptr || target->getColor() != color;
    }
    return false;
}

char Rook::getSymbol() const { return color == "White" ? 'R' : 'r'; }

// Knight method definitions
Knight::Knight(string pieceColor, int initialRow, int initialCol)
    : ChessPiece(pieceColor, initialRow, initialCol) {
}

bool Knight::canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow, int enPassantCol) const {
    int rowDiff = abs(newRow - row);
    int colDiff = abs(newCol - col);
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        ChessPiece* target = board.getPiece(newRow, newCol);
        return target == nullptr || target->getColor() != color;
    }
    return false;
}

char Knight::getSymbol() const { return color == "White" ? 'N' : 'n'; }

// Bishop method definitions
Bishop::Bishop(string pieceColor, int initialRow, int initialCol)
    : ChessPiece(pieceColor, initialRow, initialCol) {
}

bool Bishop::canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow, int enPassantCol) const {
    int rowDiff = newRow - row;
    int colDiff = newCol - col;
    if (abs(rowDiff) == abs(colDiff) && rowDiff != 0) {
        int rowStep = (rowDiff > 0) ? 1 : -1;
        int colStep = (colDiff > 0) ? 1 : -1;
        int r = row + rowStep;
        int c = col + colStep;
        while (r != newRow && c != newCol) {
            if (board.getPiece(r, c) != nullptr) return false;
            r += rowStep;
            c += colStep;
        }
        ChessPiece* target = board.getPiece(newRow, newCol);
        return target == nullptr || target->getColor() != color;
    }
    return false;
}

char Bishop::getSymbol() const { return color == "White" ? 'B' : 'b'; }

// Queen method definitions
Queen::Queen(string pieceColor, int initialRow, int initialCol)
    : ChessPiece(pieceColor, initialRow, initialCol) {
}

bool Queen::canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow, int enPassantCol) const {
    int rowDiff = newRow - row;
    int colDiff = newCol - col;
    if (newRow == row || newCol == col || abs(rowDiff) == abs(colDiff)) {
        int rowStep = (rowDiff == 0) ? 0 : (rowDiff > 0 ? 1 : -1);
        int colStep = (colDiff == 0) ? 0 : (colDiff > 0 ? 1 : -1);
        int r = row + rowStep;
        int c = col + colStep;
        while (r != newRow || c != newCol) {
            if (board.getPiece(r, c) != nullptr) return false;
            r += rowStep;
            c += colStep;
        }
        ChessPiece* target = board.getPiece(newRow, newCol);
        return target == nullptr || target->getColor() != color;
    }
    return false;
}

char Queen::getSymbol() const { return color == "White" ? 'Q' : 'q'; }

// King method definitions
King::King(string pieceColor, int initialRow, int initialCol)
    : ChessPiece(pieceColor, initialRow, initialCol) {
}

bool King::canMoveTo(int newRow, int newCol, const ChessBoard& board, int enPassantRow, int enPassantCol) const {
    int rowDiff = abs(newRow - row);
    int colDiff = abs(newCol - col);
    if (rowDiff <= 1 && colDiff <= 1 && (rowDiff + colDiff > 0)) {
        ChessPiece* target = board.getPiece(newRow, newCol);
        return target == nullptr || target->getColor() != color;
    }
    return false;
}

char King::getSymbol() const { return color == "White" ? 'K' : 'k'; }

// ChessBoard method definitions
ChessBoard::ChessBoard() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            board[r][c] = nullptr;
        }
    }
}

ChessPiece* ChessBoard::getPiece(int row, int col) const {
    return (row >= 0 && row < 8 && col >= 0 && col < 8) ? board[row][col] : nullptr;
}

void ChessBoard::setPiece(int row, int col, ChessPiece* piece) {
    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
        board[row][col] = piece;
        if (piece) {
            piece->setRow(row);
            piece->setCol(col);
        }
    }
}

void ChessBoard::clearPiece(int row, int col) {
    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
        board[row][col] = nullptr;
    }
}

// Setting up board
void ChessBoard::display() const {
    cout << "\n+-----------------+\n";
    for (int r = 7; r >= 0; r--) {
        cout << "| ";
        for (int c = 0; c < 8; c++) {
            ChessPiece* piece = board[r][c];
            if (piece == nullptr) {
                cout << ". ";
            }
            else {
                char sym = piece->getSymbol();
                if (islower(sym))
                    cout << "\033[31m" << sym << "\033[0m ";
                else
                    cout << "\033[93m" << sym << "\033[0m ";
            }
        }
        cout << "| " << (r + 1) << "\n";
    }
    cout << "+-----------------+\n";
    cout << "  a b c d e f g h\n\n";
}

// PieceMove method definitions
PieceMove::PieceMove(int sR, int sC, int eR, int eC, ChessPiece* p)
    : startRow(sR), startCol(sC), endRow(eR), endCol(eC), pieceMoved(p), pieceCaptured(nullptr) {
}

bool PieceMove::isLegal(const ChessBoard& board) const {
    if (board.getPiece(startRow, startCol) != pieceMoved) {
        return false;
    }
    return pieceMoved->canMoveTo(endRow, endCol, board, -1, -1);
}

// Player method definitions
Player::Player(string playerColor) : color(playerColor), pieceCount(0) {
    for (int i = 0; i < 16; i++) pieces[i] = nullptr;
}

Player::~Player() {
    for (int i = 0; i < 16; i++) delete pieces[i];
}

void Player::addPiece(ChessPiece* piece) {
    if (pieceCount < 16) pieces[pieceCount++] = piece;
}

void Player::removePiece(ChessPiece* piece) {
    for (int i = 0; i < pieceCount; i++) {
        if (pieces[i] == piece) {
            delete pieces[i];
            pieces[i] = pieces[--pieceCount];
            pieces[pieceCount] = nullptr;
            break;
        }
    }
}

string Player::getColor() const { return color; }

// Game method definitions
Game::Game() : white("White"), black("Black"), currentTurn("White") {
    // White pieces setup
    for (int col = 0; col < 8; col++) {
        Pawn* whitePawn = new Pawn("White", 1, col);
        white.addPiece(whitePawn);
        board.setPiece(1, col, whitePawn);
    }

    // Doing this so I can remember positions while coding

    /* POSITIONS [WHITE]:
    - pawnA: row 1, col 0, a2
    - pawnB: row 1, col 1, b2
    - pawnC: row 1, col 2, c2
    - pawnD: row 1, col 3, d2
    - pawnE: row 1, col 4, e2
    - pawnF: row 1, col 5, f2
    - pawnG: row 1, col 6, g2
    - pawnH: row 1, col 7, h2
    - rookLeft: row 0, col 0, a1
    - rookRight: row 0, col 7, h1
    - knightLeft: row 0, col 1, b1
    - knightRight: row 0, col 6, g1
    - bishopLeft: row 0, col 2, c1
    - bishopRight: row 0, col 5, f1
    - queen: row 0, col 3, d1
    - king: row 0, col 4, e1
    */

    Rook* whiteRookLeft = new Rook("White", 0, 0);
    Rook* whiteRookRight = new Rook("White", 0, 7);
    Knight* whiteKnightLeft = new Knight("White", 0, 1);
    Knight* whiteKnightRight = new Knight("White", 0, 6);
    Bishop* whiteBishopLeft = new Bishop("White", 0, 2);
    Bishop* whiteBishopRight = new Bishop("White", 0, 5);
    Queen* whiteQueen = new Queen("White", 0, 3);
    King* whiteKing = new King("White", 0, 4);
    white.addPiece(whiteRookLeft);
    white.addPiece(whiteRookRight);
    white.addPiece(whiteKnightLeft);
    white.addPiece(whiteKnightRight);
    white.addPiece(whiteBishopLeft);
    white.addPiece(whiteBishopRight);
    white.addPiece(whiteQueen);
    white.addPiece(whiteKing);
    board.setPiece(0, 0, whiteRookLeft);
    board.setPiece(0, 7, whiteRookRight);
    board.setPiece(0, 1, whiteKnightLeft);
    board.setPiece(0, 6, whiteKnightRight);
    board.setPiece(0, 2, whiteBishopLeft);
    board.setPiece(0, 5, whiteBishopRight);
    board.setPiece(0, 3, whiteQueen);
    board.setPiece(0, 4, whiteKing);

    // Black pieces setup
    for (int col = 0; col < 8; col++) {
        Pawn* blackPawn = new Pawn("Black", 6, col);
        black.addPiece(blackPawn);
        board.setPiece(6, col, blackPawn);
    }

    /* POSITIONS [BLACK]:
    - pawnA: row 6, col 0, a7
    - pawnB: row 6, col 1, b7
    - pawnC: row 6, col 2, c7
    - pawnD: row 6, col 3, d7
    - pawnE: row 6, col 4, e7
    - pawnF: row 6, col 5, f7
    - pawnG: row 6, col 6, g7
    - pawnH: row 6, col 7, h7
    - rookLeft: row 7, col 0, a8
    - rookRight: row 7, col 7, h8
    - knightLeft: row 7, col 1, b8
    - knightRight: row 7, col 6, g8
    - bishopLeft: row 7, col 2, c8
    - bishopRight: row 7, col 5, f8
    - queen: row 7, col 3, d8
    - king: row 7, col 4, e8
    */

    Rook* blackRookLeft = new Rook("Black", 7, 0);
    Rook* blackRookRight = new Rook("Black", 7, 7);
    Knight* blackKnightLeft = new Knight("Black", 7, 1);
    Knight* blackKnightRight = new Knight("Black", 7, 6);
    Bishop* blackBishopLeft = new Bishop("Black", 7, 2);
    Bishop* blackBishopRight = new Bishop("Black", 7, 5);
    Queen* blackQueen = new Queen("Black", 7, 3);
    King* blackKing = new King("Black", 7, 4);
    black.addPiece(blackRookLeft);
    black.addPiece(blackRookRight);
    black.addPiece(blackKnightLeft);
    black.addPiece(blackKnightRight);
    black.addPiece(blackBishopLeft);
    black.addPiece(blackBishopRight);
    black.addPiece(blackQueen);
    black.addPiece(blackKing);
    board.setPiece(7, 0, blackRookLeft);
    board.setPiece(7, 7, blackRookRight);
    board.setPiece(7, 1, blackKnightLeft);
    board.setPiece(7, 6, blackKnightRight);
    board.setPiece(7, 2, blackBishopLeft);
    board.setPiece(7, 5, blackBishopRight);
    board.setPiece(7, 3, blackQueen);
    board.setPiece(7, 4, blackKing);
}

void Game::displayBoard() {
    board.display();
}

bool Game::makeMove(int startRow, int startCol, int endRow, int endCol) {
    // Check if starting coordinates are valid
    if (startRow < 0 || startRow > 7 || startCol < 0 || startCol > 7 || endRow < 0 || endRow > 7 || endCol < 0 || endCol > 7) {
        cout << "Error: Move out of board bounds!" << endl;
        return false;
    }

    ChessPiece* piece = board.getPiece(startRow, startCol);

    /* --------------------- CASTLING ---------------------- */
    // Special handling if King trying to castle
    if (piece != nullptr && ((piece->getSymbol() == 'K' && currentTurn == "White") || (piece->getSymbol() == 'k' && currentTurn == "Black"))) {
        if (abs(startCol - endCol) == 2 && startRow == endRow) {
            // King is trying to castle
            if (canCastle(currentTurn, startRow, startCol, endCol)) {
                // Move the King
                board.setPiece(endRow, endCol, piece);
                board.clearPiece(startRow, startCol);
                piece->setRow(endRow);
                piece->setCol(endCol);

                // Move the corresponding Rook
                if (endCol == 6) { // Kingside's castling
                    ChessPiece* rook = board.getPiece(startRow, 7);
                    board.setPiece(startRow, 5, rook);
                    board.clearPiece(startRow, 7);
                    rook->setRow(startRow);
                    rook->setCol(5);
                }
                else if (endCol == 2) { // Queenside's castling
                    ChessPiece* rook = board.getPiece(startRow, 0);
                    board.setPiece(startRow, 3, rook);
                    board.clearPiece(startRow, 0);
                    rook->setRow(startRow);
                    rook->setCol(3);
                }

                // After castling move is done
                // Switch turn
                currentTurn = (currentTurn == "White") ? "Black" : "White";

                // Check for check/checkmate/stalemate after castling
                if (isKingInCheck(currentTurn)) {
                    cout << "Check on " << currentTurn << " King!" << endl;
                }
                if (isKingInCheck(currentTurn) && !hasAnyLegalMove(currentTurn)) {
                    cout << "Checkmate! " << (currentTurn == "White" ? "Black" : "White") << " wins!" << endl;
                    exit(0);
                }
                else if (!isKingInCheck(currentTurn) && !hasAnyLegalMove(currentTurn)) {
                    cout << "Stalemate! It's a draw!" << endl;
                    exit(0);
                }

                return true;
            }
            else {
                cout << "Invalid Castling move!" << endl;
                return false;
            }
        }
    }

    // VALIDATIONS
  
    // Check if there's a piece at start position
    if (piece == nullptr) {
        cout << "Error: No piece at selected starting position!" << endl;
        return false;
    }

    // Check if piece belongs to current player
    if (piece->getColor() != currentTurn) {
        cout << "Error: You can only move your own pieces!" << endl;
        return false;
    }

    // Check if move is legal according to piece's rules
    if (!piece->canMoveTo(endRow, endCol, board, enPassantRow, enPassantCol)) {
        cout << "Error: Illegal move for this piece!" << endl;
        return false;
    }

    // Check if capturing own piece
    ChessPiece* target = board.getPiece(endRow, endCol);
    if (target != nullptr && target->getColor() == currentTurn) {
        cout << "Error: Cannot capture your own piece!" << endl;
        return false;
    }

    // Move is valid so perform the move
    if (target != nullptr) {
        if (target->getColor() == "White") {
            white.removePiece(target);
        }
        else {
            black.removePiece(target);
        }
    }

    // SIMULATE the move temporarily
    ChessPiece* captured = board.getPiece(endRow, endCol);
    board.setPiece(endRow, endCol, piece);
    board.clearPiece(startRow, startCol);
    piece->setRow(endRow);
    piece->setCol(endCol);

    // CHECK if king is still in check
    bool kingStillInCheck = isKingInCheck(currentTurn);

    // UNDO the move
    board.setPiece(startRow, startCol, piece);
    board.setPiece(endRow, endCol, captured);
    piece->setRow(startRow);
    piece->setCol(startCol);

    // If king is still in check, move is illegal
    if (kingStillInCheck) {
        cout << "Illegal move! You must get out of check.\n";
        return false;
    }

    board.setPiece(endRow, endCol, piece);
    board.clearPiece(startRow, startCol);
    piece->setRow(endRow);
    piece->setCol(endCol);

    displayBoard();

    // Switch the turn
    currentTurn = (currentTurn == "White") ? "Black" : "White";

    // For basic check on King (ofc)
    if (isKingInCheck(currentTurn)) {
        cout << "Check on " << currentTurn << " King!" << endl;
    }

    // For checkmate
    if (isKingInCheck(currentTurn) && hasAnyLegalMove(currentTurn) == false) {
        cout << "Checkmate! " << (currentTurn == "White" ? "Black" : "White") << " wins!" << endl;
        exit(0);
    }

    else if (!isKingInCheck(currentTurn) && !hasAnyLegalMove(currentTurn)) {
        cout << "Stalemate! It's a draw!" << endl;
        exit(0);
    }

    /* --------------------- PAWN PROMOTION ---------------------- */
    // Check for Pawn Promotion manually
    char symbol = piece->getSymbol();
    if ((symbol == 'P' && endRow == 7) || (symbol == 'p' && endRow == 0)) {
        cout << "Pawn Promotion! Enter (Q, R, B, N): ";
        char choice;
        cin >> choice;

        // Keep asking until valid choice
        while (!(choice == 'Q' || choice == 'q' || choice == 'R' || choice == 'r' || choice == 'B' || choice == 'b' || choice == 'N' || choice == 'n')) {
            cout << "Invalid input! Please enter (Q, R, B, N): ";
            cin >> choice;
        }

        // Create new promoted piece
        ChessPiece* newPiece = nullptr;
        if (choice == 'Q' || choice == 'q') {
            newPiece = new Queen(piece->getColor(), endRow, endCol);
        }
        else if (choice == 'R' || choice == 'r') {
            newPiece = new Rook(piece->getColor(), endRow, endCol);
        }
        else if (choice == 'B' || choice == 'b') {
            newPiece = new Bishop(piece->getColor(), endRow, endCol);
        }
        else if (choice == 'N' || choice == 'n') {
            newPiece = new Knight(piece->getColor(), endRow, endCol);
        }

        // Replace the board position
        board.setPiece(endRow, endCol, newPiece);

        // Remove old pawn (the one that got replaced with promotion)
        if (piece->getColor() == "White") {
            white.removePiece(piece);
            white.addPiece(newPiece);
        }
        else {
            black.removePiece(piece);
            black.addPiece(newPiece);
        }
    }

    /* EN PASSANT Detection */
    // setting available en passant square
    if (piece != nullptr && (piece->getSymbol() == 'P' || piece->getSymbol() == 'p'))
    {
        if (abs(startRow - endRow) == 2)
        {
            enPassantRow = (startRow + endRow) / 2; // row in between
            enPassantCol = startCol;
        }
        else
        {
            enPassantRow = -1;
            enPassantCol = -1;
        }
    }
    else
    {
        enPassantRow = -1;
        enPassantCol = -1;
    }

    // EN PASSANT actual capture
    if (piece != nullptr && (piece->getSymbol() == 'P' || piece->getSymbol() == 'p')) {
        if (startCol != endCol && board.getPiece(endRow, endCol) == nullptr) {
            // Capturing en passant
            int capturedPawnRow = (piece->getColor() == "White") ? endRow - 1 : endRow + 1;
            ChessPiece* capturedPawn = board.getPiece(capturedPawnRow, endCol);
            if (capturedPawn != nullptr) {
                if (capturedPawn->getColor() == (piece->getColor() == "White" ? "Black" : "White")) {
                    if (piece->getColor() == "White") {
                        black.removePiece(capturedPawn);
                    }
                    else {
                        white.removePiece(capturedPawn);
                    }
                    board.clearPiece(capturedPawnRow, endCol);
                }
            }
        }
    }

    return true;
}



bool Game::isKingInCheck(string color) {
    int kingRow = -1, kingCol = -1;

    // Find the King
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            ChessPiece* piece = board.getPiece(r, c);
            if (piece != nullptr && piece->getSymbol() == (color == "White" ? 'K' : 'k')) 
            {
                kingRow = r;
                kingCol = c;
                break;
            }
        }
    }

    if (kingRow == -1 || kingCol == -1) {
        return false; // King not found (incase)
    }

    // Check if any opponent piece can attack the King
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++)
        {
            ChessPiece* piece = board.getPiece(r, c);
            if (piece != nullptr && piece->getColor() != color)
            {
                if (piece->canMoveTo(kingRow, kingCol, board, -1, -1))
                {

                    return true;
                }
            }
        }
    }

    return false;
}

bool Game::hasAnyLegalMove(string color)
{
    for (int r1 = 0; r1 < 8; r1++)
    {
        for (int c1 = 0; c1 < 8; c1++)
        {
            ChessPiece* piece = board.getPiece(r1, c1);
            if (piece != nullptr && piece->getColor() == color)
            {
                for (int r2 = 0; r2 < 8; r2++)
                {
                    for (int c2 = 0; c2 < 8; c2++)
                    {
                        if (piece->canMoveTo(r2, c2, board, -1, -1))
                        {
                            // Check moves temporarily (Without acutally making them) to check if there is at least 1 legal move remaining
                            ChessPiece* captured = board.getPiece(r2, c2);
                            board.setPiece(r2, c2, piece);
                            board.clearPiece(r1, c1);
                            piece->setRow(r2);
                            piece->setCol(c2);

                            bool stillInCheck = isKingInCheck(color);

                            // Undo virtual move here
                            board.setPiece(r1, c1, piece);
                            board.setPiece(r2, c2, captured);
                            piece->setRow(r1);
                            piece->setCol(c1);

                            if (!stillInCheck) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Game::canCastle(string color, int row, int kingCol, int targetCol) {
    if (color == "White") {
        if (row != 0) return false;

        // King's current square must not be under check (cuz that is illegal)
        if (isKingInCheck(color)) return false;

        if (kingCol == 4 && targetCol == 6) {
            ChessPiece* king = board.getPiece(0, 4);
            ChessPiece* rook = board.getPiece(0, 7);
            if (king && rook && king->getSymbol() == 'K' && rook->getSymbol() == 'R') {
                if (board.getPiece(0, 5) == nullptr && board.getPiece(0, 6) == nullptr) {
                    // Simulatinfg moving king through f1 (0,5)
                    board.setPiece(0, 5, king);
                    board.clearPiece(0, 4);
                    bool checkOnF1 = isKingInCheck(color);
                    board.setPiece(0, 4, king);
                    board.clearPiece(0, 5);

                    if (!checkOnF1) {
                        return true;
                    }
                }
            }
        }
        else if (kingCol == 4 && targetCol == 2) {
            ChessPiece* king = board.getPiece(0, 4);
            ChessPiece* rook = board.getPiece(0, 0);
            if (king && rook && king->getSymbol() == 'K' && rook->getSymbol() == 'R') {
                if (board.getPiece(0, 1) == nullptr && board.getPiece(0, 2) == nullptr && board.getPiece(0, 3) == nullptr) {
                    // Simulating moving king through d1 (0,3)
                    board.setPiece(0, 3, king);
                    board.clearPiece(0, 4);
                    bool checkOnD1 = isKingInCheck(color);
                    board.setPiece(0, 4, king);
                    board.clearPiece(0, 3);

                    if (!checkOnD1) {
                        return true;
                    }
                }
            }
        }
    }
    else if (color == "Black") {
        if (row != 7) return false;

        if (isKingInCheck(color)) return false;

        if (kingCol == 4 && targetCol == 6) {
            ChessPiece* king = board.getPiece(7, 4);
            ChessPiece* rook = board.getPiece(7, 7);
            if (king && rook && king->getSymbol() == 'k' && rook->getSymbol() == 'r') {
                if (board.getPiece(7, 5) == nullptr && board.getPiece(7, 6) == nullptr) {
                    board.setPiece(7, 5, king);
                    board.clearPiece(7, 4);
                    bool checkOnF8 = isKingInCheck(color);
                    board.setPiece(7, 4, king);
                    board.clearPiece(7, 5);

                    if (!checkOnF8) {
                        return true;
                    }
                }
            }
        }
        else if (kingCol == 4 && targetCol == 2) {
            ChessPiece* king = board.getPiece(7, 4);
            ChessPiece* rook = board.getPiece(7, 0);
            if (king && rook && king->getSymbol() == 'k' && rook->getSymbol() == 'r') {
                if (board.getPiece(7, 1) == nullptr && board.getPiece(7, 2) == nullptr && board.getPiece(7, 3) == nullptr) {
                    board.setPiece(7, 3, king);
                    board.clearPiece(7, 4);
                    bool checkOnD8 = isKingInCheck(color);
                    board.setPiece(7, 4, king);
                    board.clearPiece(7, 3);

                    if (!checkOnD8) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}


string Game::getCurrentTurn() const {
    return currentTurn;
}

// Main function for testing
int main() {
    Game game;
    cout << R"(


 _______  __   __  _______  _______  _______    _______  _______  __   __  _______ 
|       ||  | |  ||       ||       ||       |  |       ||   _   ||  |_|  ||       |
|       ||  |_|  ||    ___||  _____||  _____|  |    ___||  |_|  ||       ||    ___|
|       ||       ||   |___ | |_____ | |_____   |   | __ |       ||       ||   |___ 
|      _||       ||    ___||_____  ||_____  |  |   ||  ||       ||       ||    ___|
|     |_ |   _   ||   |___  _____| | _____| |  |   |_| ||   _   || ||_|| ||   |___ 
|_______||__| |__||_______||_______||_______|  |_______||__| |__||_|   |_||_______|


    )";
    game.displayBoard();

    while (true) {
        cout << "\n" << game.getCurrentTurn() << "'s turn." << endl;
        cout << "Type your move (like b1 b3), or '-1 -1' to quit: ";

        string start, end;
        cin >> start >> end;

        // Check if user wants to quit
        if (start == "-1" && end == "-1") {
            cout << "\nSession closed by player command (-1).\n";
            break;
        }

        // Validate format and length
        if (start.length() != 2 || end.length() != 2 || tolower(start[0]) < 'a' || tolower(start[0]) > 'h' ||
            tolower(end[0]) < 'a' || tolower(end[0]) > 'h' || start[1] < '1' || start[1] > '8' || end[1] < '1' || end[1] > '8')
        {
            cout << "Wrong! Please use proper format: a-h and 1-8 (e.g., e2 e4)." << endl;
            continue;
        }

        // Convert to internal 0–7 indexing
        int startCol = tolower(start[0]) - 'a';
        int endCol = tolower(end[0]) - 'a';
        int startRow = tolower(start[1]) - '1';
        int endRow = tolower(end[1]) - '1';

        // Show selected piece
        ChessPiece* selectedPiece = game.getBoard().getPiece(startRow, startCol);
        if (selectedPiece != nullptr) {
            cout << "You picked: ";
            cout << (selectedPiece->getColor() == "White" ? "White " : "Black ");
            cout << selectedPiece->getSymbol() << endl;
        }
        else {
            cout << "That's an empty square!" << endl;
        }

        // Try making the move
        if (game.makeMove(startRow, startCol, endRow, endCol)) {
            cout << "\Move executed!\n";
        }
        else {
            cout << "\nThat move is not allowed, try some other move.\n";
        }
    }

    return 0;
}

