import pandas as pd

df = pd.read_excel('таблица с машинами.xlsx')
print("Столбцы:", df.columns.tolist())

text_cols = df.select_dtypes(include=['object', 'string']).columns
num_cols = df.select_dtypes(include='number').columns

if len(text_cols) > 0 and len(num_cols) > 0:
    col_text, col_num = text_cols[0], num_cols[0]

    target = df[col_text].dropna().iloc[0]
    step1_2 = df[df[col_text] == target].sort_values(by=col_num, ascending=False)
    print(f"\n--- Поиск '{target}' ---\n", step1_2)

    step3 = df[df[col_num] >= 2000].sort_values(by=col_num, ascending=False)
    print("\n--- с 2000 года ---\n", step3.head())

    avg_val = df[col_num].mean()
    min_val = df[col_num].min()
    my_filter = df[(df[col_num] >= min_val) & (df[col_num] < avg_val)].dropna()
    print(f"\n--- Простой фильтр: от {min_val} до {avg_val:.1f} ---\n", my_filter.head())

    my_filter.to_excel('результат_обработки.xlsx', index=False)
    print("\nГотово! Файл 'результат_обработки.xlsx' сохранен.")
