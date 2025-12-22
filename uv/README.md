# UV Sensor (ML8511)

---

# 🌞 ML8511 UV Sensor – Calibrated UV Index Measurement  
A complete Arduino-based system for measuring UV intensity using the ML8511 analog UV sensor, applying self‑calibrated voltage measurement and atmospheric calibration to output an accurate UV Index.

---

## Overview  
This project measures ultraviolet (UV) radiation using the ML8511 sensor and converts the sensor’s analog voltage into a calibrated **UV Index**.  
The system includes:

- Self‑calibrated analog voltage measurement using the Arduino’s 3.3V reference pin  
- Baseline correction for the ML8511’s ~1.0 V zero‑UV offset  
- A custom calibration equation derived from real atmospheric UV index data  
- Clean, modular code split across multiple files (`.ino`, `.cpp`, `.h`)

---

## Parts and Requirements  
# Hardware  
- Arduino Uno
- ML8511 UV Sensor  
- Breadboard  
- Jumper wires  
- USB cable

# Software  
- Arduino IDE
 
---

## Pinout  
| ML8511 Pin | Arduino Pin | Description |
|------------|-------------|-------------|
| VCC        | 3.3V        | Sensor power |
| GND        | GND         | Ground |
| OUT        | A4          | UV analog output |

---

## How It Works  
The ML8511 outputs a voltage proportional to UV intensity.  
However:

- It always outputs *~1.0 V even with zero UV*  
- Arduino’s 5V supply is not perfectly stable  
- ADC readings drift with temperature  

To solve this, the project uses:

# **1. Self‑calibrated voltage measurement**  
Instead of converting ADC → voltage using 5V, we measure the Arduino’s 3.3V pin:

`3.3 / ref * uv`

This removes power‑supply error.

# **2. Baseline removal**  
`uvRaw = outputVoltage - 1.0`

# **3. Atmospheric calibration**  
Using real UV index data, we derived:

`uvIndex = m * uvRaw + c`

This maps the sensor’s behavior to real-world UV Index values.

---

## Wiring  
```
ML8511        Arduino
-----------------------
VCC     →     3.3V
GND     →     GND
OUT     →     A4
```

Keep wires short to reduce noise.

---

## Code  
This project uses a modular structure:

# **Main sketch (`.ino`)**
- Reads sensor values  
- Computes voltage, raw UV, and UV Index  
- Prints results  

# **utils.cpp**
Contains reusable functions such as:

```cpp
int averageAnalogRead(int pin);
```

# **utils.h**
Function declarations.

---

## Accuracy and Calibration  
# **Sources of error**
- Temperature drift  
- Shadows and reflections  

# **Calibration method**
1. Collected hourly UV Index data from a weather service  [Visit uvindex.today]([https://www.google.com](https://uvindex.today/cities/dhaka-bd#trend))
2. Measured corresponding sensor voltages  
3. Computed UV_raw = voltage − 1.0  
4. Performed linear regression  
5. Derived calibration coefficients (a, b)

This produces a UV Index that closely matches atmospheric data.

---

## Troubleshooting  
 **Sensor shows 0 UV indoors**
Correct — indoor lights do not emit UV.

 **Flashlight causes small readings**
This is **thermal drift**, not UV.  
The sensor reacts to heat from your finger or the flashlight.

 **No change in sunlight**
Check:
- Wiring  
- 3.3V reference connected to A3
- Sensor facing the sky  
- Serial monitor baud rate matches code  

 **Readings jump randomly**
- Use `avgAnalogRead()`  
- Keep wires short  
- Avoid touching the sensor (heat drift)

---

**Author** : Hasib
