# ♟️ Chess Game

A **pure C++ command-line chess game** built for conceptual clarity and learning purposes. Designed for **2-player (user vs user)** gameplay with fully functional chess mechanics — no GUI or external libraries, just clean, object-oriented code.

## 🧠 Project Goal

This project was created to reinforce:
- Object-oriented programming
- Game logic structuring
- Command-line interface interaction
- Turn-based system design

## 🎮 Features

- ✅ Fully playable chess logic (player vs player)
- ✅ Move validation for all pieces
- ✅ Check & Checkmate detection
- ✅ Piece promotion
- ✅ Capturing and turn tracking
- ✅ Text-based board rendering
- ❌ No GUI (by design)
- ❌ Undo feature not included

## 🛠 Tech Stack

- **Language:** C++
- **Interface:** Console-based (CLI)
- **Dependencies:** None — Standard Library only

## 🚀 How to Run

> ⚠️ Requires a C++ compiler (e.g. g++, clang, MSVC)

1. **Clone the repository**
   ```bash
   git clone https://github.com/your-username/your-repo.git
   cd your-repo
   ```

2. **Compile the game**
   ```bash
   g++ -std=c++11 *.cpp -o chess-game
   ```

3. **Run it**
   ```bash
   ./chess-game
   ```

## 🧾 How to Play

- Players enter moves in the format:
  ```
  e2 e4
  b8 c6
  ```
- The board will be redrawn after each move
- Game ends on checkmate or stalemate

---

## 📁 File Overview

| File             | Purpose                           |
|------------------|------------------------------------|
| `ChessBoard.h`   | Handles board state & rendering    |
| `ChessPiece.h`   | Base class for all piece types     |
| `ChessGame.cpp`  | Main game loop & control flow      |
| `Game.h`         | Manages game state logic           |
| `PieceMove.h`    | Validates move legality            |
| `Player.h`       | Player turn & interaction          |
| `q1.cpp`         | Entry point / driver (if separate) |

## 📄 License

This project is licensed under the [MIT License](LICENSE). Feel free to modify, use, or extend.

---

## ✍️ Author

- [@talha-hmd](https://github.com/talha-hmd)
