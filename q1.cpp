//#include <iostream>
//#include <cmath>
//using namespace std;
//
//// Forward declarations to break dependency cycles
//class ChessPiece;
//class ChessBoard;
//class Player;
//
//// ChessBoard class (defined first since others depend on it)
//class ChessBoard {
//private:
//    ChessPiece* board[8][8];
//public:
//    ChessBoard() {
//        for (int r = 0; r < 8; r++) {
//            for (int c = 0; c < 8; c++) {
//                board[r][c] = nullptr;
//            }
//        }
//    }
//
//    ChessPiece* getPiece(int row, int col) const {
//        return (row >= 0 && row < 8 && col >= 0 && col < 8) ? board[row][col] : nullptr;
//    }
//
//    void setPiece(int row, int col, ChessPiece* piece) {
//        if (row >= 0 && row < 8 && col >= 0 && col < 8) {
//            board[row][col] = piece;
//            if (piece) {
//                piece->setRow(row);
//                piece->setCol(col);
//            }
//        }
//    }
//
//    void clearPiece(int row, int col) {
//        if (row >= 0 && row < 8 && col >= 0 && col < 8) {
//            board[row][col] = nullptr;
//        }
//    }
//
//    // Declare display method here, but define it later
//    void display() const;
//};
//
//// Abstract base class for all chess pieces
//class ChessPiece {
//protected:
//    string color;
//    int row, col;
//public:
//    ChessPiece(string pieceColor, int initialRow, int initialCol)
//        : color(pieceColor), row(initialRow), col(initialCol) {
//    }
//
//    virtual ~ChessPiece() {}
//
//    virtual bool canMoveTo(int newRow, int newCol, const ChessBoard& board) const = 0;
//
//    string getColor() const { return color; }
//    int getRow() const { return row; }
//    int getCol() const { return col; }
//    void setRow(int newRow) { row = newRow; }
//    void setCol(int newCol) { col = newCol; }
//    virtual char getSymbol() const = 0;
//};
//
//// Define ChessBoard::display method here, after ChessPiece is fully defined
//void ChessBoard::display() const {
//    cout << "  a b c d e f g h\n";
//    for (int r = 7; r >= 0; r--) {
//        cout << (r + 1) << " ";
//        for (int c = 0; c < 8; c++) {
//            if (board[r][c] == nullptr) {
//                cout << ". ";
//            }
//            else {
//                cout << board[r][c]->getSymbol() << " ";
//            }
//        }
//        cout << "\n";
//    }
//}
//
//// PieceMove class to handle move validation
//class PieceMove {
//public:
//    int startRow, startCol, endRow, endCol;
//    ChessPiece* pieceMoved;
//    ChessPiece* pieceCaptured;
//
//    PieceMove(int sR, int sC, int eR, int eC, ChessPiece* p)
//        : startRow(sR), startCol(sC), endRow(eR), endCol(eC), pieceMoved(p), pieceCaptured(nullptr) {
//    }
//
//    bool isLegal(const ChessBoard& board) const {
//        if (board.getPiece(startRow, startCol) != pieceMoved) {
//            return false;
//        }
//        return pieceMoved->canMoveTo(endRow, endCol, board);
//    }
//};
//
//// Pawn class
//class Pawn : public ChessPiece {
//public:
//    Pawn(string pieceColor, int initialRow, int initialCol)
//        : ChessPiece(pieceColor, initialRow, initialCol) {
//    }
//
//    bool canMoveTo(int newRow, int newCol, const ChessBoard& board) const override {
//        int direction = (color == "White") ? 1 : -1;
//        int startRow = (color == "White") ? 1 : 6;
//        if (newCol == col) {
//            if (newRow == row + direction && board.getPiece(newRow, newCol) == nullptr) {
//                return true;
//            }
//            if (row == startRow && newRow == row + 2 * direction &&
//                board.getPiece(row + direction, col) == nullptr &&
//                board.getPiece(newRow, newCol) == nullptr) {
//                return true;
//            }
//        }
//        if (abs(newCol - col) == 1 && newRow == row + direction) {
//            ChessPiece* target = board.getPiece(newRow, newCol);
//            if (target != nullptr && target->getColor() != color) {
//                return true;
//            }
//        }
//        return false;
//    }
//
//    char getSymbol() const override { return color == "White" ? 'P' : 'p'; }
//};
//
//// Rook class
//class Rook : public ChessPiece {
//public:
//    Rook(string pieceColor, int initialRow, int initialCol)
//        : ChessPiece(pieceColor, initialRow, initialCol) {
//    }
//
//    bool canMoveTo(int newRow, int newCol, const ChessBoard& board) const override {
//        if (newRow == row && newCol != col) {
//            int step = (newCol > col) ? 1 : -1;
//            for (int c = col + step; c != newCol; c += step) {
//                if (board.getPiece(row, c) != nullptr) return false;
//            }
//            ChessPiece* target = board.getPiece(newRow, newCol);
//            return target == nullptr || target->getColor() != color;
//        }
//        else if (newCol == col && newRow != row) {
//            int step = (newRow > row) ? 1 : -1;
//            for (int r = row + step; r != newRow; r += step) {
//                if (board.getPiece(r, col) != nullptr) return false;
//            }
//            ChessPiece* target = board.getPiece(newRow, newCol);
//            return target == nullptr || target->getColor() != color;
//        }
//        return false;
//    }
//
//    char getSymbol() const override { return color == "White" ? 'R' : 'r'; }
//};
//
//// Knight class
//class Knight : public ChessPiece {
//public:
//    Knight(string pieceColor, int initialRow, int initialCol)
//        : ChessPiece(pieceColor, initialRow, initialCol) {
//    }
//
//    bool canMoveTo(int newRow, int newCol, const ChessBoard& board) const override {
//        int rowDiff = abs(newRow - row);
//        int colDiff = abs(newCol - col);
//        if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
//            ChessPiece* target = board.getPiece(newRow, newCol);
//            return target == nullptr || target->getColor() != color;
//        }
//        return false;
//    }
//
//    char getSymbol() const override { return color == "White" ? 'N' : 'n'; }
//};
//
//// Bishop class
//class Bishop : public ChessPiece {
//public:
//    Bishop(string pieceColor, int initialRow, int initialCol)
//        : ChessPiece(pieceColor, initialRow, initialCol) {
//    }
//
//    bool canMoveTo(int newRow, int newCol, const ChessBoard& board) const override {
//        int rowDiff = newRow - row;
//        int colDiff = newCol - col;
//        if (abs(rowDiff) == abs(colDiff) && rowDiff != 0) {
//            int rowStep = (rowDiff > 0) ? 1 : -1;
//            int colStep = (colDiff > 0) ? 1 : -1;
//            int r = row + rowStep;
//            int c = col + colStep;
//            while (r != newRow && c != newCol) {
//                if (board.getPiece(r, c) != nullptr) return false;
//                r += rowStep;
//                c += colStep;
//            }
//            ChessPiece* target = board.getPiece(newRow, newCol);
//            return target == nullptr || target->getColor() != color;
//        }
//        return false;
//    }
//
//    char getSymbol() const override { return color == "White" ? 'B' : 'b'; }
//};
//
//// Queen class
//class Queen : public ChessPiece {
//public:
//    Queen(string pieceColor, int initialRow, int initialCol)
//        : ChessPiece(pieceColor, initialRow, initialCol) {
//    }
//
//    bool canMoveTo(int newRow, int newCol, const ChessBoard& board) const override {
//        int rowDiff = newRow - row;
//        int colDiff = newCol - col;
//        if (newRow == row || newCol == col || abs(rowDiff) == abs(colDiff)) {
//            int rowStep = (rowDiff == 0) ? 0 : (rowDiff > 0 ? 1 : -1);
//            int colStep = (colDiff == 0) ? 0 : (colDiff > 0 ? 1 : -1);
//            int r = row + rowStep;
//            int c = col + colStep;
//            while (r != newRow || c != newCol) {
//                if (board.getPiece(r, c) != nullptr) return false;
//                r += rowStep;
//                c += colStep;
//            }
//            ChessPiece* target = board.getPiece(newRow, newCol);
//            return target == nullptr || target->getColor() != color;
//        }
//        return false;
//    }
//
//    char getSymbol() const override { return color == "White" ? 'Q' : 'q'; }
//};
//
//// King class
//class King : public ChessPiece {
//public:
//    King(string pieceColor, int initialRow, int initialCol)
//        : ChessPiece(pieceColor, initialRow, initialCol) {
//    }
//
//    bool canMoveTo(int newRow, int newCol, const ChessBoard& board) const override {
//        int rowDiff = abs(newRow - row);
//        int colDiff = abs(newCol - col);
//        if (rowDiff <= 1 && colDiff <= 1 && (rowDiff + colDiff > 0)) {
//            ChessPiece* target = board.getPiece(newRow, newCol);
//            return target == nullptr || target->getColor() != color;
//        }
//        return false;
//    }
//
//    char getSymbol() const override { return color == "White" ? 'K' : 'k'; }
//};
//
//// Player class
//class Player {
//private:
//    string color;
//    ChessPiece* pieces[16];
//    int pieceCount;
//public:
//    Player(string playerColor) : color(playerColor), pieceCount(0) {
//        for (int i = 0; i < 16; i++) pieces[i] = nullptr;
//    }
//
//    ~Player() {
//        for (int i = 0; i < 16; i++) delete pieces[i];
//    }
//
//    void addPiece(ChessPiece* piece) {
//        if (pieceCount < 16) pieces[pieceCount++] = piece;
//    }
//
//    void removePiece(ChessPiece* piece) {
//        for (int i = 0; i < pieceCount; i++) {
//            if (pieces[i] == piece) {
//                delete pieces[i];
//                pieces[i] = pieces[--pieceCount];
//                pieces[pieceCount] = nullptr;
//                break;
//            }
//        }
//    }
//
//    string getColor() const { return color; }
//};
//
//// Game class
//class Game {
//private:
//    ChessBoard board;
//    Player white;
//    Player black;
//    string currentTurn; // "White" or "Black"
//public:
//    Game() : white("White"), black("Black"), currentTurn("White") {
//        // White pieces setup
//        for (int col = 0; col < 8; col++) {
//            Pawn* whitePawn = new Pawn("White", 1, col);
//            white.addPiece(whitePawn);
//            board.setPiece(1, col, whitePawn);
//        }
//
//        /* POSITIONS [WHITE]:
//        - pawnA: row 1, col 0, a2
//        - pawnB: row 1, col 1, b2
//        - pawnC: row 1, col 2, c2
//        - pawnD: row 1, col 3, d2
//        - pawnE: row 1, col 4, e2
//        - pawnF: row 1, col 5, f2
//        - pawnG: row 1, col 6, g2
//        - pawnH: row 1, col 7, h2
//        - rookLeft: row 0, col 0, a1
//        - rookRight: row 0, col 7, h1
//        - knightLeft: row 0, col 1, b1
//        - knightRight: row 0, col 6, g1
//        - bishopLeft: row 0, col 2, c1
//        - bishopRight: row 0, col 5, f1
//        - queen: row 0, col 3, d1
//        - king: row 0, col 4, e1
//        */
//
//        Rook* whiteRookLeft = new Rook("White", 0, 0);
//        Rook* whiteRookRight = new Rook("White", 0, 7);
//        Knight* whiteKnightLeft = new Knight("White", 0, 1);
//        Knight* whiteKnightRight = new Knight("White", 0, 6);
//        Bishop* whiteBishopLeft = new Bishop("White", 0, 2);
//        Bishop* whiteBishopRight = new Bishop("White", 0, 5);
//        Queen* whiteQueen = new Queen("White", 0, 3);
//        King* whiteKing = new King("White", 0, 4);
//        white.addPiece(whiteRookLeft);
//        white.addPiece(whiteRookRight);
//        white.addPiece(whiteKnightLeft);
//        white.addPiece(whiteKnightRight);
//        white.addPiece(whiteBishopLeft);
//        white.addPiece(whiteBishopRight);
//        white.addPiece(whiteQueen);
//        white.addPiece(whiteKing);
//        board.setPiece(0, 0, whiteRookLeft);
//        board.setPiece(0, 7, whiteRookRight);
//        board.setPiece(0, 1, whiteKnightLeft);
//        board.setPiece(0, 6, whiteKnightRight);
//        board.setPiece(0, 2, whiteBishopLeft);
//        board.setPiece(0, 5, whiteBishopRight);
//        board.setPiece(0, 3, whiteQueen);
//        board.setPiece(0, 4, whiteKing);
//
//        // Black pieces setup
//        for (int col = 0; col < 8; col++) {
//            Pawn* blackPawn = new Pawn("Black", 6, col);
//            black.addPiece(blackPawn);
//            board.setPiece(6, col, blackPawn);
//        }
//
//        /* POSITIONS [BLACK]:
//        - pawnA: row 6, col 0, a7
//        - pawnB: row 6, col 1, b7
//        - pawnC: row 6, col 2, c7
//        - pawnD: row 6, col 3, d7
//        - pawnE: row 6, col 4, e7
//        - pawnF: row 6, col 5, f7
//        - pawnG: row 6, col 6, g7
//        - pawnH: row 6, col 7, h7
//        - rookLeft: row 7, col 0, a8
//        - rookRight: row 7, col 7, h8
//        - knightLeft: row 7, col 1, b8
//        - knightRight: row 7, col 6, g8
//        - bishopLeft: row 7, col 2, c8
//        - bishopRight: row 7, col 5, f8
//        - queen: row 7, col 3, d8
//        - king: row 7, col 4, e8
//        */
//
//        Rook* blackRookLeft = new Rook("Black", 7, 0);
//        Rook* blackRookRight = new Rook("Black", 7, 7);
//        Knight* blackKnightLeft = new Knight("Black", 7, 1);
//        Knight* blackKnightRight = new Knight("Black", 7, 6);
//        Bishop* blackBishopLeft = new Bishop("Black", 7, 2);
//        Bishop* blackBishopRight = new Bishop("Black", 7, 5);
//        Queen* blackQueen = new Queen("Black", 7, 3);
//        King* blackKing = new King("Black", 7, 4);
//        black.addPiece(blackRookLeft);
//        black.addPiece(blackRookRight);
//        black.addPiece(blackKnightLeft);
//        black.addPiece(blackKnightRight);
//        black.addPiece(blackBishopLeft);
//        black.addPiece(blackBishopRight);
//        black.addPiece(blackQueen);
//        black.addPiece(blackKing);
//        board.setPiece(7, 0, blackRookLeft);
//        board.setPiece(7, 7, blackRookRight);
//        board.setPiece(7, 1, blackKnightLeft);
//        board.setPiece(7, 6, blackKnightRight);
//        board.setPiece(7, 2, blackBishopLeft);
//        board.setPiece(7, 5, blackBishopRight);
//        board.setPiece(7, 3, blackQueen);
//        board.setPiece(7, 4, blackKing);
//    }
//
//    // Display the current state of the board
//    void displayBoard() {
//        board.display();
//    }
//
//    // Execute a move from (startRow, startCol) to (endRow, endCol)
//    bool makeMove(int startRow, int startCol, int endRow, int endCol) {
//        // Get the piece at the starting position
//        ChessPiece* piece = board.getPiece(startRow, startCol);
//
//        // Check if there is a piece and if it's the correct player's turn
//        if (piece == nullptr || piece->getColor() != currentTurn) {
//            return false;
//        }
//
//        // Create a move object to validate and execute
//        PieceMove move(startRow, startCol, endRow, endCol, piece);
//
//        // Validate the move using PieceMove's isLegal method
//        if (move.isLegal(board)) {
//            // Check if there's a piece at the destination (potential capture)
//            ChessPiece* target = board.getPiece(endRow, endCol);
//            if (target != nullptr && target->getColor() != piece->getColor()) {
//                move.pieceCaptured = target;
//                // Remove the captured piece from the opponent's player
//                if (target->getColor() == "White") {
//                    white.removePiece(target);
//                }
//                else {
//                    black.removePiece(target);
//                }
//            }
//
//            // Update the board: move the piece to the new position
//            board.setPiece(endRow, endCol, piece);
//            board.clearPiece(startRow, startCol);
//            piece->setRow(endRow);
//            piece->setCol(endCol);
//
//            // Switch turns after a successful move
//            currentTurn = (currentTurn == "White") ? "Black" : "White";
//            return true;
//        }
//
//        return false;
//    }
//
//    // Getter for current turn (useful for user interaction)
//    string getCurrentTurn() const {
//        return currentTurn;
//    }
//};
//
//// Main function for testing
//int main() {
//    Game game;
//    cout << "Initial board:\n";
//    game.displayBoard();
//    cout << "\nMoving white pawn from b2 to b3:\n";
//    game.makeMove(1, 1, 2, 1);
//    game.displayBoard();
//    cout << "\nMoving black pawn from b7 to b6:\n";
//    game.makeMove(6, 1, 5, 1);
//    game.displayBoard();
//    cout << "\nMoving white knight from b1 to c3:\n";
//    game.makeMove(0, 1, 2, 2);
//    game.displayBoard();
//    return 0;
//}