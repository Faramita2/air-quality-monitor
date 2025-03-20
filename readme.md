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

### Data Visualization

To analyze and visualize the collected air quality and rhinitis symptom data, this project includes a Python script (`main.py`) that generates various plots using data exported from ThingSpeak.

#### Prerequisites

- **Python 3**: Ensure you have Python 3 installed on your system.
- **Required Libraries**: Install the following Python libraries:
  ```bash
  pip install pandas matplotlib seaborn
  ```

#### Steps

1. **Export Data from ThingSpeak**:

   - Log into your ThingSpeak account.
   - Navigate to the air quality channel (e.g., Channel ID 2865931) and rhinitis symptom channel (e.g., Channel ID 2868847).
   - Go to "Data Import / Export" and export the data as CSV files.
   - Save the files as `air_quality.csv` and `rhinitis.csv` in the `./data/` directory of your project.

2. **Set Up the Environment**:

   - (Optional) Create a virtual environment to isolate dependencies:
     ```bash
     python3 -m venv env
     source env/bin/activate  # macOS/Linux
     env\Scripts\activate     # Windows
     ```
   - Install the required libraries within the virtual environment:
     ```bash
     pip install pandas matplotlib seaborn
     ```

3. **Run the Visualization Script**:

   - Ensure the CSV files are placed in the `./data/` directory relative to `main.py`.
   - Run the script:
     ```bash
     python main.py
     ```
   - The script will generate:
     - **Three Vertical Plots**: Temperature & Humidity (line plot), Rhinitis Symptoms (stacked bar chart), CO2 & TVOC (line plot).
     - **Scatter Plots**: Eight subplots showing relationships between air quality factors and rhinitis symptoms with regression lines.
     - **Correlation Heatmap**: A heatmap showing Spearman correlation coefficients between all variables.

4. **Interpret the Results**:
   - Check the console output for time range information to verify data alignment.
   - Review the generated plots to identify trends and correlations (e.g., TVOC peaks vs. sneezing events).

#### Notes

- If the time range in the plots (especially the rhinitis bar chart) is incorrect, verify the `created_at` timestamps in your CSV files.
- Adjust the file paths in `main.py` (e.g., `air_quality_file` and `rhinitis_file`) if your CSV files are stored elsewhere.

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

本项目是为计算机考研电子信息专业复试准备的。作为一名跨专业考生，我通过构建一个基于 ESP32-S3 主控芯片的空气质量监测系统，旨在提升对电子信息领域的理解，并积累与专业相关的项目经验。

该项目的主要目标是利用多种传感器（如温度、湿度、CO2、TVOC、PM2.5 等）收集环境数据，将数据显示在 LCD 屏幕上，上传到 ThingSpeak 物联网平台，并结合个人健康事件（如打喷嚏和流鼻涕）进行数据分析。

### 动机

作为一名跨专业考生，我希望通过实践项目来增强对电子技术和嵌入式系统的理解。这个项目是我迈向传感器集成、数据处理和物联网应用的第一步。

### 功能

- **传感器集成**:
  - SHT31：温湿度传感器
  - CCS811：CO2 和 TVOC 传感器
  - PMS7003：颗粒物传感器（待办）
  - MH-Z19B：CO2 传感器（待办）
- **数据显示**：实时显示在 LCD 屏幕上。
- **数据上传**：将传感器数据上传到 ThingSpeak 进行存储和分析。
- **健康事件记录**：通过网页表单记录打喷嚏和流鼻涕事件，并提交到 ThingSpeak。
- **未来改进**：
  - 将环境数据与健康事件关联。
  - 添加机器学习模型以预测健康结果。
  - 扩展支持的传感器种类。

### 硬件组件

- **微控制器**：ESP32-S3
- **传感器**：
  - SHT31（温湿度）
  - CCS811（CO2 和 TVOC）
  - PMS7003（PM2.5）（计划中）
  - MH-Z19B（CO2）（计划中）
- **显示屏**：TFT LCD 屏幕（ST7796 驱动）
- **连接性**：Wi-Fi（ESP32 内置）

### 软件栈

