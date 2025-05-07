#  Body Posture Detection System -- B.Tech Final Year Porject

A **biomedical engineering project** focused on real-time body posture analysis using IMU sensors. This system is designed for applications in **healthcare diagnostics**, **physical rehabilitation**, **office ergonomics**, and **sports performance**.

> 🎓 **Funded by our college as part of an undergraduate biomedical research initiative.**

---

## 📌 Overview

This project uses **11 MPU9250 sensors** placed at critical body joints to monitor posture in real time. The system processes motion data using **ESP32 microcontrollers**, visualizes posture on a **cloud dashboard**, and lays the foundation for future machine learning-based analysis and correction.

---

## 🚀 Key Features

- ✅ **Real-Time Monitoring** using 9-axis IMU sensors  
- ✅ **ESP32-Based Architecture** with SPI and MQTT communication  
- ✅ **Cloud Dashboard** via [Adafruit IO](https://io.adafruit.com)  
- 🧠 **ML-Ready**: CNN/LSTM planned for advanced posture classification  
- 📊 **Real-Time Feedback** system in development

---

## 🔧 Hardware Components

- **Microcontrollers**: 3 × ESP32  
- **Sensors**: 11 × MPU9250 (IMU: accelerometer + gyroscope + magnetometer)  
- **Others**:
  - 40-pin FFC Dupont cables  
  - Soldering tools  
  - Elastic + Velcro straps for wearable setup  

---

## 🧱 System Architecture

1. **Data Collection**: 11 MPU9250 sensors gather movement/orientation data  
2. **Data Processing**: Two ESP32 boards collect sensor data and relay to a master ESP32  
3. **Transmission**: Data sent to the cloud via MQTT  
4. **Visualization**: Real-time metrics shown on Adafruit IO dashboard

---

## 🧪 Methodology

- 🎯 **Sensor Calibration**: Manual calibration for accuracy  
- 🤖 **Sensor Placement**: Head, neck, shoulders, back, knees, and ankles  
- 🧹 **Noise Reduction**: Moving Average + Kalman Filters applied  

### 🧠 Future ML Integration

- **CNNs** for posture classification  
- **LSTMs** for dynamic posture detection  
- **Edge AI**: TinyML models for on-device inference  

---

## 💻 Implementation

- **Language**: C++ (ESP32), Python (ML – future)  
- **Data Communication**: SPI (local), MQTT (cloud)  
- **Dashboard**: Built on [Adafruit IO](https://io.adafruit.com)  
- **ML Framework** (Planned): TensorFlow/Keras

---

## ✅ Current Results

- 🎯 **Accuracy**: 94.06% in detecting posture deviations  
- ⚡ **Latency**: Detects posture changes in under 1 second  
- 📌 **ML Expansion Plans**:
  - Use pretrained models (e.g., ResNet50, InceptionV3)  
  - Deploy models using TinyML on ESP32

---

## 🔮 Future Scope

- 🏥 **Healthcare**: Early detection of musculoskeletal issues  
- 🏃 **Fitness**: Posture correction for athletes  
- 🪑 **Ergonomics**: Smart workplace posture reminders  
- 📱 **Scalability**:
  - Mobile app integration  
  - Cloud ML deployment via TensorFlow Lite / AWS SageMaker

---

## 🔧 Next Steps

- ➕ **Add One More Sensor** (12 total) to improve posture detection accuracy  
- 🔄 **Update Code & Hardware Design** to support new sensor  
- 📈 **Expand Dataset** for robust ML training  
- 🧠 **Reinforcement Learning** for adaptive feedback  
- ⚙️ **Optimize ML Models** for low-power edge devices

---

## 👥 Team Members

| Name           | Role                          | Email                          | GitHub              |
|----------------|-------------------------------|--------------------------------|----------------------|
| Bhavya Jain    | Research, Sensor Calibration  | bhavyajain1210@gmail.com       | [Bhavyajain12](https://github.com/Bhavyajain12) |
| Satyam Mishra  | Hardware Integration, Testing | mishrasatyam0602@gmail.com     | [Satyam-Mishra0602](https://github.com/Satyam-Mishra0602) |
| Ram Prakash    | Firmware Development          | ramprakash130802@gmail.com     | -                    |

---

## 📚 References

- Dobrea, D.-M., & Dobrea, M.-C. (2018). *A wearable system for poor posture detection*. IEEE  
- Nistane, S., et al. (2021). *IoT-based posture rectification using biofeedback*. IEEE  
- Severin, I.-C. (2020). *Head posture analysis with inertial sensors and ML*. IEEE  

