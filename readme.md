# Air Quality Monitor Project

[English](#english-version) | [中文](#chinese-version)

---

## English Version

### Overview

This project is designed as a preparation for the postgraduate entrance examination in Computer Science, specifically for the Electronics and Information Engineering major. As a cross-disciplinary candidate, I aimed to deepen my understanding of electronics and gain hands-on experience by building an air quality monitoring system using an ESP32-S3 microcontroller.

The primary goal of this project is to collect environmental data (temperature, humidity, CO2, TVOC, PM2.5, etc.) using various sensors, display the data on an LCD screen, upload it to the ThingSpeak IoT platform, and analyze the data alongside personal health-related events like sneezing and runny nose occurrences.

### Motivation

As a cross-disciplinary student preparing for my graduate studies, I wanted to strengthen my practical skills in electronics and embedded systems. This project serves as a stepping stone toward understanding sensor integration, data processing, and IoT applications.

### Features

- **Sensor Integration**:
  - SHT31: Temperature and Humidity Sensor
  - CCS811: CO2 and TVOC Sensor
  - PMS7003: Particulate Matter Sensor (TODO)
  - MH-Z19B: CO2 Sensor (TODO)
- **Data Display**: Real-time data visualization on an LCD screen.
- **Data Upload**: Upload sensor data to ThingSpeak for storage and analysis.
- **Health Event Tracking**: Record sneezing and runny nose events via a web form and submit them to ThingSpeak.
- **Future Enhancements**:
  - Correlate environmental data with health events.
  - Add machine learning models to predict health outcomes based on environmental conditions.
  - Expand the range of supported sensors.

### Hardware Components

- **Microcontroller**: ESP32-S3
- **Sensors**:
  - SHT31 (Temperature & Humidity)
  - CCS811 (CO2 & TVOC)
  - PMS7003 (PM2.5) (Planned)
  - MH-Z19B (CO2) (Planned)
- **Display**: TFT LCD Screen (ST7796 Driver)
- **Connectivity**: Wi-Fi (ESP32 Built-in)

### Software Stack

- **Development Environment**: Arduino IDE
- **Libraries**:
  - Adafruit_CCS811
  - Adafruit_SHT31
  - LVGL (Light and Versatile Graphics Library)
  - HTTPClient for data uploads
- **IoT Platform**: ThingSpeak

### Installation and Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/air-quality-monitor.git
   ```
2. Install the required libraries via the Arduino Library Manager:
   - Adafruit_CCS811
   - Adafruit_SHT31
   - LVGL
3. Update the `Config.h` file with your Wi-Fi credentials and ThingSpeak API keys.
4. Upload the code to your ESP32-S3 board using the Arduino IDE.
5. Access the web interface to log sneezing and runny nose events.

### TODO List

- **Sensor Integration**:
  - Integrate PMS7003 (Particulate Matter Sensor).
  - Integrate MH-Z19B (CO2 Sensor).

- **Data Analysis**:
  - Implement correlation analysis between environmental data and health events.
  - Develop machine learning models to predict health outcomes based on environmental conditions.

- **User Interface**:
  - Improve the user interface for better usability and aesthetics.
  - Add more interactive features to the web interface for easier data logging.

- **System Enhancements**:
  - Optimize memory usage for long-term stability.
  - Implement an alert system when certain thresholds (e.g., high CO2 levels) are exceeded.
  - Create an interactive dashboard using tools like Grafana or Tableau for better data visualization.

- **Mobile Application**:
  - Develop a mobile app to monitor the data remotely.

- **Documentation**:
  - Include detailed documentation for each module to make it easier for others to understand and contribute.
  - Provide comprehensive guides for setting up and using the system.

### Contribution

Feel free to contribute to this project by submitting pull requests or reporting issues. Your feedback is highly appreciated!

### License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Chinese Version

### 概述

本项目是为计算机考研电子信息专业复试准备的。作为一名跨专业考生，我通过构建一个基于ESP32-S3主控芯片的空气质量监测系统，旨在提升对电子信息领域的理解，并积累与专业相关的项目经验。

该项目的主要目标是利用多种传感器（如温度、湿度、CO2、TVOC、PM2.5等）收集环境数据，将数据显示在LCD屏幕上，上传到ThingSpeak物联网平台，并结合个人健康事件（如打喷嚏和流鼻涕）进行数据分析。

### 动机

作为一名跨专业考生，我希望通过实践项目来增强对电子技术和嵌入式系统的理解。这个项目是我迈向传感器集成、数据处理和物联网应用的第一步。

### 功能

- **传感器集成**：
  - SHT31：温湿度传感器
  - CCS811：CO2和TVOC传感器
  - PMS7003：颗粒物传感器（待办）
  - MH-Z19B：CO2传感器（待办）
- **数据显示**：实时显示在LCD屏幕上。
- **数据上传**：将传感器数据上传到ThingSpeak进行存储和分析。
- **健康事件记录**：通过网页表单记录打喷嚏和流鼻涕事件，并提交到ThingSpeak。
- **未来改进**：
  - 将环境数据与健康事件关联。
  - 添加机器学习模型以预测健康结果。
  - 扩展支持的传感器种类。

### 硬件组件

- **微控制器**：ESP32-S3
- **传感器**：
  - SHT31（温湿度）
  - CCS811（CO2和TVOC）
  - PMS7003（PM2.5）（计划中）
  - MH-Z19B（CO2）（计划中）
- **显示屏**：TFT LCD屏幕（ST7796驱动）
- **连接性**：Wi-Fi（ESP32内置）

### 软件栈

- **开发环境**：Arduino IDE
- **库**：
  - Adafruit_CCS811
  - Adafruit_SHT31
  - LVGL（轻量级图形库）
  - HTTPClient用于数据上传
- **物联网平台**：ThingSpeak

### 安装与设置

1. 克隆仓库：
   ```bash
   git clone https://github.com/yourusername/air-quality-monitor.git
   ```
2. 使用Arduino库管理器安装所需的库：
   - Adafruit_CCS811
   - Adafruit_SHT31
   - LVGL
3. 在`Config.h`文件中更新您的Wi-Fi凭据和ThingSpeak API密钥。
4. 使用Arduino IDE将代码上传到您的ESP32-S3开发板。
5. 访问网页界面记录打喷嚏和流鼻涕事件。

### 待办事项

- **传感器集成**：
  - 集成PMS7003（颗粒物传感器）。
  - 集成MH-Z19B（CO2传感器）。

- **数据分析**：
  - 实现环境数据与健康事件的相关性分析。
  - 开发基于环境条件预测健康结果的机器学习模型。

- **用户界面**：
  - 改进用户界面以提升可用性和美观性。
  - 为网页界面添加更多互动功能以便更容易记录数据。

- **系统增强**：
  - 优化内存使用以提高长期稳定性。
  - 当某些阈值（例如高CO2水平）被超过时，实现警报系统。
  - 使用Grafana或Tableau等工具创建交互式仪表板以更好地可视化数据。

- **移动应用**：
  - 开发一个移动应用程序以远程监控数据。

- **文档**：
  - 包括每个模块的详细文档，使其他人更容易理解和贡献。
  - 提供全面的指南以设置和使用该系统。

### 贡献

欢迎通过提交Pull Request或报告问题来贡献此项目。您的反馈对我们非常重要！

### 许可证

本项目采用MIT许可证。详情请参阅[LICENSE](LICENSE)文件。