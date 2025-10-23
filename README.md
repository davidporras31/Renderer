# Renderer

## Overview
This project is a **Renderer** designed to handle graphical rendering tasks for my 2d/3d games.
This project is inspired by [SFML](https://www.sfml-dev.org/) and the tutorials available on [LearnOpenGL](https://learnopengl.com/).

## Features
- Real-time rendering
- Customizable shaders cashing
- text rendering
- render state for differed rendering suport
- relative transform

## Requirements
- **Operating System**: Linux(for now)
- **Dependencies**:
    - OpenGL
    - C++17 or higher
    - make

## Installation
1. Clone the repository:
     ```bash
     git clone https://github.com/davidporras31/Renderer.git
     cd renderer
     ```
2. Build the project:
     ```bash
     make
     ```

## Usage
Run the executable:
```bash
./bin/renderer.exe
```

## License
This project is licensed under the [MIT License](LICENSE).

## Acknowledgments
- [GLAD](https://github.com/Dav1dde/glad) for OpenGL function loading
- [GLFW](https://www.glfw.org/) for window and input management
- [GLM](https://github.com/g-truc/glm) for mathematics operations
- [stb](https://github.com/nothings/stb) for image loading
- [FreeType](https://freetype.org/) for font rendering