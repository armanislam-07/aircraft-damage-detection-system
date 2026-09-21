#include <Arduino.h>
#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <Wire.h>
#include <INA226.h>

// Set these to the GPIOs connected to the INA226 on your ESP32-S3 board.
constexpr int I2C_SDA_PIN = 8;
constexpr int I2C_SCL_PIN = 9;
constexpr uint8_t INA226_ADDRESS = 0x40;
constexpr uint32_t SAMPLE_INTERVAL_MS = 100;

constexpr char DEVICE_NAME[] = "SMART_MAT";
constexpr char UART_SERVICE_UUID[] = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E";
constexpr char UART_RX_UUID[] = "6E400002-B5A3-F393-E0A9-E50E24DCCA9E";
constexpr char UART_TX_UUID[] = "6E400003-B5A3-F393-E0A9-E50E24DCCA9E";

// Matches logging/logging_resistance_data_packet.py: struct.unpack("fffI", data).
struct __attribute__((packed)) Packet {
  float resistanceOhms;
  float busVoltageVolts;
  float currentMilliAmps;
  uint32_t timestampMs;
};
static_assert(sizeof(Packet) == 16, "BLE packet must be 16 bytes");

INA226 ina(INA226_ADDRESS);
BLEServer *server = nullptr;
BLECharacteristic *txCharacteristic = nullptr;
volatile bool connected = false;
volatile bool restartAdvertising = false;
bool sensorReady = false;
uint32_t lastSampleMs = 0;

class ServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *server) override {
    connected = true;
  }

  void onDisconnect(BLEServer *server) override {
    connected = false;
    restartAdvertising = true;
  }
};

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  sensorReady = ina.begin();
  if (sensorReady) {
    // Same averaging and 0.5 A / 0.1 ohm shunt calibration as src/main.ino.
    ina.setAverage(2);
    delay(100);
    sensorReady = (ina.setMaxCurrentShunt(0.5f, 0.1f) == 0);
  }
  if (!sensorReady) {
    Serial.println("INA226 initialization or calibration failed; check wiring and shunt value.");
  }

  BLEDevice::init(DEVICE_NAME);
  server = BLEDevice::createServer();
  server->setCallbacks(new ServerCallbacks());
  BLEService *service = server->createService(UART_SERVICE_UUID);
  txCharacteristic = service->createCharacteristic(
      UART_TX_UUID, BLECharacteristic::PROPERTY_NOTIFY);
  txCharacteristic->addDescriptor(new BLE2902());
  service->createCharacteristic(UART_RX_UUID, BLECharacteristic::PROPERTY_WRITE);
  service->start();

  BLEAdvertising *advertising = server->getAdvertising();
  advertising->addServiceUUID(UART_SERVICE_UUID);
  advertising->start();
  Serial.println("SMART_MAT BLE UART ready");
}

void loop() {
  if (restartAdvertising) {
    restartAdvertising = false;
    server->startAdvertising();
  }

  if (!connected || !sensorReady) {
    delay(10);
    return;
  }

  const uint32_t now = millis();
  if (now - lastSampleMs < SAMPLE_INTERVAL_MS) {
    delay(1);
    return;
  }
  lastSampleMs = now;

  const float voltage = ina.getBusVoltage();
  const float current = ina.getCurrent_mA();
  Packet packet = {
      current != 0.0f ? voltage / (current / 1000.0f) : -1.0f,
      voltage,
      current,
      now,
  };
  txCharacteristic->setValue(reinterpret_cast<uint8_t *>(&packet), sizeof(packet));
  txCharacteristic->notify();
}
