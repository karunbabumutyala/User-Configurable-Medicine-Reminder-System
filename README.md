# 💊 USER-CONFIGURABLE MEDICINE REMINDER SYSTEM

<div align="center">

## 🔔 Smart Embedded Medicine Reminder using LPC2148

</div>

---

# 📌 Project Overview

The **User-Configurable Medicine Reminder System** is an embedded system project designed using the **LPC2148 ARM7 Microcontroller**.

This system helps users remember their medicine schedules by providing:

- ✅ Time-based reminders
- ✅ LCD notifications
- ✅ Buzzer alerts
- ✅ User-configurable medicine timings
- ✅ Keypad-based interaction
- ✅ RTC (Real Time Clock) support

The project is mainly focused on assisting elderly people and patients who need regular medicine reminders.

---

# 🎯 Objectives

* ⏰ Provide accurate medicine reminders
* 👨‍⚕️ Help users maintain medicine schedules
* 🔔 Generate buzzer alerts during reminder time
* 📟 Display medicine time information on LCD
* ⌨️ Allow users to configure reminder timings
* ⚡ Develop a real-time embedded healthcare application

---

# 🛠️ Hardware Components Used

| Component        | Description                       |
| ---------------- | --------------------------------- |
| 🔹 LPC2148       | ARM7 Microcontroller              |
| 🔹 RTC           | Real Time Clock for time tracking |
| 🔹 LCD 16x2      | Display reminder messages         |
| 🔹 Matrix Keypad | User input for configuration      |
| 🔹 Buzzer        | Audio alert for reminders         |
| 🔹 Power Supply  | System power source               |

---

# 💻 Software Requirements

| Software        | Purpose                          |
| --------------- | -------------------------------- |
| 🧠 Keil uVision | Code development and compilation |
| ⚙️ Flash Magic  | Flashing program into LPC2148    |

---

# ⚙️ Features

---

## ⏰ Real-Time Clock Integration

- Utilizes the LPC2148 RTC for accurate timekeeping
- Maintains current time, date, and day continuously
- Ensures precise scheduling of medicine alerts

<p align="center">
  <img src="rtc_display.png" width="250">
</p>

---

## 💊 Dynamic Medicine Slot Management ⭐

- Provides default medicine slots
- Allows users to:
  - Edit existing slot timings
  - Update schedules anytime
- Supports addition of extra medicine slots
- Handles multiple medicine reminders efficiently

<p align="center">
  <img src="medicine_slot.png" width="250">
</p>

---

## 🖥️ Main Menu Medicine Schedule Display ⭐

- Displays current time along with active medicine slots
- Enables users to view full schedule from the main screen
- Automatically updates when slots are modified

---

## 🔔 Smart Alert System

- Continuously compares RTC time with configured slots
- Triggers alerts exactly when timing matches
- Ensures timely medicine reminders

<p align="center">
  <img src="alert_screen.png" width="250">
</p>

---

## 📢 Audio-Visual Notification

- Buzzer alert for immediate attention
- LCD display messages for clear instructions
- Dual notification improves reliability

---

## 🔢 User-Friendly Keypad Interface

- Simple keypad-based navigation
- Allows:
  - Adding new slots
  - Editing existing timings
  - Navigating menus easily

<p align="center">
  <img src="keypad.png" width="200">
</p>

---

## ⚙️ Menu-Driven User Interface

- Structured and intuitive menu system
- Includes options for:
  - Time/Date setup
  - Medicine slot management
- Easy interaction for all users

---

## ⚡ Interrupt-Based Quick Access

- External interrupts used for fast user actions
- Improves responsiveness of the system
- Efficient event handling using ISR

---

## 🧠 Modular Embedded C Programming

- Organized driver-based coding structure
- Separate modules for:
  - LCD
  - RTC
  - Keypad
  - Interrupts
  - Buzzer
- Simplifies debugging and maintenance

---
---

# 🧩 Functional Block Diagram

<img width="1492" height="1054" alt="blockdiagram" src="https://github.com/user-attachments/assets/6470c664-7e12-4d57-a028-29b7590a8523" />

---

# 🔄 Working Principle

- 1️⃣ User sets medicine reminder timings using keypad
- 2️⃣ RTC continuously maintains current time
- 3️⃣ LPC2148 compares RTC time with stored reminder time
- 4️⃣ When timing matches:
  - 🔔 Buzzer turns ON
  - 📟 LCD displays medicine reminder message
- 5️⃣ User acknowledges reminder using keypad/button

---

# 📂 Project Structure

```text
📁 Medicine Reminder System
 ┣ 📄 main.c
 ┣ 📄 lcd.c
 ┣ 📄 lcd.h
 ┣ 📄 rtc.c
 ┣ 📄 rtc.h
 ┣ 📄 keypad.c
 ┣ 📄 keypad.h
 ┣ 📄 interrupt.c
 ┣ 📄 interrupt.h
 ┣ 📄 types.h
 ┣ 📄 delay.c
 ┣ 📄 delay.h
 ┗ 📄 README.md
```

---

# 🚀 How to Run the Project

### Step 1️⃣

Open the project in **Keil uVision**.

### Step 2️⃣

Compile the Embedded C code.

### Step 3️⃣

Generate HEX file.

### Step 4️⃣

Flash the HEX file into LPC2148 using **Flash Magic**.

### Step 5️⃣

Connect hardware components properly.

### Step 6️⃣

Power ON the system and configure medicine timings.

---

# 📸 Project Output

## 🖥️ LCD Display Example

```text
Medicine Time!
Take Tablet
```

---

# 🌟 Advantages

✅ Easy to use
✅ Helpful for elderly people
✅ Improves medicine schedule management
✅ Low power embedded solution
✅ Compact and cost effective

---

# 🔮 Future Enhancements

🚀 GSM message alerts
🚀 Mobile app integration
🚀 IoT connectivity
🚀 Voice notification system
🚀 Cloud-based reminder storage

---

# 👨‍💻 Developed By

**Karun Babu Mutyala**
Embedded Systems Enthusiast ⚡

---

# 📚 Technologies Used

* 🔹 Embedded C
* 🔹 ARM7 LPC2148
* 🔹 RTC Interfacing
* 🔹 LCD Interfacing
* 🔹 Keypad Interfacing
* 🔹 Interrupt Programming

---

# ⭐ GitHub Repository

If you like this project, give it a ⭐ on GitHub.

---

<div align="center">

## 💙 Thank You 💙

### Embedded Systems | ARM7 | Healthcare Automation

</div>
