# Data-driven-vehicle-control-using-CAN-controller-Area-Network-protocol(LPC2129)
This project implements a **robust and fault-tolerant vehicle control system** over the **CAN protocol** using **LPC2129 microcontrollers**. It features three functional nodes:

-  **Main Node (Dashboard)**
-  **Reverse Node (Distance Sensing)**
-  **Window Glass Control Node**

✅ Key Highlights
- **CAN-based communication** with node-specific messaging.
- **Main Node generates interrupt-driven requests**, and only the **intended node responds**.
- **Modular & fault-tolerant**: Main Node works **independently** and continues displaying temperature even if other nodes are removed.
- Simulates realistic vehicle operations using sensors, interrupts, LCDs, and LEDs.

##  System Architecture

### Main Node (Dashboard)
- Reads engine temperature from a **DS18B20 sensor**(p1.16) and displays it continuously.
- Sends control or data request messages when external interrupts are triggered:
  - Reverse check request (on reverse switch press(p0.1)).
  - Window open/close request (on respective switch presses(p0.3,p0.7)).
- Receives responses from other nodes and reacts accordingly:
  - Blinks a reverse warning LED(p0.22) if an obstacle is detected within 15 cm.
  - Updates LED indicators or status displays when receiving window node responses.
- Operates **independently** in case of CAN or other node failure, ensuring core functionality.

### Reverse Node (Distance Sensor Node)
- Waits for a request message from the Main Node.
- When requested, reads analog distance data using **GP2D12 IR sensor** connected via ADC(CH0).
- Sends back the distance measurement to the Main Node.
- Makes **no autonomous decisions** — functions purely as a responder.

### Window Glass Control Node
- Waits for a control message from the Main Node.
- Upon receiving a command, it:
  - Adjusts simulated window position (using LEDs(p0.0-p0.7)).
  - Responds back to the Main Node with status or confirmation.
- Movement is done in steps (e.g., one LED ON per open/close command).

### Design: Fault-Tolerant Architecture

- Nodes act **only on valid messages intended for them**.
- **CAN messages are filtered** per node functionality.
- If any node is disconnected:
  - The rest of the system continues functioning.
  - The Main Node continues to operate and display temperature data.
- All inter-node logic is interrupt- and request-based — **no polling required**.

### Hardware Requirements

- LPC2129
- CAN Transceiver(MCP2551)
- LEDS
- SWITCHES
- LCD
- GP2D12
- DS18B20 Temperature Sensor
- USB To UART Converter

### Software Requirements

-EMBEDDED C-PROGRAMMING
- KEIL-C COMPILER
- FLASH MAGIC

### GPIO PINS

- LCD -> p0.8 - p0.15, RS -> p0.16, EN -> p0.18
- LEDs -> p0.0 - p0.7
- REVERSE NODE CONTROL SWITCH -> p0.1
- WINDOWS OPEN & CLOSE -> p0.3, p0.7
- ALERT LED -> p0.22
- DS18B20 TEMPERATURE SENSOR -> p1.16
- GP2D12 DISTANCE SENSOR -> p0.27(ADC CH0)  
