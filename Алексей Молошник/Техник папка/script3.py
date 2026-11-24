import pandas as pd
df = pd.read_excel('База данных игр.xlsx')
df.columns = df.columns.str.strip()
cols = list(df.columns)

# Убираем пробелы внутри чисел и извлекаем цену
df['Цена_число'] = (df['Стоимость'].astype(str).str.replace(' ', '', regex=False).str.extract(r'(\d+)').astype(float)
)

# Создание запроса (выбор необходимых полей для отображения)
selected_cols = cols
query_df = df[selected_cols].copy()
print('---  Создан запрос с выбранными полями ---')
print(query_df, '\n')

# Фильтр 1: отзывы "Очень положительные" или крайне положительные и цена ниже 10 000
filtered_df = df[((df['Отзывы'] == 'Очень положительные') | (df['Отзывы'] == 'Крайне положительные')) & (df['Цена_число'] > 10000)].copy()

# Сортировка по возрастанию цены
filtered_df = filtered_df.sort_values(by='Цена_число', ascending=True)
print('--- Записи после применения фильтров ---')
print(filtered_df[selected_cols], '\n')

# Обработка данных
filtered_df['Цена_со_скидкой'] = filtered_df['Цена_число'] * 0.9
avg_price = filtered_df['Цена_число'].mean()
total_count = len(filtered_df)

print('--- Результаты расчётов ---')
print(f'Количество найденных игр: {total_count}')
print(f'Средняя стоимость: {avg_price:.2f} Тенге\n')

# Проверка на пропущенные значения и их исправление при наличии
errors_count = filtered_df[selected_cols].isna().sum().sum()
print(f'Найдено пустых ячеек (ошибок): {errors_count}')
if errors_count > 0:
    filtered_df[selected_cols] = filtered_df[selected_cols].fillna('Нет данных')
    print('Ошибки исправлены: пустые ячейки заполнены.')

result_cols = selected_cols + ['Цена_со_скидкой']
print('\n--- Итоговая таблица ---')
print(filtered_df[result_cols])
filtered_df[result_cols].to_excel('Результат_обработки.xlsx', index=False)