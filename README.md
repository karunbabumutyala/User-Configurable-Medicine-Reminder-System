# 💊 USER-CONFIGURABLE MEDICINE REMINDER SYSTEM

<div align="center">

## 🔔 Smart Embedded Medicine Reminder using LPC2148

<img src="https://img.shields.io/badge/Platform-LPC2148-blue?style=for-the-badge" />
<img src="https://img.shields.io/badge/Language-Embedded%20C-green?style=for-the-badge" />
<img src="https://img.shields.io/badge/Domain-Embedded%20Systems-orange?style=for-the-badge" />
<img src="https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge" />

</div>

---

# 📌 Project Overview

The **User-Configurable Medicine Reminder System** is an embedded system project designed using the **LPC2148 ARM7 Microcontroller**.

This system helps users remember their medicine schedules by providing:

✅ Time-based reminders
✅ LCD notifications
✅ Buzzer alerts
✅ User-configurable medicine timings
✅ Keypad-based interaction
✅ RTC (Real Time Clock) support

The project is mainly focused on assisting elderly people and patients who need regular medicine reminders.

---

# 🎯 Objectives

* ⏰ Provide accurate medicine reminders
* 👨‍⚕️ Help users maintain medicine schedules
* 🔔 Generate buzzer alerts during reminder time
* 📟 Display medicine information on LCD
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
| 🖥️ Embedded C  | Programming language             |

---

# ⚙️ Features

✨ User configurable medicine timings
✨ Real-time monitoring using RTC
✨ LCD-based user interface
✨ Buzzer alert notifications
✨ Easy keypad navigation
✨ Interrupt handling support
✨ Modular embedded C programming

---

# 🧩 Functional Block Diagram

```text
            +-------------------+
            |     Power Supply  |
            +---------+---------+
                      |
                      v
            +-------------------+
            |     LPC2148       |
            |   ARM7 Controller |
            +---+---+---+---+---+
                |   |   |   |
                |   |   |   |
      +---------+   |   |   +---------+
      |             |   |             |
      v             v   v             v
+-----------+  +--------+  +----------------+
|   LCD     |  | RTC    |  | Matrix Keypad  |
+-----------+  +--------+  +----------------+

                      |
                      v
                +-----------+
                |  Buzzer   |
                +-----------+
```

---

# 🔄 Working Principle

1️⃣ User sets medicine reminder timings using keypad
2️⃣ RTC continuously maintains current time
3️⃣ LPC2148 compares RTC time with stored reminder time
4️⃣ When timing matches:

* 🔔 Buzzer turns ON
* 📟 LCD displays medicine reminder message

5️⃣ User acknowledges reminder using keypad/button

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
