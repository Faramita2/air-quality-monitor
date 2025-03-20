import pandas as pd

# 读取数据
air_df = pd.read_csv('./data/air_quality.csv')
rhinitis_df = pd.read_csv('./data/rhinitis.csv')

# 选择空气质量数据的所需列
air_df = air_df[['created_at', 'field1', 'field2', 'field3', 'field4']]
air_df.columns = ['created_at', 'Temperature', 'Humidity', 'CO2', 'TVOC']

# 选择鼻炎症状数据的所需列
rhinitis_df = rhinitis_df[['created_at', 'field1', 'field2']]
rhinitis_df.columns = ['created_at', 'Sneezing', 'RunnyNose']

# 转时间格式
air_df['created_at'] = pd.to_datetime(air_df['created_at'])
rhinitis_df['created_at'] = pd.to_datetime(rhinitis_df['created_at'])

# 清洗异常值
air_df_clean = air_df[
    (air_df['Temperature'].between(15, 35)) &
    (air_df['Humidity'].between(0, 100)) &
    (air_df['CO2'].between(400, 2000, inclusive='both')) &
    (air_df['TVOC'].between(0, 500, inclusive='both'))  # 收紧 TVOC 阈值
].dropna(subset=['Temperature', 'Humidity'])

print("清洗后数据量:", len(air_df_clean))
print("清洗后 CO2 和 TVOC 统计:\n", air_df_clean[['CO2', 'TVOC']].describe())

# 按分钟（5分钟）、小时、日聚合和平滑
air_minute = air_df_clean.set_index('created_at').resample('5T').mean()
air_minute_smooth = air_minute.rolling(window=6, min_periods=1).mean()  # 30 分钟平滑
rhinitis_minute = rhinitis_df.set_index('created_at').resample('5T').sum()

air_hourly = air_df_clean.set_index('created_at').resample('H').mean()
air_hourly_smooth = air_hourly.rolling(window=3, min_periods=1).mean()  # 3 小时平滑
rhinitis_hourly = rhinitis_df.set_index('created_at').resample('H').sum()

air_daily = air_df_clean.set_index('created_at').resample('D').mean()
air_daily_smooth = air_daily.rolling(window=1, min_periods=1).mean()  # 1 天平滑（避免过度平滑）
rhinitis_daily = rhinitis_df.set_index('created_at').resample('D').sum()

# 计算相关性
combined_minute = pd.concat([air_minute_smooth, rhinitis_minute], axis=1)
combined_hourly = pd.concat([air_hourly_smooth, rhinitis_hourly], axis=1)
combined_daily = pd.concat([air_daily_smooth, rhinitis_daily], axis=1)

print("分钟级相关性:\n", combined_minute.corr(method='spearman'))
print("小时级相关性:\n", combined_hourly.corr(method='spearman'))
print("日级相关性:\n", combined_daily.corr(method='spearman'))

# 保存清洗后的数据
air_minute_smooth.to_csv('./data/air_quality_cleaned_minute.csv')
rhinitis_minute.to_csv('./data/rhinitis_cleaned_minute.csv')
air_hourly_smooth.to_csv('./data/air_quality_cleaned_hourly.csv')
rhinitis_hourly.to_csv('./data/rhinitis_cleaned_hourly.csv')
air_daily_smooth.to_csv('./data/air_quality_cleaned_daily.csv')
rhinitis_daily.to_csv('./data/rhinitis_cleaned_daily.csv')

# 打印原始和清洗后的样本
print("原始 CO2 和 TVOC (前20行):\n", air_df[['CO2', 'TVOC']].head(20))
print("清洗后 CO2 和 TVOC (前20行):\n", air_df_clean[['CO2', 'TVOC']].dropna().head(20))