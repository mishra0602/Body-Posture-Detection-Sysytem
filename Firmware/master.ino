#include <WiFi.h>
#include <esp_now.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// WiFi Credentials
#define WIFI_SSID "Your_WiFi_SSID"
#define WIFI_PASS "Your_WiFi_Password"

// Adafruit IO Configuration
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "Your_Adafruit_Username"
#define AIO_KEY         "Your_Adafruit_Key"

// MAC Addresses of Slaves
uint8_t slave1Address[] = {0x08, 0xA6, 0xF7, 0xBC, 0x98, 0xA8};  // Upper Body (6 sensors)
uint8_t slave2Address[] = {0x2C, 0xBC, 0xBB, 0x0C, 0x63, 0x14};  // Lower Body (5 sensors)

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish postureFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/body-posture");

void connectWiFi() {
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {
  int8_t ret;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
  }
  Serial.println("MQTT Connected!");
}

void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *data, int len) {
  const uint8_t *mac = recv_info->src_addr;
  char macStr[18];
  
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

  String receivedData = "";
  for (int i = 0; i < len; i++) {
    receivedData += (char)data[i];
  }

  // Create JSON payload
  String payload = "{";
  payload += "\"mac\":\"" + String(macStr) + "\",";
  payload += "\"data\":\"" + receivedData + "\"";
  payload += "}";

  // Publish to Adafruit IO
  if (!postureFeed.publish(payload.c_str())) {
    Serial.println("Failed to publish to Adafruit IO");
  } else {
    Serial.println("Data published to Adafruit IO");
  }

  // Serial output
  if (memcmp(mac, slave1Address, 6) == 0) {
    Serial.println("[Upper Body - Slave 1] Angles: " + receivedData);
  } else if (memcmp(mac, slave2Address, 6) == 0) {
    Serial.println("[Lower Body - Slave 2] Angles: " + receivedData);
  } else {
    Serial.println("Unknown sender (" + String(macStr) + ") Data: " + receivedData);
  }
}

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  connectWiFi();
  
  // Initialize ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed!");
    return;
  }
  
  // Register callback
  esp_now_register_recv_cb(OnDataRecv);
  
  // Connect to MQTT
  connectMQTT();
  
  Serial.println("Master ESP32 ready (ESP-NOW + Adafruit IO)");
}

void loop() {
  // Maintain MQTT connection
  if (!mqtt.ping()) {
    mqtt.disconnect();
    connectMQTT();
  }
  
  delay(1000); // Maintain connection without blocking
}