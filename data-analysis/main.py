import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from matplotlib.dates import DateFormatter, DayLocator

sns.set(font_scale=1.2)

# 读取 CSV 文件
air_quality_file = './data/air_quality.csv'
rhinitis_file = './data/rhinitis.csv'

air_df = pd.read_csv(air_quality_file)
rhinitis_df = pd.read_csv(rhinitis_file)

# 选择并重命名列
air_df = air_df[['created_at', 'field1', 'field2', 'field3', 'field4']]
air_df.columns = ['created_at', 'Temperature', 'Humidity', 'CO2', 'TVOC']

rhinitis_df = rhinitis_df[['created_at', 'field1', 'field2']]
rhinitis_df.columns = ['created_at', 'Sneezing', 'RunnyNose']

# 转换为 datetime 格式
air_df['created_at'] = pd.to_datetime(air_df['created_at'])
rhinitis_df['created_at'] = pd.to_datetime(rhinitis_df['created_at'])

# 调试：打印原始数据的时间范围
print("Air Quality Raw Time Range:", air_df['created_at'].min(), air_df['created_at'].max())
print("Rhinitis Raw Time Range:", rhinitis_df['created_at'].min(), rhinitis_df['created_at'].max())

# 设置索引并按天聚合
air_df.set_index('created_at', inplace=True)
rhinitis_df.set_index('created_at', inplace=True)

air_daily = air_df.resample('D').mean()
rhinitis_daily = rhinitis_df.resample('D').sum()

# 以鼻炎数据的原始时间范围为基准
min_rhinitis_time = rhinitis_df.index.min().floor('D')  # 从 3 月 8 日 00:00 开始
max_rhinitis_time = rhinitis_df.index.max().ceil('D')   # 到 3 月 20 日 23:59
air_daily = air_daily.loc[min_rhinitis_time:max_rhinitis_time]
rhinitis_daily = rhinitis_daily.loc[min_rhinitis_time:max_rhinitis_time]

# 调试：打印聚合后数据和 NaN 情况
print("Air Quality Aggregated Time Range:", air_daily.index.min(), air_daily.index.max())
print("Rhinitis Aggregated Time Range:", rhinitis_daily.index.min(), rhinitis_daily.index.max())
print("Rhinitis Daily Data (with NaN check):\n", rhinitis_daily.head(10))

# 合并数据用于相关性分析
combined_df = pd.concat([air_daily, rhinitis_daily], axis=1)

# 计算相关性矩阵
correlation_matrix = combined_df.corr(method='spearman')

# 统一 x 轴标签格式
date_formatter = DateFormatter('%m/%d')

# 创建三张主图，纵向排列
fig, axes = plt.subplots(3, 1, figsize=(12, 9), sharex=True)  # 纵向 3 行 1 列，共享 x 轴

# 第一张：温度 & 湿度折线图
axes[0].plot(air_daily.index, air_daily['Temperature'], label='Temperature (°C)', color='b', marker='o')
axes[0].plot(air_daily.index, air_daily['Humidity'], label='Humidity (%)', color='g', marker='s')
axes[0].set_ylabel('Temp / Humidity')
axes[0].set_title('Temperature and Humidity Trends')
axes[0].legend()
axes[0].grid(True)

# 第二张：鼻炎症状柱状图（放在中间）
axes[1].bar(rhinitis_daily.index, rhinitis_daily['Sneezing'], label='Sneezing', color='b', alpha=0.7)
axes[1].bar(rhinitis_daily.index, rhinitis_daily['RunnyNose'], label='RunnyNose', color='g', alpha=0.7, bottom=rhinitis_daily['Sneezing'])
axes[1].set_ylabel('Count')
axes[1].set_title('Rhinitis Symptoms Trends')
axes[1].legend()
axes[1].grid(True)

# 第三张：CO2 & TVOC 折线图
axes[2].plot(air_daily.index, air_daily['CO2'], label='CO2 (ppm)', color='r', marker='^')
axes[2].plot(air_daily.index, air_daily['TVOC'], label='TVOC (ppb)', color='m', marker='d')
axes[2].set_xlabel('Date')
axes[2].set_ylabel('CO2 / TVOC')
axes[2].set_title('CO2 and TVOC Trends')
axes[2].legend()
axes[2].grid(True)

# 设置日期格式 & 旋转 x 轴标签
axes[2].xaxis.set_major_formatter(date_formatter)
axes[2].xaxis.set_major_locator(DayLocator())  # 确保每天都显示日期
plt.xticks(rotation=45)

plt.tight_layout()  

# 图表 4：散点图（添加回归线）
fig, axes = plt.subplots(2, 4, figsize=(16, 8))
axes = axes.flatten()
plot_pairs = [
    ('Temperature', 'Sneezing'), ('Humidity', 'Sneezing'), ('CO2', 'Sneezing'), ('TVOC', 'Sneezing'),
    ('Temperature', 'RunnyNose'), ('Humidity', 'RunnyNose'), ('CO2', 'RunnyNose'), ('TVOC', 'RunnyNose')
]
for idx, (x_col, y_col) in enumerate(plot_pairs):
    sns.regplot(data=combined_df, x=x_col, y=y_col, ax=axes[idx], scatter_kws={'s': 50}, line_kws={'color': 'red'})
    axes[idx].set_title(f'{x_col} vs {y_col}')
    axes[idx].grid(True)
plt.tight_layout()

# 图表 5：相关性热图（简略字母标签）
plt.figure(figsize=(8, 6))
short_labels = ['Temp', 'Hum', 'CO2', 'TVOC', 'Snz', 'Run']  # 简略标签
sns.heatmap(correlation_matrix, annot=True, cmap='coolwarm', vmin=-1, vmax=1, center=0, fmt='.2f',
            xticklabels=short_labels, yticklabels=short_labels)
plt.title('Correlation Heatmap')
plt.xticks(rotation=0)  # X 轴标签水平放置
plt.tight_layout()

plt.show()