<h2>Chapter 9</h2>
<h1><b>Building a Gesture-Based Interface for YouTube Playback with Edge Impulse and the Raspberry Pi Pico</b></h1>

<h2> About this chapter </h2>

This chapter will teach us how to use accelerometer measurements with machine learning (ML) to recognize three hand gestures with the Raspberry Pi Pico. These recognized gestures will then be used to play/pause, mute/unmute, and change YouTube videos on our PC.
The development of this project will start by acquiring the accelerometer data to build the gesture recognition dataset. In this part, we will learn how to interface with the I2C protocol and use the Edge Impulse data forwarder tool. Next, we will focus on the Impulse design, where we will build a spectral-features-based feed-forward neural network for gesture recognition. Finally, we will deploy the model on the Raspberry Pi Pico and implement a Python script with the <b>PyAutoGUI</b> library to build a touchless interface for YouTube video playback.

<h2> Devices </h2>

| Arduino Nano 33 BLE Sense (Rev1 and Rev2) | Raspberry Pi Pico | SparkFun RedBoard Artemis Nano |
| ----------- | ---------------------------------------------------------------- | -- |
| ⛔ | ✅ | ✅ |

<h2> Hardware components </h2>

| Sensor  | Breadboard | Jumper wires | LEDs | Resistors | Extra |
| --------| -----------| ------------ | ---- | --------- | ----- |
| 1x MPU-6050 IMU | 1x half-size | 4x | - | - | - |

<h2> Software (SW) Environments </h2>

| ML | Embedded programming |
| --------| -------------------- |
| Edge Impulse | Arduino IDE (or Arduino Web Editor) |

<h2> Source code </h2>

<table class="fixed">
    <col width=50%/>
<tr>
    <th>Recipe</th>
    <th>Source code</th>
    <th>There's more</th>
</tr>
<tr style="height:72px">
    <td>Communicating with the MPU-6050 IMU through I2C</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter09/ArduinoSketches/01_i2c_imu_addr.ino">
        <img title="Sketch for Raspberry Pi Pico" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter09/ArduinoSketches/More/01_i2c_imu_addr_sparkfun_artemis_nano.ino">
        <img title="Sketch for SparkFun RedBoard Artemis Nano" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter09/ArduinoSketches/More/01_i2c_imu_addr_sparkfun_artemis_nano.png">
        <img title="Schematic for SparkFun RedBoard Artemis Nano" src="../Imgs/schematic_icon.png"  width="40">
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter09/Extra/01_i2c_pins_sparkfun_artemis_nano.png">
        <img title="I2C pinout for SparkFun RedBoard Artemis Nano" src="../Imgs/schematic_icon.png"  width="40">
    </td>
</tr>
<tr style="height:72px">
    <td>Acquiring accelerometer data</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter09/ArduinoSketches/02_i2c_imu_read_acc.ino">
        <img title="Sketch for Raspberry Pi Pico" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter09/ArduinoSketches/More/01_i2c_imu_addr_sparkfun_artemis_nano.png">
        <img title="Sketch for SparkFun RedBoard Artemis Nano" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Building the dataset with the Edge Impulse data forwarder tool</td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Designing and training the ML model</td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Live classifications with the Edge Impulse data forwarder tool</td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Developing a continuous gesture recognition application with Edge Impulse and Arm Mbed OS</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter09/ArduinoSketches/06_gesture_recognition.ino">
        <img title="Sketch for Raspberry Pi Pico" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter09/ArduinoSketches/More/06_gesture_recognition_sparkfun_artemis_nano.ino">
        <img title="Sketch for SparkFun RedBoard Artemis Nano" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Building a gesture-based interface with PyAutoGUI</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter09/PythonScripts/07_gesture_based_ui.py">
        <img title="Python script" src="../Imgs/python_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
</table>