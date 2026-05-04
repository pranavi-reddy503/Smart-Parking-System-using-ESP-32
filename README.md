#  Smart Parking System using ESP32

An IoT-based Smart Parking System that detects real-time parking slot availability and provides **voice guidance** to users using ESP32.

---

# Circuit Diagram

<p align="center">
  <img src="Circuit Diagram.png" width="700">
</p>

---

# Project Demo Video

 [Watch Demo Video](https://drive.google.com/drive/folders/1PAK65SML2nUoAfc2vNeL1ipr_jRY6WbW?usp=drive_link)

---

## 📊 Project Presentation

 [View / Download PPT](https://drive.google.com/drive/folders/1PAK65SML2nUoAfc2vNeL1ipr_jRY6WbW?usp=drive_link)

---

# Problem Statement

In modern parking areas, drivers often face difficulty in identifying available parking slots, leading to time wastage, congestion, and frustration. Traditional parking systems rely on manual observation or basic indicators, which are not efficient in real-time scenarios.

There is a need for a smart system that can automatically detect parking slot availability and provide clear guidance to users. This project addresses this issue by developing an automated parking system that uses sensors and a microcontroller to monitor slots and communicate availability through display and voice output.

---

# Objectives

- To detect parking slot occupancy using IR sensors  
- To process real-time data using ESP32  
- To display available slots on a 16x2 LCD  
- To provide voice guidance using DFPlayer Mini and speaker  
- To design a low-cost and efficient smart parking system  
- To reduce manual effort and improve user convenience  

---

# Components Used

- ESP32 (ESP32-DEVKIT-32)  
- IR Sensors (4)  
- 16x2 I2C LCD Display  
- DFPlayer Mini (MP3 Module)  
- Speaker (4Ω / 3W recommended)  
- Power Supply (5V)  
- Jumper Wires & Breadboard  

---

# Working Principle

1. IR sensors are placed in each parking slot to detect vehicle presence.  
2. Each sensor sends a signal (HIGH/LOW) to the ESP32.  
3. ESP32 processes the data to determine which slots are empty.  
4. The LCD displays the number of available slots and slot details.  
5. The DFPlayer Mini plays pre-recorded audio indicating available slots.  
6. The system continuously updates in real-time.  

---

# Unique Feature

This system provides **voice-based guidance**, announcing exactly which parking slots are available. This improves usability and makes the system more user-friendly compared to traditional visual-only systems.

---

# Future Improvements

- Mobile app integration (IoT dashboard)  
- Cloud-based parking monitoring  
- Automatic gate control system  
- AI-based vehicle detection using camera  
- Navigation to nearest available slot  

---

# Project Files

- `sps_modified.ino` → Arduino code  
- `Circuit Diagram.png` → Circuit diagram  
- `output image.jpg` → Output/result image  

---

# Author

**Pranavi Reddy**
