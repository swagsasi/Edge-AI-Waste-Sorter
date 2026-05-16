# Edge AI Waste Sorter (Android + ESP32 + BLE)

[![Demo Video](https://img.shields.io/badge/YouTube-Watch_Video-red)](https://www.youtube.com/watch?v=dWPl3rfXH1A)

## Foreword

A few years ago, I built a waste sorting system. The setup consists of a conveyor, a tilt-based sorter using servo, and a phone on top of the conveyor to scan the garbage objects. I used the ESP8266 microcontroller to communicate with the phone using Wi-Fi. The classifier was a `.tflite` model trained using the Teachable Machine website.

Recently, I wanted to give it an upgrade by implementing custom training for better accuracy and using Bluetooth Low Energy with the help of ESP32 to reduce dependency on the router, which the previous Wi-Fi system needed.

## What is it?

This is a garbage classification system, which classifies waste into biodegradable and non-biodegradable in real-time. If the model is confident that the object is organic and has a confidence level of above 90%, it is treated as biodegradable. And the phone sends a BLE payload to the ESP32 microcontroller, which turns on the green LED. If not, the object is considered non-biodegradable, and the red LED turns on.

This can be further expanded into a physical waste sorter by utilizing conveyors and servo motors, as shown in the YouTube video.

## Project Structure
* `/android_app` - The modified Android Studio project containing the TF Lite inference and BLE connection logic.
* `/esp32_ble_code` - The C++ Arduino code for the ESP32 BLE server and GPIO controls.
* `/ml_training` - The Python script (meant for Google Colab) used to train the model and attach Android-ready metadata.

## Steps to Replicate
If you want to build this yourself:
1. **Train the Model**: Run the Python script in `/ml_training` using a Google Colab T4 GPU. It will download the Kaggle dataset automatically, train the model, and spit out a `waste_classifier.tflite` file.
2. **Flash the ESP32**: Open the `.ino` file in Arduino IDE, install the ESP32 board manager, and upload it to your board. Wire some LEDs (or a servo) to pins 25 and 26.
3. **Run the App**: Drop your `.tflite` file into the `assets` folder of the Android app. Build the app on your phone, give it Bluetooth/Camera permissions, and point it at some garbage!


## Credits & Citations
While I handled the overall working logic, and ESP32 integration, I built upon some great open-source resources:
* **Base Android Vision App**: Built on top of Google's official [TensorFlow Lite Image Classification Demo](https://github.com/tensorflow/examples/tree/master/lite/examples/image_classification/android).
* **Dataset**: Used the [Waste Classification Data](https://www.kaggle.com/datasets/techsash/waste-classification-data) by Sashaank Sekar on Kaggle.
* **ESP32 BLE**: Utilized the standard ESP32 `BLEDevice.h` libraries by Neil Kolban.
