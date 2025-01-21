
<b><p align='center'>[![Packt Sale](https://static.packt-cdn.com/assets/images/e72907cf-bf2f-4f83-bb58-6cc08a901ff9.jpeg)](https://www.packtpub.com/)</p></b>Get this book on sale at [Packt](https://www.packtpub.com/).

# TinyML Cookbook, Second Edition

<a href="https://www.packtpub.com/product/tinyml-cookbook-second-edition/9781837637362"><img src="https://m.media-amazon.com/images/I/81DSW7odWRL._SL1500_.jpg" alt="TinyML Cookbook, Second Edition" height="256px" align="right"></a>

This is the code repository for **[TinyML Cookbook, Second Edition](https://www.packtpub.com/product/tinyml-cookbook-second-edition/9781837637362)**, published by Packt.
\
\
**Combine machine learning with microcontrollers to solve real-world problems**
\
\
Author: **[Gian Marco Iodice](https://www.linkedin.com/in/gian-marco-iodice-3183a9a1/)**\
Publisher: **[Packt](https://www.packtpub.com/)**

<h1> About the book </h1>
This book is about tinyML, the technology that allows smartness in a minimally intrusive way using machine learning (ML) on low-powered devices like microcontrollers.
Whether new to this field or looking to expand your ML knowledge, this improved second edition of TinyML Cookbook has something for all. Each chapter is structured to be a self-contained project to learn how to use some of the key tinyML technologies, such as <b>Arduino</b>, <b>CMSIS-DSP</b>, <b>Edge Impulse</b>, <b>emlearn</b>, <b>Raspberry Pi Pico SDK</b>, <b>TensorFlow</b>, <b>TensorFlow Lite for Microcontrollers</b>, and <b>Zephyr</b>.

This second edition includes new recipes featuring:
* <b>LSTM neural network</b> to recognize music genres
* Edge Impulse <b>Faster-Objects-More-Objects</b> (<b>FOMO</b>) algorithm for detecting objects in a scene.
* <b>TVM</b> for the Arduino Nano 33 BLE Sense, Raspberry Pi Pico, and SparkFun RedBoard Artemis Nano model deployment
* <b>On-device learning</b> to train models on microcontrollers
* <b>Emlearn</b> to deploy <b>scikit-learn</b> trained models on microcontrollers.

TinyML Cookbook is a practical book with a focus on the principles. Although most of the presented projects are based on the **[Arduino Nano 33 BLE Sense Rev1 and Rev2](https://store.arduino.cc/products/arduino-nano-33-ble-sense)** and **[Raspberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/)**, this second edition also features the **[SparkFun RedBoard Artemis Nano](https://www.sparkfun.com/products/15443)** to help you practice the learned principles on an alternative microcontroller.
Therefore, by the end of this book, you will be well-versed in best practices and ML frameworks to develop ML applications easily on microcontrollers.

<h1> Who is this book for </h1>

Whether you are an enthusiast or professional with a basic familiarity with ML and an interest in developing ML applications on microcontrollers through practical examples, this book is for you.
TinyML Cookbook will help you expand your knowledge of tinyML by building end-to-end projects with real-world data sensors on <b>Arduino Nano 33 BLE Sense</b>, <b>Raspberry Pi Pico</b>, and <b>SparkFun RedBoard Artemis Nano</b>.
While familiarity with <b>C/C++</b>, <b>Python</b> programming, and <b>command-line interface</b> (<b>CLI</b>) is required, no prior knowledge of microcontrollers is necessary.

<h1> Technical requirements </h1>

For most of the chapters, with the only exception of <b>Chapter 10, Deploying a CIFAR-10 Model for Memory-Constrained Devices with Zephyr OS on QEMU</b>, you will need a computer (either a laptop or desktop) running Linux (preferably Ubuntu 20.04+), macOS, or Windows operating systems on an x86_64 architecture. Additionally, your computer should have a minimum of two USB ports.
In Chapter 10, you will specifically require a computer running either Linux (preferably Ubuntu 20.04+) or macOS on an x86_64 architecture.

> ⚠️ It is worth noting that most projects can also be developed on Macs powered by Apple silicon, such as M1 or M2 chips. However, at the time of writing, there is no support for the SparkFun RedBoard Artemis Nano on Apple silicon devices.

The only software prerequisites for your computer are:
* **Python** (Python 3.7+)
* **Text editor** (for example, gedit on Ubuntu)
* **Media player** (for example, VLC)
* **Image viewer** (for example, the default app in Ubuntu or Windows 10)
* **Web browser** (for example, Google Chrome)

During our tinyML journey, we will require different software tools to cover ML development and embedded programming. Thanks to Arduino, Edge Impulse, and Google, these tools will be in the cloud, browser-based, and with a free plan for our usage.
You can develop projects on the Arduino Nano 33 BLE Sense and Raspberry Pi Pico directly in your web browser using the **[Arduino Web Editor](https://create.arduino.cc)**.

> ⚠️ For projects involving the <b>SparkFun RedBoard Artemis Nano</b>, you must use the local **[Arduino IDE](https://www.arduino.cc/en/software)**. You can find the setup instructions for developing projects on this microcontroller by following this **[link](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Docs/setup_sparkfun_artemis_nano.md)**.

> ℹ️ You may also consider using the local **[Arduino IDE](https://www.arduino.cc/en/software)** the Arduino Nano 33 BLE Sense and Raspberry Pi Pico following the instructions provided at this **[link](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Docs/setup_local_arduino_ide.md)**.

The projects we will develop together require sensors and additional electronic components to build realistic tinyML prototypes and experience the complete development workflow. These components are listed at the beginning of each chapter and in the <b>README.md</b> file within the corresponding chapter folder on GitHub:
| Chapter |
| --------|
| **[2: Unleashing Your Creativity with Microcontrollers](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter02/README.md)** |
| **[3: Building a Weather Station with TensorFlow Lite for Microcontrollers](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter03/README.md)** |
| **[4: Using Edge Impulse and the Arduino Nano to Control LEDs with Voice Commands](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter04/README.md)** |
| **[5: Recognizing Music Genres with TensorFlow and the Raspberry Pi Pico - part1](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/README.md)** |
| **[6: Recognizing Music Genres with TensorFlow and the Raspberry Pi Pico - part2](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter05_06/README.md)** |
| **[7: Detecting objects with Edge Impulse using FOMO on the Raspberry Pi Pico](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter07/README.md)** |
| **[8: Classifying Desk Objects with TensorFlow and the Arduino Nano](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter08/README.md)** |
| **[9: Building a Gesture-Based Interface for YouTube Playback with Edge Impulse and the Raspberry Pi Pico](Chapter09/README.md)** |
| **[10: Deploying a CIFAR-10 Model for Memory-Constrained Devices with Zephyr OS on QEMU](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter10/README.md)** |
| **[11: Running ML models on the Arduino and Arm Ethos-U55 microNPU using Apache TVM](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter11/README.md)** |
| **[12: Enabling Compelling tinyML Solutions with On-Device Learning and Scikit-Learn on the Arduino Nano and Raspberry Pi Pico](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Chapter12/README.md)** |

Don't worry if you are an electronics beginner. You will learn more about electronic components such as LEDs, push-buttons, and resistors in the first two chapters of this book. Furthermore, we have prepared this **[beginner shopping list](https://github.com/PacktPublishing/TinyML-Cookbook_2E/blob/main/Docs/shopping_list.md)** so you know precisely what to buy.

<h1> Citation </h1>

To cite TinyML Cookbook - Second Edition in publications use:

```
@book{iodice2023tinymlcookbook2e,
  title={TinyML Cookbook, Second Edition: Combine machine learning with microcontrollers to solve real-world problems},
  author={Gian Marco Iodice},
  year={2023},
  publisher={Packt},
  isbn = {9781837637362},
  url = {https://www.packtpub.com/product/tinyml-cookbook-second-edition/9781837637362}
}
```

## Know more on the Discord server <img alt="Coding" height="25" width="32"  src="https://cliply.co/wp-content/uploads/2021/08/372108630_DISCORD_LOGO_400.gif">
You can get more engaged on the discord server for more latest updates and discussions in the community at [Discord](https://packt.link/tiny)

## Download a free PDF <img alt="Coding" height="25" width="40" src="https://emergency.com.au/wp-content/uploads/2021/03/free.gif">

_If you have already purchased a print or Kindle version of this book, you can get a DRM-free PDF version at no cost. Simply click on the link to claim your free PDF._
[Free-Ebook](https://packt.link/free-ebook/9781837637362) <img alt="Coding" height="15" width="35"  src="https://media.tenor.com/ex_HDD_k5P8AAAAi/habbo-habbohotel.gif">

We also provide a PDF file that has color images of the screenshots/diagrams used in this book at [GraphicBundle](https://packt.link/gbp/9781837637362) <img alt="Coding" height="15" width="35"  src="https://media.tenor.com/ex_HDD_k5P8AAAAi/habbo-habbohotel.gif">

## Get to know the Author

<b>Gian Marco Iodice</b> is an experienced Edge and mobile computing specialist at Arm for machine learning (ML). He is also chair of the global meetups for the tinyML foundation since 2022.

He received the MSc with honors in electronic engineering from the University of Pisa (Italy), where he specialized in HW/SW co-design for embedded systems.

At Arm, he leads the engineering developments for the **[Arm Compute Library](https://github.com/ARM-software/ComputeLibrary)**, which he co-created in 2017 to run ML workloads as efficiently as possible on Arm processors. Arm Compute Library, designed to deliver the best performance across Arm Cortex-A CPUs and Mali GPUs, is deployed on billions of devices worldwide – from servers to smartphones.

Gian Marco's specialization lies in optimizing algorithms for resource-constrained devices, which is crucial to bringing ML and computer vision (CV) capabilities to various devices, including mobile and IoT devices. Some of his relevant optimizations have been for the matrix multiplication routines and stereo vision algorithms on Arm Mali GPUs and Arm Cortex-A CPUs.

In 2023, he collaborated with the University of Cambridge to integrate ML functionalities on an Arm Cortex-M microcontroller powered by algae. This ground-breaking work was showcased at the tinyML EMEA Innovation Forum in Amsterdam in June of the same year.

In 2023, Gian Marco contributed to the development of the EdTech for Good Curation Framework. This framework, developed by UNICEF in collaboration with Arm and the Asian Development Bank (ADB), represents a significant step forward in the responsible use of technology in education. It enables public entities and international organizations to evaluate digital educational technologies, prioritizing learning outcomes and children's safety.


## Other Related Books
- [Machine Learning Engineering with Python - Second Edition](https://www.packtpub.com/product/machine-learning-engineering-with-python-second-edition/9781837631964)
- [Interpretable Machine Learning with Python - Second Edition](https://www.packtpub.com/product/interpretable-machine-learning-with-python-second-edition/9781803235424)

