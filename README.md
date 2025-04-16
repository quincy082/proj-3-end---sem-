# End-Sem-Project

### Group Name: Pixels

<br>

### Student 1: Dia Pitroda
### Student Id: 202404009

<br> 

### Student 2: Vadi Quincy Hiren
### Student Id: 202401488

<br>

### Student 3: Sania Debbarma
### Student Id: 202404037

<br>

# Multiplayer LAN Carrom Game

A 2D real-time Carrom board game implemented in C using OpenGL, with multiplayer support over LAN and optional AI opponents.

---

## 📌 Project Overview

- **Languages Used**: C (primary), some Objective-C
- **Graphics Library**: OpenGL
- **Networking**: TCP sockets
- **Game Type**: Real-time LAN multiplayer with AI
- **Github Repository**: https://github.com/koroder/multiplayer-LAN-Carrom-game

---

## 🧠 Breadth-Wise Understanding

### Module Breakdown
- `main.c`: Initializes OpenGL and routes to the appropriate client
- `car_client2p.c`: Logic for 2-player LAN mode
- `car_client2p_ai.c`: 2-player mode with an AI opponent
- `car_client4p1.c` to `car_client4p3.c`: Separate clients for each player in 4-player mode
- `serv_include/`: Server-side logic
- `Makefile`: Compiles everything

### Execution Flow
1. Server starts and listens for connections
2. Clients connect via IP/port
3. Game initializes coin and striker positions
4. Turn-based control via the server
5. Server receives moves and broadcasts game state
6. Ends when win conditions are met

---

## 🔍 Depth-Wise Analysis

### Approaches Taken
- TCP used for reliable communication
- OpenGL for simple 2D rendering
- Each client has isolated logic for its player
- AI logic is embedded directly in the client

### Data Structures Used
- `struct point`: Represents 2D coordinates
- `char buffer[1024]`: For transmitting game states
- `int player_id, turn`: Track player turns
- `coin_x[10], coin_y[10]`: Coin positions

### Trade-offs Made

| Decision                    | Advantages                              | Disadvantages                             |
|-----------------------------|-----------------------------------------|-------------------------------------------|
| Separate clients            | Easier to debug                         | Code duplication                          |
| TCP networking              | Reliable and ordered                    | More overhead                             |
| OpenGL rendering            | Lightweight, low dependency             | Less flexibility for modern graphics      |
| AI inline in client         | Simple integration                      | Harder to reuse or scale                  |

---

### 🧑‍💻 Contribution Suggestions

## 🐞 Report Issues
- Raise bugs related to gameplay or synchronization  
- Highlight logic duplication in the 4-player clients  
- Suggest improvement for dynamic client management  

## 🔧 Refactor or Enhance
- Combine all 4-player clients into a single unified client  
- Let players select their ID at runtime  
- Create a settings panel to adjust game parameters (speed, visuals)  

## 🎮 Feature Additions
- Add sound effects for coin collisions and scoring  
- Implement a graphical scoreboard with OpenGL  
- Add pause/resume, rematch, or spectator functionality  

## 🧹 Code & Documentation Cleanup
- Improve function comments and variable names  
- Break large files into logical modules  
- Expand the README with GIFs or gameplay video

---

## ⚙️ How to Build and Run

### Prerequisites
- Linux/macOS
- GCC
- OpenGL + GLUT (`freeglut3-dev` on Ubuntu)

### Build Instructions
```bash
sudo apt install freeglut3-dev
make


