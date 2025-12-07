# IoT4ALL -- Mini Connected Weather Station

A collaborative learning project by the **IoT4ALL Club** focused on
building a complete IoT weather monitoring system using embedded
systems, wireless communication, and cloud technologies.

------------------------------------------------------------------------

## 🚀 Project Overview

This project aims to design and implement a **Mini Connected Weather
Station** capable of measuring environmental parameters such as:\
- Wind speed (Hall‑effect anemometer)\
- Rainfall (tipping‑bucket rain gauge + Hall sensor)\
- Temperature & humidity

Data is transmitted wirelessly using **LoRa** and **WiFi**, processed by
a microcontroller (**Raspberry Pi Pico W and esp32**), and prepared for future
cloud integration.

------------------------------------------------------------------------

## 🎯 Objectives

-   Introduce students to **embedded systems**, **sensors**, and **IoT
    communication**\
-   Apply real‑world engineering concepts: interrupts, signal
    processing, calibration\
-   Build teamwork, documentation skills, and hands-on experience\
-   Create a functional prototype and improve it with iterative sessions

------------------------------------------------------------------------

## 🛠 Technologies & Tools

-   **Raspberry Pi Pico W**\
-   **Esp32**\
-   **Hall‑effect sensors** for rainfall and wind speed\
-   **LoRa SX1276/SX1278** modules\
-   **Fritzing** for wiring documentation\
-   **GitHub** for version control and collaboration

------------------------------------------------------------------------

## 📁 Repository Structure

    IoT4ALL-WeatherStation/
    │
    ├── code/
    │   ├── sender-pico/
    │   │   ├── Sender.ino
    │   └── receiver-esp32/
    │       └── ReceiverS.ino
    │
    ├── hardware/
    │   ├── fritzing/
    │   │   └── diagram.fzz
    │   └── photos/
    │
    ├── docs/
    │   ├── calibration/
    │   ├── sessions/
    │   └── tutorials/
    │
    ├── assets/
    │   ├── logo/
    │   └── icons/
    │
    └── README.md

------------------------------------------------------------------------

## 📸 Documentation

Every session includes:\
- A short description\
- What was achieved\
- Photos or diagrams\
- Code updates\
- Remaining tasks

This ensures a professional and reproducible workflow for future club
members.

------------------------------------------------------------------------

## 👥 Contributors

IoT4ALL Club Members -- 2025/2026\
Supervised by: **Radhi Yazidi**

------------------------------------------------------------------------

## 📄 License

This project is released under the **MIT License**.

------------------------------------------------------------------------

## 🔗 Useful Links

-   Official Club Page: *https://www.facebook.com/ClubIoT4ALLISSATM/*\
-   Project tutorials\
-   Datasheets and references

------------------------------------------------------------------------

## 🎉 Final Notes

This repository represents the collaborative work of passionate students
exploring the world of IoT.\
Feel free to fork, contribute, and continue building this project!
