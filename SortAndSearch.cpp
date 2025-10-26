// algorithms.cpp
// Полный демонстрационный файл: сортировки и поиски на C++.
// Скомпилировать: g++ -std=c++17 algorithms.cpp -O2 -o algos

#include <iostream>     // для std::cout, std::endl
#include <vector>       // для std::vector
#include <algorithm>    // для std::swap, std::copy
#include <cmath>        // для std::floor
#include <limits>       // для std::numeric_limits

// Используем пространство имён std локально в файле, чтобы код был компактнее.
// В больших проектах лучше избегать using namespace std; но в демонстрационных файлах оно уместно.
using namespace std;

   ---------------------------
   ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
   --------------------------- 

// Функция для вывода массива/вектора в консоль (для демонстрации).
void print_vector(const vector<int>& a, const string& name = "") {
    if (!name.empty()) cout << name << ": ";
    cout << "[";
    for (size_t i = 0; i < a.size(); ++i) {
        cout << a[i];
        if (i + 1 < a.size()) cout << ", ";
    }
    cout << "]" << endl;
}




   ===========================
   СОРТИРОВКИ
   =========================== 


1) Сортировка выбором (Selection Sort)
   Идея: проходим по массиву, на i-ой итерации выбираем минимальный
   элемент среди оставшихся (i..n-1) и ставим его на позицию i.

  
void selection_sort(vector<int>& a) {
    size_t n = a.size();                          // размер массива
    for (size_t i = 0; i < n; ++i) {              // for: фиксируем позицию i, куда ставим минимальный
        size_t min_idx = i;                       // считаем, что текущий i — минимальный
        for (size_t j = i + 1; j < n; ++j) {      // ищем минимальный элемент в оставшейся части
            if (a[j] < a[min_idx]) {              // если нашли меньше — обновляем индекс минимума
                min_idx = j;
            }
        }
        if (min_idx != i) {                       // если минимум не на месте — меняем местами
            swap(a[i], a[min_idx]);
        }
    }
}


2) Пузырьковая сортировка (Bubble Sort)
   Идея: многократно проходим по массиву и "всплываем" большие элементы вправо,
   делая попарные сравнения и обмены. Имеет оптимизацию — если за проход не было обменов,
   массив уже отсортирован.

  
void bubble_sort(vector<int>& a) {
    size_t n = a.size();                          // длина массива
    bool swapped;                                 // флаг — был ли обмен в проходе
    for (size_t pass = 0; pass < n; ++pass) {     // максимум n проходов
        swapped = false;                          // предположим, обменов нет
        for (size_t j = 1; j < n - pass; ++j) {   // проходим по неотсортированной части
            if (a[j - 1] > a[j]) {                // если порядок нарушен — меняем
                swap(a[j - 1], a[j]);
                swapped = true;                   // отмечаем, что был обмен
            }
        }
        if (!swapped) break;                      // если за прохода не было обменов — выходим
    }
}


3) Сортировка слиянием (Merge Sort)
   Идея: рекурсивно делим массив пополам, сортируем половины и затем сливаем их.
   Отличается стабильностью (сохраняет порядок эквивалентных элементов).

  
void merge(vector<int>& a, vector<int>& tmp, size_t left, size_t mid, size_t right) {
    // left .. mid-1 и mid .. right-1 — две отсортированные части.
    size_t i = left;      // указатель на текущий элемент в левой части
    size_t j = mid;       // указатель на текущий элемент в правой части
    size_t k = left;      // указатель в временном массиве

    // Пока обе части не пусты, выбираем меньший элемент
    while (i < mid && j < right) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];   // копируем из левой части
        } else {
            tmp[k++] = a[j++];   // копируем из правой части
        }
    }
    // Копируем оставшиеся элементы (если какие-то остались)
    while (i < mid) tmp[k++] = a[i++];
    while (j < right) tmp[k++] = a[j++];

    // Копируем обратно в основной массив
    for (size_t idx = left; idx < right; ++idx) {
        a[idx] = tmp[idx];
    }
}

void merge_sort_rec(vector<int>& a, vector<int>& tmp, size_t left, size_t right) {
    // Сортируем а[left..right-1]
    if (right - left <= 1) return;                // база рекурсии: 0 или 1 элемент — уже отсортирован
    size_t mid = left + (right - left) / 2;       // делим пополам
    merge_sort_rec(a, tmp, left, mid);            // сортируем левую половину
    merge_sort_rec(a, tmp, mid, right);           // сортируем правую половину
    merge(a, tmp, left, mid, right);              // сливаем две отсортированные половины
}

void merge_sort(vector<int>& a) {
    vector<int> tmp(a.size());                    // вспомогательный массив того же размера
    merge_sort_rec(a, tmp, 0, a.size());         // запускаем рекурсивную сортировку
}


4) Сортировка Шелла (Shell Sort)
   Идея: улучшение сортировки вставками — сначала сравниваем элементы, удалённые на некоторый gap,
   затем уменьшаем gap. Часто используется последовательность деления gap = gap/2.

     
