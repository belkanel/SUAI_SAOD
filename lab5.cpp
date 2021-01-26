#include <iostream>
#include <vector>

int ARRAY_LEN = 10;
int SORT_SWAPS = 0;
int SORT_COMPARES = 0;

void print_value(int val, char* txt) {
    std::cout << txt << val << std::endl;
}

void print_arr(int* arr) {
    for (int c = 0; c < ARRAY_LEN; c++) {
        std::cout << c << ": " << arr[c] << " ";
    }
    std::cout << std::endl;
}

void sort_extract(int arr[]) {
    print_arr(arr);
    // число изменений элементов
    // Перебираем все значения массива
    for (int c = ARRAY_LEN - 1; c > 0; c--) {
        int max_item = 0;
        // ищем максимальный индекс в несортированной части
        for (int k = 1; k <= c; k++) {
            if (arr[max_item] < arr[k]) {
                max_item = k;
            }
            // число сравнений
            SORT_COMPARES++;
        }
        print_arr(arr);
        std::cout << max_item << " c:" << c << std::endl;
        if (max_item != c) {
            // меняем элементы местами
            std::swap(arr[max_item], arr[c]);
            // число перестановок
            SORT_SWAPS++;
        }

    }
}

int find_value_by_position(int* arr, int position) {
    if (0 < position < ARRAY_LEN)
        return arr[position];
    return -1;
}

int find_index_by_value(int* arr, int value) {
    int result = -1;
    for (int c = 0; c < ARRAY_LEN; c++) {
        if (arr[c] == value) {
            result = c;
            break;
        }
    }
    return result;
}

int deduped_numbers(int* arr)
{
    int unique_numbers = 0;
    for (int c = 1; c < ARRAY_LEN; c++)
    {
        //только уникальные значения
        if (arr[c] == arr[c - 1])
        {
            continue;
        }
        unique_numbers++;
    }
    if (unique_numbers > 0)
        return unique_numbers + 1;
    return 0;
    {

    };
}


int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    //    int A[ARRAY_LEN];
    std::vector<int> A;
    A.resize(ARRAY_LEN);

    for (int c = 0; c < ARRAY_LEN; c++) {
        A[c] = rand() % 255;
    }

    print_arr(&A[0]);
    sort_extract(&A[0]);
    std::cout << "Sorting swaps::" << SORT_SWAPS << " сравнений: " << SORT_COMPARES << std::endl;
    print_arr(&A[0]);

    int choice = 42;
    char x[100];

    while (choice != 0) {
        std::cout << "МЕНЮ\n";
        std::cout << "1. Создать и заполнить массив\n";
        std::cout << "2. Отсортировать\n";
        std::cout << "3. Добавить случайный элемент в массив\n";
        std::cout << "4. Удалить последний элемент массива\n";
        std::cout << "5. Поиск элемента по индексу\n";
        std::cout << "6. Поиск элемента по значению\n";
        std::cout << "7. Просмотреть массив\n";
        std::cout << "8. Подсчитать количество разных символов в массиве\n";
        std::cout << "0. Выход\n"; std::cout << "\n";

        do {
            std::cout << "Выберите пункт: ", std::cin >> x;
        } while (!isdigit(x[0]));
        choice = atof(x);
        std::cout << "---------------------\n";
        std::cout << "\n";

        switch (choice) {
        case 1: 
        { //обнуление результирующего массива
            SORT_COMPARES = 0;
            SORT_SWAPS = 0;
            for (int c = 0; c < ARRAY_LEN; c++) {
                A[c] = rand() % 255;
                print_arr(&A[0]);
            }
            break;
        }
        case 2: 
        { // сортировка
            sort_extract(&A[0]);
            print_arr(&A[0]);
            std::cout << "Количество сравнений = " << SORT_COMPARES << std::endl;
            std::cout << "Количество перестановок = " << SORT_SWAPS << std::endl; 
            break;
        }
        case 3: 
        { // Добавить элемент в массив
            A.push_back(rand() % 255);
            ARRAY_LEN++;
            print_arr(&A[0]);
            break;
        }
        case 4: 
        { // Удалить элемент
            A.pop_back();
            ARRAY_LEN--;
            print_arr(&A[0]);
            break;
        }
        case 5: 
        { // Поиск элемента по индексу
            int ind = 0;
            std::cout << "Введите индекс искомого элемента." << std::endl;
            std::cin >> ind;
            std::cout << find_value_by_position(&A[0], ind) << std::endl;
            break;
        }
        case 6: 
        {// Поиск элемента по значению
            int val = 0;
            std::cout << "Введите значение искомого элемента." << std::endl;
            std::cin >> val;
            std::cout << find_index_by_value(&A[0], A[4]) << std::endl;
            break;
        }
        case 7: 
        {
            print_arr(&A[0]);
            break;
        }
        case 8:
        {
            std::cout << "Разных элементов в массиве " << deduped_numbers(&A[0]) << std::endl;
        }
        }
    }

    return 0;
}