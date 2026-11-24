import pandas as pd

df = pd.read_excel('Таблица Техник.xlsx')

print("--- Исходная таблица ---")
print(df)

df['Цена_число'] = pd.to_numeric(df['Цена'].str.replace(r'\D', '', regex=True), errors='coerce')
df['Кол_во_число'] = pd.to_numeric(df['Количество'].str.replace(r'\D', '', regex=True), errors='coerce')

print("\n--- Шаг 1. Поиск: товары в наличии ---")
found_items = df[df['Статус'] == 'в наличии']
print(found_items[['Индекс', 'Категория', 'Цена', 'Статус']])

print("\n--- Шаг 2. Сортировка по цене (по возрастанию) ---")
sorted_asc = found_items.sort_values(by='Цена_число', ascending=True)
print(sorted_asc[['Индекс', 'Цена']])

print("\n--- Шаг 2. Сортировка по цене (по убыванию) ---")
sorted_desc = found_items.sort_values(by='Цена_число', ascending=False)
print(sorted_desc[['Индекс', 'Цена']])

print("\n--- Шаг 3. Фильтрация (цена > 1000) ---")
filtered = found_items[found_items['Цена_число'] > 1000].copy()
filtered['Общая_стоимость'] = filtered['Цена_число'] * filtered['Кол_во_число']
print(filtered[['Индекс', 'Цена_число', 'Кол_во_число', 'Общая_стоимость']])

print("\n--- Шаг 4. Проверка данных на пропуски ---")
print(df.isnull().sum())
filtered[['Индекс', 'Цена_число', 'Кол_во_число', 'Общая_стоимость']].to_excel('Результат_обработки.xlsx', index=False)
print("\nГотово! Результат сохранен в файл 'Результат_обработки.xlsx'")






