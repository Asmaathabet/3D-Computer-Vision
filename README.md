# Image Transformation with OpenCV

This project demonstrates various 2D image transformations, including translation, rotation, scaling, skewing, and perspective distortion using OpenCV. The transformations are applied in real-time, allowing interactive adjustments through keyboard inputs.

## Features

- **Translation:** Move the image horizontally or vertically.
- **Rotation:** Rotate the image around a specified angle.
- **Scaling:** Scale the image along the x and y axes.
- **Skewing:** Apply a skew effect to the image, distorting it along one axis.
- **Perspective Distortion:** Apply perspective transformations to simulate 3D effects.

## Prerequisites

- **OpenCV**: The project relies on OpenCV for image processing. Install it using the following command:
  ```bash
  pip install opencv-python
  ```
- **C++ Compiler**: Ensure you have a C++ compiler that supports C++11 or later.

## How to Build

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/opencv-transformations.git
   cd opencv-transformations
   ```

2. **Compile the Program:**
   ```bash
   g++ -o transform main.cpp `pkg-config --cflags --libs opencv4`
   ```

3. **Run the Program:**
   ```bash
   ./transform
   ```

## Usage

- **Start the Application:**
  The program will open a window displaying the transformed image.

- **Keyboard Controls:**
  - `b`: Decrease rotation angle.
  - `e`: Increase rotation angle.
  - `u`: Move the image up (increase `ty`).
  - `d`: Move the image down (decrease `ty`).
  - `l`: Move the image left (decrease `tx`).
  - `r`: Move the image right (increase `tx`).
  - `x`: Decrease the scaling factor.
  - `y`: Increase the scaling factor.
  - `a`: Reset all transformations to default values.
  - `Esc`: Exit the application.

## Example Image

Make sure to replace the image path in the `main()` function with the correct path to your image:
```cpp
cv::Mat img = cv::imread("path_to_your_image.jpg");
```

## Project Structure

- **main.cpp**: The main source code file that contains the implementation of the image transformations.
- **README.md**: Documentation file (this file).

## Future Enhancements

- Add support for more complex transformations.
- Implement GUI sliders to adjust transformation parameters in real-time.

