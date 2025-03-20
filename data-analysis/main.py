import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from matplotlib.dates import DateFormatter, DayLocator

sns.set(font_scale=1.2)

# 读取清洗后的日级数据
air_quality_file = './data/air_quality_cleaned_daily.csv'
rhinitis_file = './data/rhinitis_cleaned_daily.csv'

air_df = pd.read_csv(air_quality_file, parse_dates=['created_at'])
rhinitis_df = pd.read_csv(rhinitis_file, parse_dates=['created_at'])

# 设置索引
air_df.set_index('created_at', inplace=True)
rhinitis_df.set_index('created_at', inplace=True)

# 合并数据用于相关性分析
combined_df = pd.concat([air_df, rhinitis_df], axis=1)

# 计算相关性矩阵
correlation_matrix = combined_df.corr(method='spearman')

# 统一 x 轴标签格式
date_formatter = DateFormatter('%m/%d')

# 创建三张主图，纵向排列
fig, axes = plt.subplots(3, 1, figsize=(12, 9), sharex=True)

# 第一张：温度 & 湿度折线图
axes[0].plot(air_df.index, air_df['Temperature'], label='Temperature (°C)', color='b', marker='o')
axes[0].plot(air_df.index, air_df['Humidity'], label='Humidity (%)', color='g', marker='s')
axes[0].set_ylabel('Temp / Humidity')
axes[0].set_title('Temperature and Humidity Trends')
axes[0].legend()
axes[0].grid(True)

# 第二张：鼻炎症状柱状图
axes[1].bar(rhinitis_df.index, rhinitis_df['Sneezing'], label='Sneezing', color='b', alpha=0.7)
axes[1].bar(rhinitis_df.index, rhinitis_df['RunnyNose'], label='RunnyNose', color='g', alpha=0.7, bottom=rhinitis_df['Sneezing'])
axes[1].set_ylabel('Count')
axes[1].set_title('Rhinitis Symptoms Trends')
axes[1].legend()
axes[1].grid(True)

# 第三张：TVOC 折线图
axes[2].plot(air_df.index, air_df['CO2'], label='CO2 (ppm)', color='r', marker='^')
axes[2].plot(air_df.index, air_df['TVOC'], label='TVOC (ppb)', color='m', marker='d')
axes[2].set_xlabel('Date')
axes[2].set_ylabel('CO2 / TVOC')
axes[2].set_title('CO2 and TVOC Trends')
axes[2].legend()
axes[2].grid(True)

# 设置日期格式 & 旋转 x 轴标签
axes[2].xaxis.set_major_formatter(date_formatter)
axes[2].xaxis.set_major_locator(DayLocator())
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig('data/trends_cleaned.png')
plt.close()

# 图表 4：散点图
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
plt.savefig('data/scatter_cleaned.png')
plt.close()

# 图表 5：相关性热图
plt.figure(figsize=(8, 6))
short_labels = ['Temp', 'Hum', 'CO2', 'TVOC', 'Snz', 'Run']
sns.heatmap(correlation_matrix, annot=True, cmap='coolwarm', vmin=-1, vmax=1, center=0, fmt='.2f',
            xticklabels=short_labels, yticklabels=short_labels)
plt.title('Correlation Heatmap')
plt.xticks(rotation=0)
plt.tight_layout()
plt.savefig('data/heatmap_cleaned.png')
plt.close()