<h2>Chapter 4</h2>
<h1><b>Using Edge Impulse and the Arduino Nano to Control LEDs with Voice Commands</b></h1>

<h2> About this chapter </h2>

This chapter will demonstrate the usage of <b>keyword spotting</b> (<b>KWS</b>) through Edge Impulse by building an application to voice control a light-emitting diode (LED) that emits a colored light (red, green, or blue) a certain amount of times (one, two, or three blinks) on the Arduino Nano.

The chapter will begin with dataset preparation, showing you how to acquire audio data with a mobile phone and the built-in microphone on the Arduino Nano. Then, we will design a model based on the popular <b>Mel-filterbank energy</b> (<b>MFE</b>) features for speech recognition. In these recipes, we will show you how to extract these features from audio samples, train a machine learning (ML) model, and optimize performance with the Edge Impulse EON Tuner. At the end of the chapter, we will concentrate on deploying the KWS application on the Arduino Nano.

<h2> Devices </h2>

| Arduino Nano 33 BLE Sense (Rev1 and Rev2) | Raspberry Pi Pico | SparkFun RedBoard Artemis Nano |
| ----------- | ---------------------------------------------------------------- | -- |
| ✅ | ⛔ | ⛔ |

<h2> Hardware components </h2>

| Sensor  | Breadboard | Jumper wires | LEDs | Resistors | Extra |
| --------| -----------| ------------ | ---- | --------- | ----- |
| - | - | - | - | - | - |

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
    <td>Acquiring audio data with a smartphone</td>
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
    <td>Acquiring audio data with the Arduino Nano</td>
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
    <td>Extracting MFE features from audio samples</td>
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
    <td>Designing and training a convolutional neural network (CNN)</td>
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
    <td>Tuning model performance with the EON Tuner</td>
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
    <td>Tuning model performance with the EON Tuner</td>
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
    <td>Keyword spotting on the Arduino Nano</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter04/ArduinoSketches/07_kws_arduino_nano_ble33_sense.ino">
        <img title="Sketch for Arduino Nano" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
</table>