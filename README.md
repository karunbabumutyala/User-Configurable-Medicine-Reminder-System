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
# 🧩 Functional Block Diagram

<img width="1492" height="1054" alt="blockdiagram" src="https://github.com/user-attachments/assets/6470c664-7e12-4d57-a028-29b7590a8523" />

---
# 🔌 Circuit Diagram

<p align="center">
  <img width="720" height="515" alt="image" src="https://github.com/user-attachments/assets/c3227f36-e6b5-44cb-95ca-07bbbb38c83e" />

</p>

> 📌 Complete circuit connection diagram of the LPC2148 based User-Configurable Medicine Reminder System.

---

## ⚡ Circuit Connections

| Component | LPC2148 Interface |
|---|---|
| ⌨️ 4x4 Matrix Keypad | GPIO Pins |
| 🖥️ LCD 16x2 | Data + Control Pins |
| ⏰ RTC Module | I2C Interface |
| 🔔 Buzzer | GPIO Output Pin |
| 🔘 Switch 1 | EINT0 |
| 🔘 Switch 2 | EINT1 |
| ⚡ Power Supply | 3.3V / 5V |

---

# 💻 Software Requirements

| Software        | Purpose                          |
| --------------- | -------------------------------- |
| 🧠 Keil uVision | Code development and compilation |
| ⚙️ Flash Magic  | Flashing program into LPC2148    |

---

# ⚙️ Features

## ⏰ Real-Time Clock Integration

- Utilizes the LPC2148 RTC for accurate timekeeping
- Maintains current time, date, and day continuously
- Ensures precise scheduling of medicine alerts
<p align = "center">
<img width="199" height="80" alt="image" src="https://github.com/user-attachments/assets/743063c6-5c0f-4b0b-bed5-ebfdec2df171" />
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
 <img width="194" height="79" alt="image" src="https://github.com/user-attachments/assets/4cc2d875-99b8-438e-a083-138e300bb655" />
 <img width="196" height="84" alt="image" src="https://github.com/user-attachments/assets/d999b05e-e164-4b78-b179-fdad0dee53f5" />


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
  <img width="202" height="84" alt="image" src="https://github.com/user-attachments/assets/40344c4f-230f-43dd-ac92-0ea65a5646b2" />

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
  <img width="188" height="180" alt="image" src="https://github.com/user-attachments/assets/dd70721d-24a3-40dd-bc41-4ed097963843" />

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
# ⚙️ Hardware Setup

---

## 🔘 Switch 1 (Edit Mode)

Switch1 is connected to the **EINT0** pin of LPC2148.

When the switch is pressed, the system enters **Edit Mode**.

<p align="center">
  <img width="322" height="395" alt="image" src="https://github.com/user-attachments/assets/9a9ce7e0-b410-4aa3-b66f-6236a7d32e51" />

</p>

### User can:

- Set time and date
- Add medicine timings
- Edit medicine slots
- Navigate menu using keypad

After editing, the system returns to normal monitoring mode.

---

## 🔕 Switch 2 (Stop Alert)

Switch2 is connected to the **EINT1** pin of LPC2148.

When medicine time matches, the buzzer turns ON.

<p align="center">
  <img width="310" height="384" alt="image" src="https://github.com/user-attachments/assets/14a4bdcc-7019-430a-a007-ec9f6ee74f9c" />

</p>

### When Switch2 is pressed:

- Buzzer stops
- LCD message clears
- Medicine alert is acknowledged

Then the system continues monitoring normally.

---

# 🔄 Working Principle

- 1️⃣ RTC starts and continuously maintains current time
- 2️⃣ User presses Switch1 (Edit Mode)
- 3️⃣ User sets medicine reminder timings using keypad
- 4️⃣ LPC2148 stores and compares RTC time with reminder time
- 5️⃣ When timing matches:
  - 🔔 Buzzer turns ON
  - 📟 LCD displays medicine reminder message
- 6️⃣ User presses Switch2 to stop alert
- 7️⃣ System returns to normal monitoring mode

---

# 🌟 Advantages

- ✅ Easy to use
- ✅ Helpful for elderly people
- ✅ Improves medicine schedule management
- ✅ Low power embedded solution
- ✅ Compact and cost effective

---

# 🔮 Future Enhancements

- 🚀 GSM message alerts
- 🚀 Mobile app integration
- 🚀 IoT connectivity
- 🚀 Voice notification system
- 🚀 Cloud-based reminder storage

---

---

# 👨‍💻 Developed By

**Karun Babu Mutyala**
Embedded Systems Enthusiast ⚡

---

# ⭐ GitHub Repository

If you like this project, give it a ⭐ on GitHub.

---

<div align="center">

## 💙 Thank You 💙

### Embedded Systems | ARM7 | Healthcare Automation

</div>
