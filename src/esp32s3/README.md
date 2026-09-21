# ESP32-S3 firmware

Open `esp32s3.ino` in Arduino IDE and select your ESP32-S3 board from the Espressif **esp32** board package. Install the **INA226** library by Rob Tillaart. The BLE headers come with the Espressif Arduino core.

Connect the INA226 to the ESP32-S3 using 3.3 V, GND, SDA, and SCL. The sketch uses GPIO 8 for SDA and GPIO 9 for SCL; change `I2C_SDA_PIN` and `I2C_SCL_PIN` if your board uses different pins. The INA226 address is `0x40`, and the calibration assumes a 0.1 ohm shunt and 0.5 A maximum current. Confirm the actual shunt value before relying on current or resistance readings.

The device advertises as `SMART_MAT` and provides Nordic UART Service. It sends a 16-byte notification every 100 ms while connected: resistance in ohms, bus voltage in volts, current in **milliamps**, and `millis()` as a 32-bit timestamp. Resistance is `-1` when measured current is zero. The existing Python logger can decode the packet; update its `DEVICE_ADDRESS` to the ESP32-S3 address found with `logging/scanner.py`. The logger's `Current (A)` CSV heading is inaccurate for this packet format: the transmitted value is in milliamps.

If INA226 initialization fails, the sketch reports the error over serial and does not send measurements. BLE advertising remains active.
