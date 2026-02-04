# 🎮 Tic-Tac-Toe CLI in C

[![Language: C](https://img.shields.io/badge/Language-C-00599C?logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![Interface: CLI](https://img.shields.io/badge/Interface-CLI-black?logo=gnuterminal&logoColor=white)](https://en.wikipedia.org/wiki/Command-line_interface)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A simple command-line Tic-Tac-Toe game written in C with score tracking and match history.

## ✨ Highlights

- Two-player local gameplay
- Custom player names and symbols
- Score tracking across sessions
- Match history logging with timestamps
- Simple, consistent CLI interface

## 📥 Clone

```text
git clone https://github.com/litch07/tik-tac-toe-c.git
cd tik-tac-toe-c
```

## 🛠️ Build (Windows)

```text
gcc Tic-Tac-Toe.c -o tic_tac_toe.exe
```

## ▶️ Run (Windows)

```text
tic_tac_toe.exe
```

## 🎯 How To Play

- The board positions are numbered `1` to `9`.
- Enter a position number to place your symbol.
- Enter `0` to exit the current match and return to the menu.
- The player using `X` always goes first.

## 🧾 Example (CLI)

```text
Position reference:

     |     |     
  1  |  2  |  3  
-----+-----+-----
  4  |  5  |  6  
-----+-----+-----
  7  |  8  |  9  
     |     |     

Main Menu:
1. Play Match
2. Customize Players & Symbols
3. View Statistics
4. Reset Scores
5. Exit
> Choose (1-5):
```

## 📁 Files

- `Tic-Tac-Toe.c` - main source code
- `scores.txt` - saved scores (auto-created)
- `history.log` - match history (auto-created)

## 📝 Notes

- Data is stored in plain text files in the project folder.

## 📄 License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.
