import pandas as pd

df = pd.read_excel('Таблица Техник.xlsx')

print("--- Исходная таблица ---")
print(df)

df['Цена_число'] = pd.to_numeric(df['Цена'].str.replace(r'\D', '', regex=True), errors='coerce')
df['Кол_во_число'] = pd.to_numeric(df['Количество'].str.replace(r'\D', '', regex=True), errors='coerce')

print("\n--- Шаг 1. Поиск: товары в наличии ---")
found_items = df[df['Статус'] == 'в наличии']
print(found_items[['Индекс', 'Категория', 'Цена', 'Статус']])

print("\n--- Шаг 2. Обработка данных ---")
found_items = found_items.sort_values(by='Цена_число', ascending=False)
print(sorted_desc[['Индекс', 'Цена']])

print("\n--- Шаг 3. Систематизация данных (по убыванию цены) ---")
sorted_data = found_items.sort_values(by='Цена_число', ascending=False)
print(sorted_data[['Индекс', 'Цена_число', 'Кол_во_число', 'Общая_стоимость']])

print("\n--- Шаг 4. Проверка результата ---")
print("Количество пропущенных значений в итоге:")
print(sorted_data.isnull().sum())

output_columns = ['Индекс', 'Цена_число', 'Кол_во_число', 'Общая_стоимость']
sorted_data[output_columns].to_excel("Результат_обработки.xlsx", index=False)
print("\nГотово! Результат сохранен в файл 'Результат_обработки.xlsx'")



