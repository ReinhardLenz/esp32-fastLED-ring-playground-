


# **Circuit Documentation**

## Schematic

![My picture](circuit_image_potentiometer.png)


## Photo

![My picture](photo_curcuit_with_potentiometer.jpg)


## **1\. Circuit Summary**

This circuit combines a LILYGO T-Beam Meshtastic LORA32 868 MHz controller with:

> * A BNO085 motion sensor.  
> * A 45-pixel WS2812 NeoPixel ring.  
> * A potentiometer connected to an analog input.  
> * An 18650 battery and MT3608 boost converter used to provide approximately 5 V to the NeoPixel ring.

The T-Beam  reads the potentiometer wiper through an analog-capable GPIO36 and drives the NeoPixel ring.   
The circuit and program is intended to test the potentiometer and Neopixelring together. By rotating the potentiometer from zero to full, the LED is changing it's position between 0 ... 360 degrees. In this code setup, the BNO085 has no function at all.


## ---

**2\. Component List**

### **LILYGO T-Beam Meshtastic LORA32 915 MHz**

The T-Beam is the main microcontroller and control board. It:

> * Runs the Arduino firmware.  
> * Reads the potentiometer through its analog input.  
> * Drives the WS2812 LED data signal.  
> * Provides 3.3 V power to the BNO085 and potentiometer.  
> * Provides the GPIO connections used by the BNO085.

The firmware uses:

> * GPIO 13 for the LED data output.  
> * GPIO 36, labeled VP on the board, for potentiometer measurement.  
> * GPIO 15 for one BNO085 serial interface signal.  
> * GPIO 14 for the other BNO085 serial interface signal.

### ---

**BNO085**

The BNO085 is a 9-axis intelligent motion sensor capable of providing orientation and motion data.  
In this circuit:

> * VCC is connected to the T-Beam 3.3 V supply.  
> * GND is connected to the common ground.  
> * PS1 is tied to 3.3 V.  
> * PS0 is tied to ground.  
> * SDA/MISO/TX is connected to T-Beam GPIO 15\.  
> * SCL/SCK/RX is connected to T-Beam GPIO 14\.

The BNO085 chip-select, interrupt, and reset pins are not connected in the supplied wiring. The interface selected by PS0 and PS1 should be confirmed against the BNO085 module documentation.

### ---

**WS2812 45-LED Ring**

The LED ring contains 45 individually addressable RGB LEDs.  
In this circuit:

> * 5V receives power from the MT3608 boost converter.  
> * GND is connected to the common ground.  
> * D1 receives the data signal from T-Beam GPIO 13\.  
> * D0 is not connected.

The firmware illuminates exactly one LED at a time in blue. The LED position is determined by the potentiometer voltage.

### ---

**18650 Battery Holder**

The 18650 holder supplies the circuit’s battery power.

> * VCC supplies the positive battery voltage to the MT3608 VIN+ input.  
> * GND connects to the MT3608 VIN- input.

Only use a suitable protected or properly managed 18650 cell. The battery holder does not itself provide charging, over-discharge protection, or short-circuit protection unless those functions are included in the holder or battery system.

### ---

**MT3608 Boost Converter**

The MT3608 boosts the 18650 battery voltage to a higher output voltage for the LED ring.

> * VIN+ connects to the battery positive terminal.  
> * VIN- connects to the battery negative terminal.  
> * VOUT+ supplies the LED ring’s 5 V input.  
> * VOUT- connects to the common ground.

The converter output should be adjusted to the required LED supply voltage before attaching the LED ring. The converter must also be capable of supplying the required LED current.

### ---

**Potentiometer**

The potentiometer provides a variable analog voltage to the T-Beam.

> * A connects to the T-Beam 3.3 V supply.  
> * E connects to the common ground.  
> * S connects to the T-Beam VP analog input, corresponding to GPIO 36\.

Rotating the potentiometer changes the voltage at the wiper. The firmware converts this voltage into an LED position from LED 0 through LED 44\.

## ---

**3\. Component Wiring Details**

### **LILYGO T-Beam Meshtastic LORA32 915 MHz**

