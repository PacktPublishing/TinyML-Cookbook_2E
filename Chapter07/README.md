<h2>Chapter 7</h2>
<h1><b>Detecting objects with Edge Impulse using FOMO on the Raspberry Pi Pico</b></h1>

<h2> About this chapter </h2>

This chapter will showcase the successful deployment of an object detection application on microcontrollers using Edge Impulse and the <b>Faster Objects, More Objects</b> <b>(FOMO)</b> ML algorithm.
Our objective will be to develop an application capable of detecting cans. The chapter will begin with dataset preparation, demonstrating how to acquire images with a webcam and label them in Edge Impulse. Next, we will design an ML model based on the FOMO algorithm. In this part, we will explore the architectural features of this novel ML solution that allows us to deploy object detection on highly constrained devices. Subsequently, we will test the model using the Edge Impulse Live classification tool and then on the Raspberry Pi Pico. The Raspberry Pi Pico will not be connected to any camera module because we transmit the images captured with the webcam to the microcontroller using the serial interface.

<h2> Devices </h2>

| Arduino Nano 33 BLE Sense (Rev1 and Rev2) | Raspberry Pi Pico | SparkFun RedBoard Artemis Nano |
| ----------- | ---------------------------------------------------------------- | -- |
| ⛔ | ✅ | ✅ |

<h2> Hardware components </h2>

| Sensor  | Breadboard | Jumper wires | LEDs | Resistors | Extra |
| --------| -----------| ------------ | ---- | --------- | ----- |
| 1x USB webcam |- | - | - | - | - |

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
    <td>Acquiring images with the webcam</td>
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
    <td>Designing the Impulse’s pre-processing block</td>
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
    <td>Transfer learning with FOMO</td>
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
    <td>Evaluating the model’s accuracy</td>
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
    <td>Using OpenCV and pySerial to send images over the serial</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter07/PythonScripts/05_emulated_camera.py">
        <img title="Python script" src="../Imgs/python_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Reading data from the serial port with Arduino-compatible platforms</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter07/ArduinoSketches/06_read_camera_frame.ino">
        <img title="Sketch for Raspberry Pi Pico" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter07/ArduinoSketches/06_read_camera_frame.ino">
        <img title="Sketch for SparkFun RedBoard Artemis Nano" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Deploying FOMO on the Raspberry Pi Pico</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter07/ArduinoSketches/07_object_detection.ino">
        <img title="Sketch for Raspberry Pi Pico" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter07/PythonScripts/07_emulated_camera_centroids.py">
        <img title="Python script" src="../Imgs/python_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter07/ArduinoSketches/07_object_detection.ino">
        <img title="Sketch for SparkFun RedBoard Artemis Nano" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
</tr>
</table>