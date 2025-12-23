# **MQ-07 Carbon Monoxide Sensor Calibration & Detection**

This project explains how to **calibrate and use the MQ-07 gas sensor** with an **Arduino Uno** to detect **Carbon Monoxide (CO)**.

The MQ-07 sensor requires a **special heating cycle** and proper calibration to produce accurate results.  
This repository documents the **complete workflow**, including real problems faced during calibration and how they were solved .

---

## **About MQ-07:**
The **MQ-07** is a **Metal Oxide Semiconductor (MOS)** sensor specifically designed to detect **Carbon Monoxide (CO)**.

- It can detect CO concentration from **10 ppm – 10,000 ppm**
- Its sensor resistance **decreases** as CO concentration increases
- It requires a **high-low heating cycle** for accurate readings

---

## **Sensor Principles:**
- The sensor has a heating element and a sensitive layer
- When CO gas is present, the layer becomes more conductive
- Higher CO → Lower resistance → Higher voltage output
- Arduino reads this voltage and converts it into **PPM (Parts Per Million)**

---

## **Pin Description**
The MQ-07 module has **4 pins**:

| Pin | Description |
|----|------------|
| **VCC** | Connects to **5V** |
| **GND** | Connects to **Ground** |
| **DO** | Digital output (HIGH/LOW, threshold-based) |
| **AO** | Analog output (0–5V, used for calibration) |

This project uses **Analog Output (AO)** for accurate calibration.

---

## **Important Note (Arduino Driver Issue)**

### **Problem Faced**
Arduino Uno was **not detected** at first in Arduino IDE due to a missing **FT232R USB-UART driver**.

### **Solution**
I installed the **FTDI Virtual COM Port (VCP) driver** manually from this website:

🔗 https://ftdichip.com/drivers/vcp-drivers/

After installation:
- I restarted my Arduino IDE
- As a result, I could see **COM Port** appearing correctly which couldn't be seen before!

---

## **MQ-07 Heating Cycle:**
The MQ-07 sensor operates in a **heating cycle**:

- **High Voltage (5V)** → ~60 seconds (cleans the sensor)
- **Low Voltage** → ~90 seconds (measurement phase)

This cycle improves accuracy and sensor stability.

---

## **Step-by-Step Calibration Process**

### **Step 1: Sensor Warm-Up**
- I connected **VCC → 5V** and **GND → GND**
- Then allowed the sensor to warm up for **5–10 minutes**
- So that this will ensure stable and accurate readings

---

### **Step 2: Wiring for Calibration**
- I connected **AO → Arduino A0**
- Then also **GND → Arduino GND**

---

### **Step 3: Uploading Calibration Code**

🔗 **Calibration Code**  
[Calibration Code](https://github.com/KraKEn-bit/MQ-07_Calibration/blob/main/Calibration_Tool/Callibration_of_Gas_sensor.ino)

---

### **Step 4: Monitoring Sensor Output**
- Opened **Serial Monitor**
- Then I set **Baud Rate: 9600**
- As a result, the sensor prints **R0 values** every few seconds

**My Observations:**  
- Initial values fluctuate rapidly  
- So, I waited **~15 minutes** until the values stabilize

After stabilization, the obtained value was: 2.65, which was used later for the Detection phase.
---

### **Step 5: CO Concentration Formula**
To convert sensor readings into PPM, the following **power-law regression formula** is used:


PPM = 100 × (Rs / R0)^(-1.53)


## **Detection Phase**

### **Step 6: Uploading Detection Code**

🔗 **Calibration Code**  
[Detection Code](https://github.com/KraKEn-bit/MQ-07_Calibration/blob/main/Final_Monitor/R_value_callibration.ino)

- Then I Opened the detection sketch  
- Uploaded the code to the Arduino  
- Reopened the **Serial Monitor** to observe live Carbon Monoxide (CO) readings  

---

## **Problem that I Encountered**
- Raw analog values remained around **13–14**
- Arduino’s analog input range is **0–1023**
- Such low values indicate an output voltage close to **0V**

### **Impact due to the Problem:**
- **Rs/R0 ratio** became extremely high  
- Calculated **PPM values** were unrealistically low (≈ **0.6,0.67,0.7,0.5.... PPM**)  

---

## **Recalculation & Debugging**

So I calculated the Voltage and used that to find the Rs value which then will replace the R0 value to find accurate results!
### **Voltage Calculation**

Vout = 14 × (5.0 / 1023.0) ≈ 0.068 V

### **Sensor Resistance Calculation:**

Rs = (5.0 − 0.068) / 0.068 ≈ 72.5 Ω

---

### **After that:**
- I uploaded the updated detection code
- Then reopened the Serial Monitor

## **Final Result of software calibration phase:**

- Rs/R0 ratio stabilized around 1.0

- CO concentration stabilized near 100 PPM

- Sensor readings became consistent and realistic




---

# **Analysis of Test Results after Lighting up a match:**

### **Detection Period:**
- At **01:47:35.802**, the sensor detected the presence of smoke instantly.  
- The **raw analog value increased sharply from 14 to 139**, confirming that the MQ-07 sensor is **physically active** and **highly sensitive to Carbon Monoxide (CO)**.

---

### **Accuracy:**
The calculated **CO concentration spiked to 4140.55 PPM**, which is consistent with expected readings from a **concentrated smoke source**, such as a recently blown-out match.

---

### **Safety Alert**
The system successfully triggered the alert message that I implemented at last:

```text
!!! WARNING: HIGH CO LEVELS !!!



