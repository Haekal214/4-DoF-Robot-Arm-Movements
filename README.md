# 🤖 4-DoF Robot Arm Movements

An Arduino-based project to control a **4-DoF robotic arm** using **Forward Kinematics** and **Inverse Kinematics**. This project is perfect for robotics enthusiasts, students, and developers who want to understand how robotic arm movements are calculated and executed in real-time on microcontrollers.

---

## ✨ Features

- ✅ **Forward Kinematics**: Calculates the end-effector position from the given joint angles.
- 🔄 **Inverse Kinematics**: Computes the required joint angles to reach a target position.
- ⚙️ **Arduino-Compatible**: Implemented using `.ino` files, ready to upload to your board.
- 🤖 **Real Robot Control**: Designed for servo-controlled robotic arms.

---

## ⚡ Requirements

- Arduino board (Uno, Mega, etc.)
- 4x servo motors
- External power supply (recommended)
- Breadboard & jumper wires
- Arduino IDE

---

## 🚀 Getting Started

1. Open Arduino IDE
2. Connect your Arduino board via USB
3. Load either `forward_kinematics.ino` or `inverse_kinematics.ino`
4. Upload the code
5. Watch the robotic arm move as expected!

---

## 📐 How It Works

### 🔹 Forward Kinematics  
Input: Joint angles  
Output: Position of the end-effector in space  

### 🔹 Inverse Kinematics  
Input: Target position  
Output: Required joint angles to reach that position  

All calculations are handled **directly on the Arduino**, enabling real-time execution.

---
