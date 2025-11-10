# Spy - The Spider Robot 🤖

A fully controllable 4-legged spider robot powered by ESP32 and PCA9685 servo controller. Control your spider via Bluetooth from your smartphone with continuous movement capabilities!

## ✨ Features

- 🤖 **4-Legged Spider Design** - 12 servos for realistic biomimetic movement
- 📱 **Bluetooth Control** - Wireless control via smartphone app
- 🚀 **Continuous Movement** - Hold buttons for smooth, uninterrupted motion
- 💃 **Multiple Actions** - Walk, turn, wave, dance, handshake, and more
- ⚡ **Fast & Responsive** - Optimized speeds for smooth performance
- 🔧 **Easy to Build** - Standard components with clear instructions
- 🔋 **Battery Powered** - Portable with 18650 Li-ion batteries

## 🛠 Hardware Requirements

### Components List

| Component | Quantity | Notes |
|-----------|----------|-------|
| ESP32 Development Board | 1 | Any ESP32 variant |
| PCA9685 16-Channel PWM Servo Driver | 1 | Controls up to 16 servos |
| MG90S Servo Motors | 12 | 3 per leg (Coxa, Femur, Tibia) |
| 18650 Li-ion Battery | 2 | 7.4V series configuration |
| Battery Holder | 1 | For 2x 18650 batteries |
| Robot Chassis & Legs | 1 set | 3D printed or custom |
| Jumper Wires | Pack | Male-to-female recommended |
| Breadboard | 1 | Optional for prototyping |
| buck converter | 1 | DC power converter |

### Wiring Diagram

```
ESP32 <--> PCA9685 <--> 12x Servos
  |            |
Bluetooth   Power (7.4V)
```

**PCA9685 to ESP32 Connections:**
- **SDA** → GPIO 21 (ESP32)
- **SCL** → GPIO 22 (ESP32) 
- **VCC** → 3.3V (ESP32)
- **GND** → GND (ESP32)
- **V+** → 7.4V (Battery+)
- **GND** → Battery-

**Servo Layout (4 legs × 3 servos each):**
```
Leg 0: Channels 0,1,2   (Coxa, Femur, Tibia)
Leg 1: Channels 3,4,5
Leg 2: Channels 6,7,8  
Leg 3: Channels 9,10,11
```

## 💻 Software Installation

### Prerequisites
- Arduino IDE 2.0+ or PlatformIO
- ESP32 Board Support
- Required Libraries

### Library Installation

1. **Install ESP32 Board Support in Arduino IDE:**
   - Go to `File → Preferences`
   - Add to Additional Board Manager URLs:
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Go to `Tools → Board → Board Manager`
   - Search "ESP32" and install

2. **Install Required Libraries:**
   - **Adafruit PWM Servo Driver Library**
     - `Sketch → Include Library → Manage Libraries`
     - Search "Adafruit PWM Servo Driver" and install
   - **ESP32 BluetoothSerial** (Built-in - no installation needed)

### Uploading Code

1. Connect ESP32 to computer via USB cable
2. Select Board: `ESP32 Dev Module`
3. Select correct COM port
4. Upload the provided `spy_spider_robot.ino` code

## 📱 Bluetooth Control

### Connection Steps

1. **Power on the robot** - Wait for initialization (LED will indicate ready)
2. **On your smartphone:**
   - Open Bluetooth settings
   - Scan for new devices
   - Look for device named **"Spy"**
   - Pair with the device (no PIN required)
3. **Use Bluetooth Serial App:**
   - Download "Serial Bluetooth Terminal" (Android) or "Bluetooth Terminal" (iOS)
   - Connect to "Spy" device
   - Send single-character commands

### Control Commands

| Command | Action | Description |
|---------|--------|-------------|
| **F** | Forward | Continuous forward movement (hold button) |
| **B** | Backward | Continuous backward movement (hold button) |
| **L** | Turn Left | Continuous left turns (hold button) |
| **R** | Turn Right | Continuous right turns (hold button) |
| **S** | Stop | Stop all movement immediately |
| **U** | Stand Up | Stand to normal walking position |
| **D** | Sit Down | Sit/lower body to resting position |
| **W** | Wave | Wave with front leg (3 waves) |
| **H** | Handshake | Shake hand gesture (3 shakes) |
| **A** | Dance | Fun dance sequence |

**Usage Tips:**
- 🎮 **Hold F/B/L/R** for continuous movement
- ⏹️ **Release button** - robot automatically stops after 500ms
- 🛑 **Press S** for immediate emergency stop
- 🎭 **W, H, A** are one-time actions that complete automatically

## ⚙️ Calibration & Tuning

### Servo Calibration
If servos aren't centered properly, adjust these values in the code:

```cpp
#define SERVO_MIN  150   // Adjust for 0° position (default: 150)
#define SERVO_MAX  600   // Adjust for 180° position (default: 600)
```

### Movement Tuning
Adjust speed constants for different performance:

```cpp
const float leg_move_speed = 15;      // Walking speed (increase for faster)
const float spot_turn_speed = 8;      // Turning speed 
const float body_move_speed = 6;      // Body movement speed
float speed_multiple = 1.5;           // Global speed multiplier
```

## 🚨 Troubleshooting

### Common Issues & Solutions

| Problem | Solution |
|---------|----------|
| **Servos Not Moving** | Check 7.4V power supply, verify PCA9685 connections |
| **Bluetooth Not Connecting** | Ensure ESP32 is powered, restart phone Bluetooth |
| **Jerky Movements** | Check battery level, reduce movement speeds in code |
| **Robot Unbalanced** | Adjust servo positions in `polar_to_servo()` function |
| **Servos Overheating** | Reduce `speed_multiple` value, check for mechanical binding |
| **Limited Range** | Increase battery capacity, check for voltage drop |

### Debug Mode
The robot outputs serial messages at 115200 baud. Monitor with Serial Monitor for debugging:

```
Robot starts initialization
Bluetooth started! Device name: 'Spy'
Servo service started
Robot initialization Complete
```

## 🏗 Project Structure

```
spy-spider-robot/
├── spy_spider_robot.ino    # Main robot control code
├── README.md              # This file
├── images/                # Project images and diagrams
├── 3d_models/            # STL files for chassis (if available)
└── wiring_diagram.png    # Connection diagram
```

## 🔧 Customization

### Adding New Movements
Create new movement functions following the pattern:

```cpp
void new_movement() {
  move_speed = desired_speed;
  // Define leg positions
  set_site(leg_number, x, y, z);
  wait_all_reach();
  // Add more positions as needed
}
```

### Modifying Bluetooth Name
Change the device name in `setup()`:
```cpp
SerialBT.begin("YourCustomName");
```

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Copyright (c) 2024 Sanal M S

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! Feel free to check [issues page](../../issues).

## 📞 Support

If you have any questions or need help:
1. Check the troubleshooting section above
2. Open an issue on GitHub
3. Check the Arduino forums for ESP32 projects

---

**Happy Building!** 🎉 Let your Spy robot come to life!

---
*Project maintained by [SANAL](https://github.com/sanal-m-s)*
