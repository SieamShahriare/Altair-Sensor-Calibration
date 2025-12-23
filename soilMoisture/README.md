# Soil & Environment Sensing Module (Arduino UNO + DHT11 + YL69)

## 1) Overview
This project implements a sensing module for a rover that measures:

- **Ground/soil moisture** using a **YL69 (2-pin) soil probe**
- **Ambient temperature and humidity** using a **DHT11** sensor

The soil probe reading is converted into a **relative moisture percentage (Option B calibration)** so the rover gets consistent results in its operating environment.

---

## 2) Hardware
### Components
1. **Arduino UNO (ATmega328P)**
2. **DHT11 temperature/humidity module** (3 pins: `+`, `out`, `−`)
3. **YL69 / 2-pin soil probe**
4. **10kΩ resistor** (required for the soil probe voltage divider)
5. Breadboard + jumper wires

---

## 3) Circuit Connections

### 3.1 DHT11 Wiring
DHT11 module pins are labeled `+`, `out`, `−`.

| DHT11 Pin | Arduino UNO Pin |
|----------|------------------|
| `+`      | 5V               |
| `out`    | D2               |
| `−`      | GND              |

---

### 3.2 Soil Probe Wiring (YL69 2-pin) with Voltage Divider
The soil probe behaves like a variable resistor. A **10kΩ pull-down resistor** provides a stable analog voltage at **A0**.

**Connections:**
- **Probe pin 1 → Arduino D7**
- **Probe pin 2 → Arduino A0**
- **10kΩ resistor between A0 and GND**
- **Arduino GND to breadboard GND rail**

**Circuit form:**
`D7 → (Soil Probe) → A0 → (10kΩ) → GND`

**Important:**
- Do **NOT** connect **A0 directly to GND** with a wire.
- Only the **10kΩ resistor** should connect **A0 to GND**.

---

## 4) Software Dependencies
### Required Arduino Libraries
- **DHT sensor library** (Adafruit)
- **Adafruit Unified Sensor** (dependency)

Install from Arduino IDE:
**Sketch → Include Library → Manage Libraries → Search “DHT sensor library”**

---

## 5) Measurement Principle

### 5.1 Soil Probe Reading
- The Arduino powers the probe through **D7 only during measurement** (helps reduce corrosion).
- **A0** reads the voltage divider output.
- Multiple samples are averaged for stability.
- Raw ADC values are mapped into **0–100%** using calibration values:
  - `DRY_RAW`: air / dry reference
  - `WET_RAW`: wet soil reference (Option B: practical upper reference)

### 5.2 Option B (Relative Moisture Scale)
Option B provides a repeatable scale for rover usage:
- **DRY_RAW** represents “dry ground baseline”
- **WET_RAW** represents “wet ground reference”
- The percentage is **relative to your environment**, not a universal soil standard.

---

## 6) Calibration Procedure (Option B)

### Step 1: DRY_RAW (Air / Dry reference)
1. Keep probe in **air**
2. Observe `Soil raw=...` for ~20 seconds
3. Take the stable average → set as `DRY_RAW`

### Step 2: WET_RAW (Wet reference)
1. Insert probe into **wet soil** (or dip into water briefly for test)
2. Observe stable raw values
3. Take the stable average → set as `WET_RAW`

---

## 7) Output (Serial Monitor)
Open Serial Monitor at **9600 baud**.

The system prints:
- Soil raw ADC value
- Soil moisture %
- Moisture label
- Temperature and humidity

Example:
`Soil raw=52 soil=4% [DRY] | T=40.9 C H=28%`

---

## 8) Moisture Interpretation (Rover Use)
Suggested bands:
- **0–25%** → DRY
- **26–45%** → MEDIUM
- **46–70%** → GOOD
- **71–100%** → WET

Tune thresholds based on the rover’s terrain.

---

## 9) How to Run
1. Wire sensors according to **Section 3**.
2. Install libraries (Section 4).
3. Open the `.ino` file in Arduino IDE.
4. Set calibration values:
   ```cpp
   int DRY_RAW = 41;   // your measured air/dry value
   int WET_RAW = 298;  // your measured wet reference value
