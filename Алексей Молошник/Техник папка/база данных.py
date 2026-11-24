import pandas as pd
df = pd.read_csv('База данных игр.xlsx')
print("---Загруженная база данных---")
print(df.head())
print("\n---Информация о таблице---")
print(df.info())