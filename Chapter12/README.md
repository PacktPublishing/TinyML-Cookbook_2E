<h2>Chapter 12</h2>
<h1><b>Enabling Compelling tinyML Solutions with On-Device Learning and Scikit-Learn on the Arduino Nano and Raspberry Pi Pico </b></h1>

<h2> About this chapter </h2>

This chapter aims to answer three likely questions you might be pondering to bring your tinyML projects to the next level.
The first question will delve into the feasibility of training models directly on microcontrollers. How can we have <b>on-device learning</b> on microcontrollers? In this part, we will discuss the backpropagation algorithm to train a shallow neural network. We will also show how to use the <b>CMSIS-DSP</b> library to accelerate its implementation on any microcontroller with an Arm Cortex-M CPU.
After discussing on-device learning, we will tackle another problem: deploying <b>scikit-learn</b> models to microcontrollers. In this second part, we will demonstrate how to deploy generic ML algorithms trained with scikit-learn using the <b>emlearn</b> open-source project.
The final question we will answer is about powering microcontrollers with batteries.

<h2> Devices </h2>

| Arduino Nano 33 BLE Sense (Rev1 and Rev2) | Raspberry Pi Pico | SparkFun RedBoard Artemis Nano |
| ----------- | ---------------------------------------------------------------- | -- |
| ✅ | ✅ | ✅ |

<h2> Hardware components </h2>

| Sensor  | Breadboard | Jumper wires | LEDs | Resistors | Extra |
| --------| -----------| ------------ | ---- | --------- | ----- |
| - | 1x half-size | 2x | - | - | 1x 3 AA battery holder |
| - | - | - | - | - | 1x 4 AA battery holder |
| - | - | - | - | - | 4x AA batteries |

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
    <td>How can we train a model on microcontrollers?</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter12/PythonScripts/01_backpropagation.py">
        <img title="Python script" src="../Imgs/python_icon.png" width="40">
        </a>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter12/ColabNotebooks/on_device_learning_and_scikit_learn.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter12/ArduinoSketches/01_backpropagation.ino">
        <img title="Sketch for on-device learning" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter12/ArduinoSketches/01_backpropagation.ino">
        <img title="Sketch for on-device learning" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>How can we deploy scikit-learn models on microcontrollers?</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter12/ColabNotebooks/on_device_learning_and_scikit_learn.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter12/ArduinoSketches/02_scikit_learn_with_emlearn.ino">
        <img title="Sketch for scikit_learn models" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter12/ArduinoSketches/02_scikit_learn_with_emlearn.ino">
        <img title="Sketch for scikit_learn models" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>How can we power microcontrollers with batteries?</td>
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
</table>