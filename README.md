# 🎲 Bogosort Visualization (SDL2 + C++)

This project visualizes the infamous **Bogosort** algorithm using SDL2 and C++. It uses colorful bars to represent array elements and lets you watch the (painful) process of Bogosort at work.

---

## 📷 Preview

_(Insert a screenshot or GIF here if you want!)_

---

## 🧠 About

Bogosort (also known as "stupid sort") is a highly inefficient sorting algorithm that randomly shuffles the array until it becomes sorted. This project visualizes each shuffle in real-time using SDL2.

---

## 🛠 Features

- Real-time visualization using SDL2
- Custom random shuffle until sorted
- Keyboard-controlled sorting and reshuffling

---

## ⛓ Dependencies

- C++17 or higher
- [SDL2](https://www.libsdl.org/)
- [vcpkg](https://github.com/microsoft/vcpkg)
- CMake (>= 3.15)

---

## ⚙️ Build Instructions (Windows/macOS/Linux)

### 1. Install vcpkg (if not already installed)

```bash
git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.bat    # Windows
./bootstrap-vcpkg.sh     # macOS/Linux
```

### 2. Install SDL2

```bash
./vcpkg install sdl2
./vcpkg integrate install
```

> This makes vcpkg automatically work with CMake.

### 3. Clone this project

```bash
git clone https://github.com/your-username/bogosort_visualisation.git
cd bogosort_visualisation
```

### 4. Build with CMake

```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

> Replace `C:/path/to/vcpkg` with the actual path to your vcpkg folder.

---

## 🎮 Controls

| Key | Action              |
|-----|---------------------|
| `K` | Start Bogosort      |
| `R` | Reshuffle the array |
| `ESC` or close window | Quit the application  |

---

## 📁 Project Structure

```
bogosort_visualisation/
├── main.cpp
├── CMakeLists.txt
├── README.md
└── .gitignore
```
---

## 📄 License

MIT License — free to use and modify.

