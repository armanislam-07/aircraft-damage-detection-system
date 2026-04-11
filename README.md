    

# SMART MATERIALS

## Overview

Smart materials or metamaterials are responsive substances designed to alter their properties in a controlled reversible manner. How does this relate to engineering? If we are able to control or understand how these properties change, we can use these materials as low cost sensors.

In this project we explore the use of Carbon Nano Fibers (CNF) and Polylactic acid (PLA) for damage detection.

### Idea

When the material encounters stress, the resistance of the material changes. This project aims to detect the resistance change and map out how much damage the aircraft takes

### Organization

Update! The project has moved from the NRF24L01 to the NRF52840. This completely changes the archetecture of the project and the current organization will be as follows

-> logging
    - Contains the python files neccesary for capturing the BLE signals that the NRF52840 transmits
-> src
    - Contains the .ino and .cpp files necessary for the system
        - Currently the system is designed in arduino and C++ but I am planning on transferring the codebase into C++ and Zephyr.

### Materials

- NRF52840
- INA 226
- CNF/PLA Sensors







### Archive Information of the old system

#### Materials

- NRF24L01
- ATmega328p
- INA 226
- CNF/PLA Sensors

#### System Design

1. Home Base

   - System on theh ground receiving data transmitted dfrom the drone about the resistance measurments and logs the data.
2. Onboard Sensor System

   - System on the drone calculating resistance values and transmitting them to home base.
