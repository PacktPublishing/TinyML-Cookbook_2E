<h2>Chapter 8</h2>
<h1><b>Classifying Desk Objects with TensorFlow and the Arduino Nano</b></h1>

<h2> About this chapter </h2>

In this chapter, we will see the benefit of adding sight to our tiny devices by classifying two desk objects with the OV7670 camera module in conjunction with the Arduino Nano.
In the first part, we will learn how to acquire images from the OV7670 camera module. Then, we will focus on the model design, applying transfer learning with the Keras API to recognize two objects we typically find on a desk: a mug and a book.
Finally, we will deploy the quantized TensorFlow Lite model on an Arduino Nano with the help of TensorFlow Lite for Microcontrollers (tflite-micro).

<h2> Devices </h2>

| Arduino Nano 33 BLE Sense (Rev1 and Rev2) | Raspberry Pi Pico | SparkFun RedBoard Artemis Nano |
| ----------- | ---------------------------------------------------------------- | -- |
| ✅ | ⛔ | ⛔ |

<h2> Hardware components </h2>

| Sensor  | Breadboard | Jumper wires | LEDs | Resistors | Extra |
| --------| -----------| ------------ | ---- | --------- | ----- |
| 1x OV7670 camera module | 1x half-size | 18x (male to female) | - | - | 1x push-button |

<h2> Software (SW) Environments </h2>

| ML | Embedded programming |
| --------| -------------------- |
| Google Colaboratory | Arduino IDE (or Arduino Web Editor) |

<h2> Source code </h2>

<table class="fixed">
    <col width=50%/>
<tr>
    <th>Recipe</th>
    <th>Source code</th>
    <th>There's more</th>
</tr>
<tr style="height:72px">
    <td>Taking pictures with the OV7670 camera module</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter08/ArduinoSketches/01_camera_capture.ino">
        <img title="Sketch for Arduino Nano 33 BLE Sense" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Grabbing camera frames from the serial port with Python</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter08/ArduinoSketches/02_camera_capture_qvga_rgb565.ino">
        <img title="Sketch for Arduino Nano 33 BLE Sense" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter08/PythonScripts/02_parse_camera_frame.py">
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
    <td>Acquiring QQVGA images with YCbCr422 color format</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter08/ArduinoSketches/03_camera_capture_qqvga_ycbcr422.ino">
        <img title="Sketch for Arduino Nano 33 BLE Sense" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Building the dataset for classifying desk objects</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter08/PythonScripts/04_build_dataset.py">
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
    <td>Transfer learning with Keras</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter08/ColabNotebooks/prepare_model.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Quantizing and testing the trained model with TensorFlow Lite</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter08/ColabNotebooks/prepare_model.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Fusing the pre-processing operators for efficient deployment</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter08/ArduinoSketches/07_desk_objects_classification.ino">
        <img title="Sketch for Arduino Nano 33 BLE Sense" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
</table>