import java.util.Arrays;

public class SortingAndSearching {

    // ======== СОРТИРОВКИ ========

    // 1️⃣ Сортировка выбором (Selection Sort)
    public static void selectionSort(int[] arr) {
        int n = arr.length;
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            // Находим индекс минимального элемента в неотсортированной части
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            // Меняем местами текущий элемент и минимальный
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }

    // 2️⃣ Сортировка пузырьком (Bubble Sort)
    public static void bubbleSort(int[] arr) {
        int n = arr.length;
        boolean swapped;
        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    // Обмен соседних элементов, если нарушен порядок
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapped = true;
                }
            }
            // Если за проход не было обменов, массив уже отсортирован
            if (!swapped) break;
        }
    }

    // 3️⃣ Сортировка слиянием (Merge Sort)
    public static void mergeSort(int[] arr, int left, int right) {
        if (left < right) {
            int mid = (left + right) / 2;

            // Рекурсивно сортируем левую и правую половины
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);

            // Объединяем две отсортированные части
            merge(arr, left, mid, right);
        }
    }

    private static void merge(int[] arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int[] L = new int[n1];
        int[] R = new int[n2];

        // Копируем данные во временные массивы
        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        // Слияние обратно в основной массив
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }

        // Копируем оставшиеся элементы
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    // 4️⃣ Сортировка Шелла (Shell Sort)
    public static void shellSort(int[] arr) {
        int n = arr.length;
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j = i;
                // Сдвигаем элементы, чтобы вставить temp в правильное место
                while (j >= gap && arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
            }
        }
    }

    // 5️⃣ Пирамидальная (Heap) сортировка
    public static void heapSort(int[] arr) {
        int n = arr.length;

        // Строим max-heap
        for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

        // Извлекаем элементы один за другим
        for (int i = n - 1; i >= 0; i--) {
            // Перемещаем текущий корень в конец
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // Восстанавливаем кучу для уменьшенного массива
            heapify(arr, i, 0);
        }
    }

    private static void heapify(int[] arr, int n, int i) {
        int largest = i;       // Корень
        int left = 2 * i + 1;  // Левый потомок
        int right = 2 * i + 2; // Правый потомок

        // Проверяем, больше ли левый потомок корня
        if (left < n && arr[left] > arr[largest]) largest = left;

        // Проверяем правого потомка
        if (right < n && arr[right] > arr[largest]) largest = right;

        // Если корень не самый большой, меняем местами и рекурсивно heapify
        if (largest != i) {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;
            heapify(arr, n, largest);
        }
    }

    // ======== ПОИСК ========

    // 1️⃣ Последовательный (линейный) поиск
    public static int linearSearch(int[] arr, int x) {
        for (int i = 0; i < arr.length; i++)
            if (arr[i] == x) return i;
        return -1;
    }

    // 2️⃣ Интерполяционный поиск (для отсортированного массива)
    public static int interpolationSearch(int[] arr, int x) {
        int low = 0, high = arr.length - 1;

        while (low <= high && x >= arr[low] && x <= arr[high]) {
            if (low == high) return (arr[low] == x) ? low : -1;

            int pos = low + ((x - arr[low]) * (high - low)) / (arr[high] - arr[low]);

            if (arr[pos] == x) return pos;
            if (arr[pos] < x) low = pos + 1;
            else high = pos - 1;
        }
        return -1;
    }

    // 3️⃣ Поиск Фибоначчи (для отсортированного массива)
    public static int fibonacciSearch(int[] arr, int x) {
        int n = arr.length;
        int fibMMm2 = 0; // (m-2)'е число Фибоначчи
        int fibMMm1 = 1; // (m-1)'е
        int fibM = fibMMm2 + fibMMm1; // m-е

        while (fibM < n) {
            fibMMm2 = fibMMm1;
            fibMMm1 = fibM;
            fibM = fibMMm2 + fibMMm1;
        }

        int offset = -1;
        while (fibM > 1) {
            int i = Math.min(offset + fibMMm2, n - 1);

            if (arr[i] < x) {
                fibM = fibMMm1;
                fibMMm1 = fibMMm2;
                fibMMm2 = fibM - fibMMm1;
                offset = i;
            } else if (arr[i] > x) {
                fibM = fibMMm2;
                fibMMm1 = fibMMm1 - fibMMm2;
                fibMMm2 = fibM - fibMMm1;
            } else return i;
        }

        if (fibMMm1 == 1 && offset + 1 < n && arr[offset + 1] == x)
            return offset + 1;

        return -1;
    }

    // ======== ТЕСТ ========
    public static void main(String[] args) {
        int[] arr = {64, 25, 12, 22, 11};
        System.out.println("Исходный массив: " + Arrays.toString(arr));

        int[] temp;

        // Примеры сортировок
        temp = arr.clone();
        selectionSort(temp);
        System.out.println("Сортировка выбором: " + Arrays.toString(temp));

        temp = arr.clone();
        bubbleSort(temp);
        System.out.println("Пузырьковая сортировка: " + Arrays.toString(temp));

        temp = arr.clone();
        mergeSort(temp, 0, temp.length - 1);
        System.out.println("Слиянием: " + Arrays.toString(temp));

        temp = arr.clone();
        shellSort(temp);
        System.out.println("Шелла: " + Arrays.toString(temp));

        temp = arr.clone();
        heapSort(temp);
        System.out.println("Пирамидальная: " + Arrays.toString(temp));

        // Поиск
        int[] sorted = {11, 12, 22, 25, 64};
        System.out.println("\nПоиск элемента 22:");
        System.out.println("Линейный: индекс = " + linearSearch(sorted, 22));
        System.out.println("Интерполяционный: индекс = " + interpolationSearch(sorted, 22));
        System.out.println("Фибоначчи: индекс = " + fibonacciSearch(sorted, 22));
    }
}
