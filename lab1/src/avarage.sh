# Проверка наличия аргументов
if [ $# -eq 0 ]; then
	echo "Ошибка: Не были предоставлены аргументы."
	exit 1
fi

# Инициализация переменных
sum=0
count=0

# Суммирование аргументов
for arg in "$@"
do 
	sum=$((sum + arg))
	count=$((count + 1))
done

# Вычисление среднего арифметического
average=$(echo "scale=2; $sum / $count" | bc)

# Вывод результатов 
echo "Количество аргументов: $count" 
echo "Среднее арифметическое: $average"