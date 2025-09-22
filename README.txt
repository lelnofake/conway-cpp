# C++ SFML Project – Learning Basics

This is a C++ project I created to practice and learn the basics of C++.  
It uses **SFML (Simple and Fast Multimedia Library)** for graphics and input handling.

The program is a variant of **Conway’s Game of Life**, where you can configure:
- Grid size (`Rows`, `Cols`)
- Cell respawn / overpopulation / underpopulation rules
- Random initial state with configurable chance
- Option to count corners towards neighbor count

---

## Dependencies

On **Arch Linux**, install SFML with:

```bash
sudo pacman -Syu sfml

# Compile with SFML
g++ conway.cpp -o conway -lsfml-graphics -lsfml-window -lsfml-system

# Run
./conway

## Notes
- You need a font file named **`Arial.TTF`** in the same directory as the executable.
- This is a learning project, not meant for production use.
