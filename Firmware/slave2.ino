#include <WiFi.h>
#include <esp_now.h>
#include <MPU9250_WE.h>
#include <SPI.h>
#include <math.h>

// Chip Select pins for 5 sensors
const int csPins[5] = {5, 17, 16, 4, 2};  // Update as per your wiring
MPU9250_WE sensors[5] = {
  MPU9250_WE(&SPI, csPins[0], true),
  MPU9250_WE(&SPI, csPins[1], true),
  MPU9250_WE(&SPI, csPins[2], true),
  MPU9250_WE(&SPI, csPins[3], true),
  MPU9250_WE(&SPI, csPins[4], true),
};

float smoothedAngles[5] = {0};
#define SMOOTHING_FACTOR 0.2

// MAC address of the Master ESP32
uint8_t masterAddress[] = {0x88, 0x13, 0xBF, 0x03, 0x7D, 0xF0};

void setupSensor(MPU9250_WE &sensor, int index) {
  Serial.print("Initializing Sensor ");
  Serial.println(index + 1);
  if (!sensor.init()) {
    Serial.print("Sensor ");
    Serial.print(index + 1);
    Serial.println(" not responding!");
  } else {
    Serial.print("Sensor ");
    Serial.print(index + 1);
    Serial.println(" connected.");
  }

  delay(500);
  sensor.autoOffsets();
  sensor.enableGyrDLPF();
  sensor.setGyrDLPF(MPU9250_DLPF_6);
  sensor.setSampleRateDivider(5);
  sensor.setGyrRange(MPU9250_GYRO_RANGE_250);
  sensor.setAccRange(MPU9250_ACC_RANGE_2G);
  sensor.enableAccDLPF(true);
  sensor.setAccDLPF(MPU9250_DLPF_6);
  delay(200);
}

float calculatePostureAngle(const xyzFloat &g) {
  float norm = sqrt(g.x * g.x + g.y * g.y + g.z * g.z);
  float x = g.x / norm;
  float y = g.y / norm;
  float z = g.z / norm;
  return atan2(-x, sqrt(y * y + z * z)) * 180.0 / PI;
}

void sendAngles() {
  String payload = "";
  for (int i = 0; i < 5; i++) {
    xyzFloat g = sensors[i].getGValues();
    float rawAngle = calculatePostureAngle(g);
    smoothedAngles[i] = (SMOOTHING_FACTOR * rawAngle) + ((1 - SMOOTHING_FACTOR) * smoothedAngles[i]);
    payload += String(smoothedAngles[i], 2);
    if (i < 4) payload += ",";
  }

  esp_now_send(masterAddress, (uint8_t *)payload.c_str(), payload.length());
  Serial.print("Sent: ");
  Serial.println(payload);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed!");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, masterAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  for (int i = 0; i < 5; i++) {
    setupSensor(sensors[i], i);
  }

  Serial.println("Slave 2 setup complete. Sending data...");
}

void loop() {
  sendAngles();
  delay(1000);  // 1-second interval
}