- **开发环境**：Arduino IDE
- **库**：
  - Adafruit_CCS811
  - Adafruit_SHT31
  - LVGL（轻量级图形库）
  - HTTPClient 用于数据上传
- **物联网平台**：ThingSpeak

### 安装与设置

1. 克隆仓库：
   ```bash
   git clone https://github.com/yourusername/air-quality-monitor.git
   ```
2. 使用 Arduino 库管理器安装所需的库：
   - Adafruit_CCS811
   - Adafruit_SHT31
   - LVGL
3. 在`Config.h`文件中更新您的 Wi-Fi 凭据和 ThingSpeak API 密钥。
4. 使用 Arduino IDE 将代码上传到您的 ESP32-S3 开发板。
5. 访问网页界面记录打喷嚏和流鼻涕事件。

### 数据可视化

为了分析和可视化收集到的空气质量和鼻炎症状数据，本项目包含一个 Python 脚本（`main.py`），用于从 ThingSpeak 导出的数据生成多种图表。

#### 前提条件

- **Python 3**：确保系统中已安装 Python 3。
- **所需库**：安装以下 Python 库：
  ```bash
  pip install pandas matplotlib seaborn
  ```

#### 操作步骤

1. **从 ThingSpeak 导出数据**：

   - 登录 ThingSpeak 账户。
   - 进入空气质量频道（例如 Channel ID 2865931）和鼻炎症状频道（例如 Channel ID 2868847）。
   - 转到“Data Import / Export”，将数据导出为 CSV 文件。
   - 将文件保存为 `./data/` 目录下的 `air_quality.csv` 和 `rhinitis.csv`。

2. **设置环境**：

   - （可选）创建一个虚拟环境以隔离依赖：
     ```bash -->
     python3 -m venv env
     source env/bin/activate  # macOS/Linux
     env\Scripts\activate     # Windows
     ```
   - 在虚拟环境中安装所需库：
     ```bash
     pip install pandas matplotlib seaborn
     ```

3. **运行可视化脚本**：

   - 确保 CSV 文件已放置在相对于 `main.py` 的 `./data/` 目录中。
   - 运行脚本：
     ```bash
     python main.py
     ```
   - 脚本将生成：
     - **三张纵向图表**：温度与湿度（折线图）、鼻炎症状（堆叠柱状图）、CO2 与 TVOC（折线图）。
     - **散点图**：八个子图，显示空气质量因素与鼻炎症状之间的关系，并带有回归线。
     - **相关性热图**：显示所有变量之间 Spearman 相关系数的热图。

4. **解读结果**：
   - 检查控制台输出的时间范围信息，验证数据是否对齐。
   - 查看生成的图表，识别趋势和相关性（例如 TVOC 峰值与打喷嚏事件的对应关系）。

#### 注意事项

- 如果图表（特别是鼻炎柱状图）的时间范围不正确，请检查 CSV 文件中的 `created_at` 时间戳。
- 如果 CSV 文件存储在其他位置，请调整 `main.py` 中的文件路径（例如 `air_quality_file` 和 `rhinitis_file`）。

### 待办事项

- **传感器集成**：
  - 集成 PMS7003（颗粒物传感器）。
  - 集成 MH-Z19B（CO2 传感器）。
- **数据分析**：
  - 实现环境数据与健康事件的相关性分析。
  - 开发基于环境条件预测健康结果的机器学习模型。
- **用户界面**：
  - 改进用户界面以提升可用性和美观性。
  - 为网页界面添加更多互动功能以便更容易记录数据。
- **系统增强**：
  - 优化内存使用以提高长期稳定性。
  - 当某些阈值（例如高 CO2 水平）被超过时，实现警报系统。
  - 使用 Grafana 或 Tableau 等工具创建交互式仪表板以更好地可视化数据。
- **移动应用**：
  - 开发一个移动应用程序以远程监控数据。
- **文档**：
  - 包括每个模块的详细文档，使其他人更容易理解和贡献。
  - 提供全面的指南以设置和使用该系统。

### 贡献

欢迎通过提交 Pull Request 或报告问题来贡献此项目。您的反馈对我们非常重要！

### 许可证

本项目采用 MIT 许可证。详情请参阅[LICENSE](LICENSE)文件。
