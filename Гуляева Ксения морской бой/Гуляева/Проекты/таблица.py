import pandas as pd

df = pd.read_csv('таблица с машинами.csv', sep=';', encoding='utf-8-sig')
print("Столбцы:", df.columns.tolist())

text_cols = df.select_dtypes(include=['object', 'string']).columns
num_cols = df.select_dtypes(include='number').columns

if len(text_cols) > 0 and len(num_cols) > 0:
    col_text, col_num = text_cols[0], num_cols[0]

    df[col_text] = df[col_text].astype(str).str.strip()
    df = df.drop_duplicates().dropna(subset=[col_num])

    target = df[col_text].iloc[0]
    step1_2 = df[df[col_text] == target].sort_values(by=col_num, ascending=False)
    print(f"\n--- Записи '{target}' ---\n", step1_2)

    step3 = df[df[col_num] >= 2000].sort_values(by=col_num, ascending=False)
    print("\n--- С 2000 года и новее ---\n", step3.head())

    avg_val = df[col_num].mean()
    min_val = df[col_num].min()
    my_filter = df[(df[col_num] >= min_val) & (df[col_num] < avg_val)]
    print(f"\n--- От {min_val} до {avg_val:.1f} ---\n", my_filter.head())

    my_filter.to_csv('результат_обработки.csv', index=False, encoding='utf-8-sig', sep=';')
    check = pd.read_csv('результат_обработки.csv', sep=';', encoding='utf-8-sig')
    print(f"\nСохранено строк: {len(check)} из {len(my_filter)}. Файл корректен.")
else:
    print("Не нашлись одновременно текстовые и числовые столбцы — проверьте шапку таблицы.")
