<h2>Chapter 10</h2>
<h1><b>Deploying a CIFAR-10 Model for Memory-Constrained Devices with Zephyr OS on QEMU</b></h1>

<h2> About this chapter </h2>

In this chapter, we will build an image classification application with TensorFlow Lite for Microcontrollers (tflite-micro) for an emulated Arm Cortex-M3 microcontroller. To accomplish our task, we will start by installing the <b>Zephyr OS</b>, the primary framework used in this chapter. Next, we will design a tiny quantized CIFAR-10 model with TensorFlow. This model will be capable of running on a microcontroller with only 256 KB of program memory and 64 KB of RAM. Ultimately, we will deploy an image classification application on an emulated Arm Cortex-M3 microcontroller through Quick Emulator (QEMU).

<h2> Devices </h2>

| Arduino Nano 33 BLE Sense (Rev1 and Rev2) | Raspberry Pi Pico | SparkFun RedBoard Artemis Nano | Software emulated device |
| ----------- | ---------------------------------------------------------------- | -- | -- |
| ⛔ | ⛔ | ⛔ | ✅ |

<h2> Hardware components </h2>

| Sensor  | Breadboard | Jumper wires | LEDs | Resistors | Extra |
| --------| -----------| ------------ | ---- | --------- | ----- |
| - | - | - | - | - | - |

<h2> Software (SW) Environments </h2>

| ML | Embedded programming |
| --------| -------------------- |
| Google Colaboratory | Local IDE |

<h2> Source code </h2>

<table class="fixed">
    <col width=50%/>
<tr>
    <th>Recipe</th>
    <th>Source code</th>
    <th>There's more</th>
</tr>
<tr style="height:72px">
    <td>Getting started with the Zephyr OS</td>
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
    <td>Designing and training a CIFAR-10 model for memory-constrained devices</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter10/ColabNotebooks/prepare_model.ipynb">
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
    <td>Evaluating the accuracy of the quantized model</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter10/ColabNotebooks/prepare_model.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter10/ColabNotebooks/prepare_model.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Converting a NumPy image to a C-byte array</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter10/ColabNotebooks/prepare_model.ipynb">
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
    <td>Preparing the Zephyr project structure</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/tree/main/Chapter10/ZephyrProject/src">
        <img title="Zephyr project" src="../Imgs/project_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Deploying the TensorFlow Lite for microcontrollers application on QEMU</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter10/ZephyrProject/src/main_functions.cc">
        <img title="C/C++ code" src="../Imgs/code_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
</table>