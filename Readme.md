# Micro Vector Editor

## Description
Micro vector Editor is a simple graphic editor implemented in C++ using Qt6
    The application supports creating and editing the following shapes:
    
    Shapes:
    - Rectangle
    - Circle
    - Line
    - Rounded Rectangle
    - Hexagon
    - Freehand (Polyline)
    - Text

    Users can:
    - Draw shapes using mouse
    - Select and move shapes
    - Change stroke color
    - Change fill color
    - Change stroke width
    - Copy, Cut, Paste
    - Undo / Redo
    - Save as SVG
    - Open SVG

    The program follows a modular structure separating:
    - Model (Shapes + Diagram)
    - View (Canvas)
    - Controller (MainWindow)
    - SVG parsing and writing

## Project Structure

    project/
    │
    ├── CMakeLists.txt
    ├── README.md
    │
    ├── src/
    │   ├── main.cpp
    │   ├── model/
    │   ├── gui/
    │   └── svg/
    │
    └── include/
    ├── model/
    ├── gui/
    └── svg/


---
## Requirement

- C++17
- Qt6 (Widgets module)
- CMake (>= 3.15)

---
## Compilation Instructions
### 1️⃣ Create Build Directory
From inside the `project` directory:
```bash
mkdir build
cd build

Run cmake 
cmake ..

Build
cmake --build .

Run Instruction
./editor
