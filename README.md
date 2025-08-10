# hitTheball

A simple pong-style game implemented in C-style C++ using **[Raylib](https://github.com/raysan5/raylib)**.

## Overview

**hitTheball** is a minimalistic pong-inspired game written in C++ using a C-style approach. The game uses [Raylib](https://github.com/raysan5/raylib), a simple and easy-to-use library for graphics and windowing.  

## Features

- Classic pong gameplay
- C-style coding in C++
- Lightweight and easy to build
- Graphics powered by Raylib
- Personalized pong character instead of just a ball

## Technologies

- **Language:** C++ (C-style)
- **Graphics Library:** [Raylib](https://github.com/raysan5/raylib)

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++, clang++)
- **Raylib library files** (download from [Raylib GitHub](https://github.com/raysan5/raylib))

### Installation

1. **Clone the repository:**
    ```sh
    git clone https://github.com/ms-solly/hitTheball.git
    cd hitTheball
    ```

2. **Download Raylib:**  
   Visit [Raylib GitHub](https://github.com/raysan5/raylib) and follow the instructions to download and build Raylib for your platform.

   - For Linux (example):
     ```sh
     sudo apt-get install libraylib-dev
     ```
     Or see detailed instructions: [Raylib Wiki - Building on GNU/Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux)

   - For Windows or macOS, follow platform-specific instructions in the Raylib repo.

3. **Compile the code:**  
    Make sure Raylib's include and library files are available to your compiler.
    ```sh
    g++ -o hitTheball main.cpp -lraylib
    ```
    *(Replace `main.cpp` with your actual main file name if needed.)*

4. **Run the game:**
    ```sh
    ./hitTheball
    ```

## Usage

- Control your paddle using the keyboard.
- Keep the ball (character) in play as long as possible.
- (Add specific controls or scoring details here.)

## Example

```cpp
// Example snippet from the game
int main() {
    // Game loop and logic here
}
```

## Contributing

Pull requests are welcome! You can also fork this repo and experiment with Raylib.

---

**Repository:** [ms-solly/hitTheball](https://github.com/ms-solly/hitTheball)
