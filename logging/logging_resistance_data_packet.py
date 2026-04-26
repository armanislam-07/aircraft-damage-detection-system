import asyncio
from bleak import BleakClient
import struct

#This is the device address of the NRF52840 specific to your current device
#Change if using a different setup
DEVICE_ADDRESS = "F8:56:1C:1F:C6:2D"

# Nordic UART Service UUID (standard for BLEUart)
UART_RX_UUID = "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

log_file = "ble_log.txt"
buffer =""

def callback(sender, data):
    if len(data) == 16:
        r, v, i, t= struct.unpack("fffI", data)
        line = f"T:{t}ms, R:{r:.3f},V:{v:.3f},I:{i:.3f}"

        print(line)
        with open(log_file, "a") as f:
            f.write(line + "\n")

async def main():
    async with BleakClient(DEVICE_ADDRESS) as client:
        print("Connected!")

        await client.start_notify(UART_RX_UUID, callback)

        print("Logging started")

        while True:
            if not client.is_connected:
                print("Device Disconnected")
                break
            await asyncio.sleep(1)

asyncio.run(main())