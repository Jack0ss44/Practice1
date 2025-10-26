 ============================================================
 Алгоритмы сортировки и поиска с пояснениями
 ============================================================

# ---------- 1. Сортировка выбором ----------
def selection_sort(arr):
    # Проходим по всем элементам массива
    for i in range(len(arr)):
        min_index = i  # считаем текущий элемент минимальным
        for j in range(i + 1, len(arr)):  # ищем минимальный в оставшейся части
            if arr[j] < arr[min_index]:
                min_index = j  # обновляем индекс минимального
        # меняем местами текущий элемент и найденный минимальный
        arr[i], arr[min_index] = arr[min_index], arr[i]
    return arr


# ---------- 2. Сортировка пузырьком ----------
def bubble_sort(arr):
    n = len(arr)
    for i in range(n - 1):
        for j in range(n - 1 - i):
            # если текущий элемент больше следующего — меняем их местами
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr


# ---------- 3. Сортировка слиянием ----------
def merge_sort(arr):
    # Базовый случай: массив из одного элемента уже отсортирован
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2  # делим массив пополам
    left = merge_sort(arr[:mid])   # рекурсивно сортируем левую половину
    right = merge_sort(arr[mid:])  # рекурсивно сортируем правую

    # Слияние отсортированных частей
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    # добавляем оставшиеся элементы
    result.extend(left[i:])
    result.extend(right[j:])
    return result


# ---------- 4. Сортировка Шелла ----------
def shell_sort(arr):
    n = len(arr)
    gap = n // 2  # начальный шаг (расстояние между сравниваемыми элементами)
    while gap > 0:
        for i in range(gap, n):
            temp = arr[i]
            j = i
            # выполняем сортировку вставками с данным шагом
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap]
                j -= gap
            arr[j] = temp
        gap //= 2  # уменьшаем шаг вдвое
    return arr


# ---------- 5. Пирамидальная (кучевая) сортировка ----------
def heapify(arr, n, i):
    largest = i          # считаем текущий узел наибольшим
    left = 2 * i + 1     # левый потомок
    right = 2 * i + 2    # правый потомок

    # проверяем, не больше ли левый потомок текущего узла
    if left < n and arr[left] > arr[largest]:
        largest = left

    # проверяем правого потомка
    if right < n and arr[right] > arr[largest]:
        largest = right

    # если найден элемент больше текущего — меняем местами
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)  # рекурсивно восстанавливаем свойство кучи


def heap_sort(arr):
    n = len(arr)

    # строим максимальную кучу (heap)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # извлекаем элементы один за другим
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]  # перемещаем текущий корень в конец
        heapify(arr, i, 0)  # восстанавливаем кучу на оставшейся части
    return arr


 ============================================================
 Алгоритмы поиска
 ============================================================

# ---------- 6. Последовательный (линейный) поиск ----------
def linear_search(arr, target):
    for i in range(len(arr)):
        if arr[i] == target:
            return i  # возвращаем индекс найденного элемента
    return -1  # если не найден


# ---------- 7. Интерполяционный поиск ----------
def interpolation_search(arr, target):
    low = 0
    high = len(arr) - 1

    while low <= high and arr[low] <= target <= arr[high]:
        # оцениваем позицию искомого элемента (формула интерполяции)
        pos = low + ((target - arr[low]) * (high - low)) // (arr[high] - arr[low])

        if arr[pos] == target:
            return pos
        elif arr[pos] < target:
            low = pos + 1
        else:
            high = pos - 1
    return -1


# ---------- 8. Поиск Фибоначчи ----------
def fibonacci_search(arr, target):
    n = len(arr)
    # инициализация чисел Фибоначчи
    fibMMm2 = 0  # (m-2)'е число
    fibMMm1 = 1  # (m-1)'е число
    fibM = fibMMm2 + fibMMm1  # m-е число

    # находим наименьшее число Фибоначчи >= n
    while fibM < n:
        fibMMm2 = fibMMm1
        fibMMm1 = fibM
        fibM = fibMMm2 + fibMMm1

    offset = -1  # исключённая область с начала

    while fibM > 1:
        i = min(offset + fibMMm2, n - 1)

        if arr[i] < target:
            fibM = fibMMm1
            fibMMm1 = fibMMm2
            fibMMm2 = fibM - fibMMm1
            offset = i
        elif arr[i] > target:
            fibM = fibMMm2
            fibMMm1 = fibMMm1 - fibMMm2
            fibMMm2 = fibM - fibMMm1
        else:
            return i
    if fibMMm1 and offset + 1 < n and arr[offset + 1] == target:
        return offset + 1
    return -1


