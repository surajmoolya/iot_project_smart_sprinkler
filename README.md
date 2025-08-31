# Smart Sprinkler – IoT-driven Irrigation System

Smart irrigation using ESP8266, AWS IoT, and a fuzzy inference system.

---

## Overview

This project implements a smart sprinkler system that automates irrigation by combining:

- **Sensor monitoring** via the ESP8266 microcontroller,
- **Cloud connectivity** through AWS IoT,
- **Intelligent decision-making** using a Fuzzy Inference System (FIS),
- An **optional GUI dashboard** for real-time monitoring and control (`iot_gui`).

---

## Key Features

- **ESP8266-based control** – Reads sensor data such as soil moisture (and potentially temperature/humidity).
- **Cloud connectivity** – Sends data to AWS IoT; can receive remote commands to control the sprinkler or water pump.
- **Fuzzy logic** – Determines irrigation actions based on imprecise or noisy inputs, mimicking human decision-making.
- **Dashboard interface** – A GUI (web or desktop) for real-time data visualization and manual intervention.

---

## Project Structure

├── esp8266/
│ └── [ESP-related modules and helpers]
├── iot_gui/
│ └── [User interface files—web app or desktop]
├── esp8266.ino
└── README.md

