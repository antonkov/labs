#include <iostream>

using namespace std;

// Функция возвращает значение является ли число n простым
bool prime(int n) {
    if (n == 1) {
        return false;
    }
    // Достаточно проверить делители не более sqrt(n), так как наименьший делитель (!= 1) для любого составного числа не превосходит sqrt(n)
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// Структура хранит начало и конец интервала включительно с обеих сторон
struct range_t {
    int start;
    int finish;
};

void fibonacci_print() {
    string intro("Введите 2 целых числа в интервале [0, 2147483647]");
    cout << intro << endl;
    range_t range;
    while (true) {
        if (cin >> range.start >> range.finish) { // Проверяем, что указаны числа
            if (range.start != range.finish) {
                break;
            } else {
                cout << "Числа не должны быть равны" << endl;
            }
        } else {
            cout << intro << endl;
            // http://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer
            cin.clear();
            //Игнорирует символы после неподходящего символа
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    if (range.start > range.finish) {
        swap(range.start, range.finish);
    }
    // Строим ряд Фибоначчи
    // Максимальное число Фибоначчи влезающие в тип int имеет номер 45 1836311903, поэтому достаточно посчитать 46 чисел Фибоначчи
    const int SIZE = 46;
    int fib[SIZE];
    fib[0] = fib[1] = 1;
    for (int i = 2; i < SIZE; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    cout << "Числа, удовлетворяющие условиям: ";
    // Перебираем числа Фибоначчи, так как их существенно меньше, чем простых чисел
    for (int j = 0; j < SIZE; j++) {
        // Проверям входит ли число Фибоначчи в заданный интервал
        if (fib[j] >= range.start && fib[j] <= range.finish) {
            //Проверяем является ли число Фибоначчи простым
            if (prime(fib[j]))
                cout << fib[j] << " ";
        }
    }
    cout << endl;
}

int main() {
    cout << "Постановка задачи: в заданном интервале указать все числа удовлетворяющие двум условиям" << endl;
    cout << "1. Простые числа" << endl << "2. Числа ряда Фибоначчи" << endl << "Программу разработала студент 465 группы Филимонова Марина" << endl;

    while (true) {
        fibonacci_print();

        cout << "Желаете ввести интервал еще раз? (y/n)" << endl;
        char answer;
        cin >> answer;
        if (answer == 'n') {
            break;
        }
    }
}