void shell_sort(vector<int>& a) {
    size_t n = a.size();                          // размер массива
    // Начальное значение шага (gap)
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        // для каждого "подмассива" делаем сортировку вставками
        for (size_t i = gap; i < n; ++i) {
            int temp = a[i];                      // сохраняем текущий элемент
            size_t j = i;
            // сдвигаем элементы, пока не найдём место для temp
            while (j >= gap && a[j - gap] > temp) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;                          // вставляем элемент
        }
    }
}


5) Пирамидальная сортировка (Heap Sort)
   Идея: строим max-кучу, затем подряд извлекаем максимум (корень) в конец массива,
   уменьшая "активный" размер кучи.


// Функция для корректировки поддерева (heapify) — для max-кучи.
void heapify(vector<int>& a, size_t n, size_t i) {
    size_t largest = i;         // считаем, что i — самый большой
    size_t l = 2 * i + 1;       // индекс левого ребёнка
    size_t r = 2 * i + 2;       // индекс правого ребёнка

    // Если левый ребёнок больше родителя — обновляем largest
    if (l < n && a[l] > a[largest])
        largest = l;

    // Если правый ребёнок больше текущего largest — обновляем largest
    if (r < n && a[r] > a[largest])
        largest = r;

    // Если largest не равен i — нужно поменять и рекурсивно heapify
    if (largest != i) {
        swap(a[i], a[largest]);     // меняем местами
        heapify(a, n, largest);     // продолжаем heapify вниз по дереву
    }
}

void heap_sort(vector<int>& a) {
    size_t n = a.size();

    // Строим max-кучу — преобразуем массив в кучу
    // Начинаем с последнего не-листа: последний родитель = (n/2)-1
    for (size_t i = n / 2; i-- > 0;) {   // убывающий цикл: i = n/2-1 ... 0
        heapify(a, n, i);                // корректируем поддерево
        if (i == 0) break;               // защита от переполнения size_t при i--
    }

    // Извлекаем элементы из кучи по одному
    for (size_t i = n; i-- > 1;) {       // i = n-1 ... 1
        swap(a[0], a[i]);                // переносим текущий максимум в конец
        heapify(a, i, 0);                // восстанавливаем кучу для уменьшенного массива
        if (i == 1) break;               // защита от переполнения при i--
    }
}

   ===========================
   ПОИСКИ
   ===========================


Последовательный поиск (Linear Search)
   Идея: проходим по массиву по порядку и сравниваем каждый элемент с ключом.
   Возвращаем индекс первого найденного или -1, если не найден.

  
int linear_search(const vector<int>& a, int key) {
    for (size_t i = 0; i < a.size(); ++i) {    // пробегаем весь вектор
        if (a[i] == key) return static_cast<int>(i); // нашли — возвращаем индекс
    }
    return -1;                                 // не найден
}


 Интерполяционный поиск (Interpolation Search)
   Работает на отсортированных массивах с примерно равномерным распределением значений.
   Пытается "угадать" позицию ключа, используя линейную интерполяцию.

  
int interpolation_search(const vector<int>& a, int key) {
    size_t lo = 0;                              // левая граница (индекс)
    size_t hi = (a.empty() ? 0 : a.size() - 1); // правая граница (индекс)

    if (a.empty()) return -1;                   // пустой массив — ничего не найдено

    // пока ключ в диапазоне значений a[lo] .. a[hi]
    while (lo <= hi && key >= a[lo] && key <= a[hi]) {
        // если все элементы в отрезке равны — проверяем один из них
        if (a[lo] == a[hi]) {
            if (a[lo] == key) return static_cast<int>(lo);
            else break;
        }

        // вычисляем позицию методом линейной интерполяции:
        // pos = lo + ( (key - a[lo]) * (hi - lo) / (a[hi] - a[lo]) )
        double denom = static_cast<double>(a[hi] - a[lo]);
        double num = static_cast<double>(key - a[lo]);
        size_t pos = lo + static_cast<size_t>( (num * (hi - lo)) / denom );

        // защита от выхода за границы (на всякий случай)
        if (pos < lo || pos > hi) break;

        if (a[pos] == key) return static_cast<int>(pos); // нашли
        if (a[pos] < key) lo = pos + 1;                  // ищем в правой части
        else if (pos == 0) break;                        // защита от underflow
        else hi = pos - 1;                               // ищем в левой части
    }

    return -1; // не найден
}


/ Поиск Фибоначчи (Fibonacci Search)
   Работает для отсортированных массивов. Использует разбиение с помощью чисел Фибоначчи./

  
int fibonacci_search(const vector<int>& a, int key) {
    size_t n = a.size();
    if (n == 0) return -1;

    // Ищем наименьшее число Фибоначчи >= n
    size_t fibMm2 = 0;  // (m-2)-е число Фибоначчи (F_{m-2})
    size_t fibMm1 = 1;  // (m-1)-е число Фибоначчи (F_{m-1})
    size_t fibM = fibMm2 + fibMm1; // m-е число Фибоначчи (F_m)

    while (fibM < n) {                 // расширяем последовательность пока fibM < n
        fibMm2 = fibMm1;
        fibMm1 = fibM;
        fibM = fibMm2 + fibMm1;
    }

    //
