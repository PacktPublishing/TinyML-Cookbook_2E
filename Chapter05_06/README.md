<h2>Chapter 5 and Chapter 6</h2>
<h1><b>Recognizing Music Genres with TensorFlow and Raspberry Pi Pico</b></h1>

<h2> About these chapters </h2>

This project aims to recognize three music genres from recordings obtained with a microphone connected to the Raspberry Pi Pico. The music genres we will classify are disco, jazz, and metal. Since the project offers many learning opportunities, it is split into two chapters to give as much exposure to the technical aspects as possible.

In <b>Chapter 5</b>, we will focus on the dataset preparation and the analysis of the feature extraction technique employed for classifying music genres: the Mel Frequency Cepstral Coefficients (MFCCs).

In <b>Chapter 6</b>, we will amply discuss how the target device influences the implementation of the MFCCs feature extraction.
We will start our discussion by tailoring the MFCCs implementation for the Raspberry Pi Pico. Here, we will learn how fixed-point arithmetic can help minimize the latency performance and show how the <b>CMSIS-DSP</b> library provides tremendous support in employing this limited numerical precision in feature extraction.
After reimplementing the extraction of the MFCCs using fixed-point arithmetic, we will design an ML model capable of recognizing music genres with a <b>Long Short-Term Memory (LSTM)</b> recurrent neural network (RNN).
Finally, we will test the model accuracy on the test dataset and deploy a music genre classification application on the Raspberry Pi Pico with the help of the TensorFlow Lite for Microcontrollers (tflite-micro).

<h2> Devices </h2>

| Arduino Nano 33 BLE Sense (Rev1 and Rev2) | Raspberry Pi Pico | SparkFun RedBoard Artemis Nano |
| ----------- | ---------------------------------------------------------------- | -- |
| ⛔ | ✅ | ✅ |

<h2> Hardware components </h2>

| Sensor  | Breadboard | Jumper wires | LEDs | Resistors | Extra |
| --------| -----------| ------------ | ---- | --------- | ----- |
| 1x electret microphone amplifier - MAX9814 | 1x half-size | 8x | - | - | 5-pins press-fit header strip (optional) |
|  | | | | | 1x push-button |

<h2> Software (SW) Environments </h2>

| ML | Embedded programming |
| --------| -------------------- |
| Google Colaboratory | Arduino IDE (or Arduino Web Editor) |

<h2> Chapter 5 source code </h2>

<table class="fixed">
    <col width=50%/>
<tr>
    <th>Recipe</th>
    <th>Source code</th>
    <th>There's more</th>
</tr>
<tr style="height:72px">
    <td>Connecting the microphone to the Raspberry Pi Pico</td>
    <td>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Recording audio samples with the Raspberry Pi Pico</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ArduinoSketches/02_mic_capture.ino">
        <img title="Sketch for Raspberry Pi Pico" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a>
        <img title="More in the book!" src="../Imgs/books_icon.svg" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Generating audio files from samples transmitted over the serial</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/PythonScripts/03_parse_audio_samples.py">
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
    <td>Building the dataset for classifying music genres </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/PythonScripts/04_build_dataset.py">
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
    <td>Extracting MFCCs from audio samples with TensorFlow</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ColabNotebooks/prepare_model.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ColabNotebooks/prepare_model.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
    </td>
</tr>
</table>

<h2> Chapter 6 source code </h2>

<table class="fixed">
    <col width=50%/>
<tr>
    <th>Recipe</th>
    <th>Source code</th>
    <th>There's more</th>
</tr>
<tr style="height:72px">
    <td>Computing the FFT magnitude with fixed-point arithmetic using the CMSIS-DSP library</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ColabNotebooks/prepare_model.ipynb">
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
    <td>Implementing the MFCCs feature extraction with the CMSIS-DSP Python library</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ColabNotebooks/prepare_model.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ColabNotebooks/prepare_model.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Designing and training an LSTM RNN model</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ColabNotebooks/prepare_model.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ColabNotebooks/prepare_model.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Evaluating the accuracy of the quantized model on the test dataset</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ColabNotebooks/prepare_model.ipynb">
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
    <td>Deploying the MFCCs feature extraction algorithm on the Raspberry Pi Pico</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ColabNotebooks/prepare_model.ipynb">
        <img title="Colab notebook" src="../Imgs/colab_icon.png" width="40">
        </a>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ArduinoSketches/10_mfccs.ino">
        <img title="Sketch for Raspberry Pi Pico" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ArduinoSketches/More/10_mfccs_sparkfun_artemis_nano.ino">
        <img title="Sketch for SparkFun RedBoard Artemis Nano" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
</tr>
<tr style="height:72px">
    <td>Deploying the MFCCs feature extraction algorithm on the Raspberry Pi Pico</td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ArduinoSketches/11_music_genre_classification.ino">
        <img title="Sketch for Raspberry Pi Pico" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
    <td>
        <a href="https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/ArduinoSketches/More/11_music_genre_classification_sparkfun_artemis_nano.ino">
        <img title="Sketch for SparkFun RedBoard Artemis Nano" src="../Imgs/arduino_sketch_icon.png" width="40">
        </a>
    </td>
</tr>
</table>