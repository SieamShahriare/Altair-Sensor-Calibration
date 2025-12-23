# MQ-4 Methane Sensor Implementation

## Hardware Configuration

- **Microcontroller:** Arduino UNO
- **VCC:** 5V DC
- **GND:** Ground
- **AO:** Analog Pin A0
- **RL:** 10000 Ohm (Standard module load)

## Implementation Steps

#### 1. Calibration (Finding R0)

1. Run the `calibration.ino` script in fresh air.
2. Record the suggested R0 once the value stabilizes.

#### 2. Monitoring

1. Open the `monitoring.ino` script.
2. Update `const float R0` with recorded value.
3. Upload and monitor the Serial Output.


## Calculations

* **ADC Sampling:** Maps the 0–5V analog signal to **0–1023**

* **Voltage Conversion:** `Vout = ADC × (5.0 / 1023.0)`

* **Sensor Resistance:** `Rs = RL × (5.0 − Vout) / Vout`


* **Ratio:** `Ratio = Rs / R0`

* **Reference Points [(MQ-4 Datasheet)](https://www.datasheethub.com/wp-content/uploads/2022/10/MQ-4.pdf):**

  * **Clean air:** Rs/R0 ≈ **4.4**
  * **~1000 ppm Methane:** Rs/R0 ≈ **1.0**



## Status Thresholds

- **Ratio > 3.0:** [OK] Clean Air
- **Ratio 1.0 – 3.0:** [WARNING] Gas Detected
- **Ratio < 1.0:** [DANGER] Gas Leak