| T-Beam Pin | Connection | Function   |
| :---- | :---- | :---- |
| GPIO 13 | WS2812 ring D1 | LED data output |
| VP / GPIO 36 | Potentiometer S | Analog potentiometer input |
| GPIO 15 | BNO085 SDA/MISO/TX | Sensor interface signal |
| GPIO 14 | BNO085 SCL/SCK/RX | Sensor interface signal |
| 3V3 | BNO085 VCC, BNO085 PS1, potentiometer A | 3.3 V supply |
| GND | Common ground network | Ground return |

The T-Beam’s other listed pins are not connected in the supplied net list.

### ---

**BNO085**

| BNO085 Pin | Connection | Function   |
| :---- | :---- | :---- |
| VCC | T-Beam 3V3 | Sensor power |
| GND | Common ground | Ground return |
| PS1 | T-Beam 3V3 | Interface-mode selection |
| PS0 | Common ground | Interface-mode selection |
| SDA/MISO/TX | T-Beam GPIO 15 | Sensor data/interface signal |
| SCL/SCK/RX | T-Beam GPIO 14 | Sensor clock/interface signal |
| ADR/MOSI | No connection listed | Unconnected |
| CS | No connection listed | Unconnected |
| INT | No connection listed | Unconnected |
| RST | No connection listed | Unconnected |

The actual communication protocol must match the BNO085 breakout board’s interface configuration. Because the firmware supplied here does not initialize or communicate with the BNO085, the sensor is not used by the current application code.

### ---

**WS2812 45-LED Ring**

| LED Ring Pin | Connection | Function   |
| :---- | :---- | :---- |
| 5V | MT3608 VOUT+ | LED ring power |
| GND | Common ground | Ground return |
| D1 | T-Beam GPIO 13 | Serial LED data input |
| D0 | No connection listed | Unconnected or unused data output |

The LED ring should have a suitable bulk capacitor across its 5 V and ground connections. A series resistor in the data line is also commonly recommended, especially when the data wire is long. These components are not included in the supplied parts list.

### ---

**18650 Battery Holder**

| Battery Holder Pin | Connection | Function   |
| :---- | :---- | :---- |
| VCC | MT3608 VIN+ | Battery positive |
| GND | MT3608 VIN- | Battery negative |

The battery voltage varies during discharge. The MT3608 input and output ratings must be checked against the selected battery and LED load.

### ---

**MT3608 Boost Converter**

| MT3608 Pin | Connection | Function   |
| :---- | :---- | :---- |
| VIN+ | 18650 holder VCC | Battery input positive |
| VIN- | 18650 holder GND | Battery input negative |
| VOUT+ | WS2812 ring 5V | Boosted LED supply |
| VOUT- | Common ground | Output ground |

The MT3608 output voltage is not specified in the net list. It should be adjusted to approximately 5 V and verified with a multimeter before connecting the LED ring.

### ---

**Potentiometer**

| Potentiometer Pin | Connection | Function   |
| :---- | :---- | :---- |
| A | T-Beam 3V3 | Potentiometer supply |
| E | Common ground | Potentiometer ground |
| S | T-Beam VP / GPIO 36 | Wiper output |

The potentiometer wiper voltage should remain within the T-Beam ADC input range. Since the potentiometer is supplied by 3.3 V, its output should remain between approximately 0 V and 3.3 V.

## ---

**4\. Electrical Nets**

The following summarizes every specified electrical connection.

### **BNO085 Data Connections**

> * BNO085 SDA/MISO/TX ↔ T-Beam GPIO 15  
> * BNO085 SCL/SCK/RX ↔ T-Beam GPIO 14

### **3.3 V Supply Network**

> * BNO085 VCC  
> * BNO085 PS1  
> * T-Beam 3V3  
> * Potentiometer A

These pins are all electrically connected.

### **Common Ground Network**

> * BNO085 GND  
> * BNO085 PS0  
> * T-Beam GND  
> * MT3608 VOUT-  
> * Potentiometer E  
> * WS2812 ring GND

These pins are all electrically connected.

### **Battery Input**

> * 18650 holder GND ↔ MT3608 VIN-  
> * 18650 holder VCC ↔ MT3608 VIN+

### **LED Data**

> * T-Beam GPIO 13 ↔ WS2812 ring D1

### **Potentiometer Wiper**

> * T-Beam VP / GPIO 36 ↔ Potentiometer S

### **LED Power**

> * MT3608 VOUT+ ↔ WS2812 ring 5V

## ---

