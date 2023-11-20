<h1><b> Build the Arduino TensorFlow Lite for Microcontrollers (tflite-micro) library</b></h1>

Unfortunately, in this edition of the book, an official pre-built **Arduino tflite-micro** library that supports all Arduino microcontrollers, including the Arduino Nano 33 BLE Sense, Raspberry Pi Pico, and the SparkFun RedBoard Artemis Nano, is not available. As a solution, we have included a pre-built tflite-micro Arduino library designed to work on any Arduino-compatible platform with an Arm Cortex-M CPU.

The library is available **[here](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/ArduinoLibs/Arduino_TensorFlowLite.zip)** and derived from the **[Arduino tflite-micro library for the Arduino Nano 33 BLE Sense](https://github.com/tensorflow/tflite-micro-arduino-examples)**. All references to the Arduino Nano 33 BLE Sense have been removed from the library, enabling its use with any Arduino-compatible platform.

> ℹ️ You can import this library into the Arduino IDE like you do for other Arduino libraries.

For those eager to know the necessary modifications to apply to the original **Arduino tflite-micro** library to achieve compatibility with all Arduino-compatible platforms, we have prepared **[this](build_arduino_tflitemicro_lib.ipynb)** Colab notebook.

