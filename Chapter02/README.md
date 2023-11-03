<h2>Chapter 2</h2>
<h1><b>Unleashing Your Creativity with Microcontrollers</b></h1>

<h2> About this chapter </h2>

In this chapter, we will start our micontroller programming journey by handling data transmission over the serial protocol, equipping ourselves with a foundation for basic code debugging. The transmitted data will be captured in a log file and uploaded directly to our cloud storage in Google Drive.
Afterward, we will delve into programming the GPIO peripherals using the <b>Arm Mbed</b> API and use a solderless breadboard to connect external components, such as LEDs and push-buttons.

<h2> Devices </h2>

| Arduino Nano 33 BLE Sense (Rev1 and Rev2) | Raspberry Pi Pico | SparkFun RedBoard Artemis Nano |
| ----------- | ---------------------------------------------------------------- | -- |
| ✅ | ✅ | ✅ |

<h2> Hardware components </h2>

| Sensor  | Breadboard | Jumper wires | LEDs | Resistors | Extra |
| --------| -----------| ------------ | ---- | --------- | ----- |
| - | 1x half-size | 5x | 1x RED | - | 1x push-button |

<h2> Software (SW) Environments </h2>

| ML | Embedded programming |
| --------| -------------------- |
| - | Arduino IDE (or Arduino Web Editor) |

<h2> Source code </h2>

<table class="fixed">
    <col width=50%/>
<tr>
    <th>Recipe</th>
    <th>Source code</th>
    <th>There's more</th>
</tr>
<tr style="height:72px">
    <td>Transmitting data over serial</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter02/ArduinoSketches/01_serial.ino">
        <img title="Arduino sketch" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Reading serial data and uploading files to Google Drive with Python</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter02/PythonScripts/02_serial_to_gdrive.py">
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
    <td>Implementing an LED status indicator on the breadboard</td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter02/ArduinoSketches/More/03_led_status_sparkfun_artemis_nano.png">
        <img title="Schematic for SparkFun RedBoard Artemis Nano" src="../Imgs/schematic_icon.png"  width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Controlling an external LED with the GPIO</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter02/ArduinoSketches/04_gpio_out.ino">
        <img title="Arduino sketch" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter02/ArduinoSketches/More/04_gpio_out_sparkfun_artemis_nano.ino">
        <img title="Arduino sketch" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter02/ArduinoSketches/More/04_gpio_out_sparkfun_artemis_nano.png">
        <img title="Schematic for SparkFun RedBoard Artemis Nano" src="../Imgs/schematic_icon.png"  width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Turning an LED on and off with a push-button</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter02/ArduinoSketches/05_gpio_in_out.ino">
        <img title="Arduino sketch" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter02/ArduinoSketches/More/05_gpio_in_out_sparkfun_artemis_nano.ino">
        <img title="Arduino sketch" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter02/ArduinoSketches/More/05_gpio_in_out_sparkfun_artemis_nano.png">
        <img title="Schematic for SparkFun RedBoard Artemis Nano" src="../Imgs/schematic_icon.png"  width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Using interrupts to read the push-button state</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter02/ArduinoSketches/06_gpio_interrupt.ino">
        <img title="Arduino sketch" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
</table>