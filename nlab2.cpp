#include <iostream>
#include <fstream>

using namespace std;

struct {
    bool valid;
    int l, r, size;
    int *v;
} input_data; // Создаем структуру для хранения исходных данных

struct {
    bool valid;
    bool exist_number;
    int number;
} output_data; // Структура с входными данными

void free(int *v) { // Освобождаем выделенную память
    if (v) {
        delete v;
        v = NULL;
    }
}

void clear_cin() {
    // http://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer
    cin.clear();
    // Игнорирует символы после неподходящего символа
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void process(istream &input) {
    input_data.valid = false;
    bool fail = false;
    if (input >> input_data.l >> input_data.r >> input_data.size && input_data.size > 0) {
        free(input_data.v);
        input_data.v = new int[input_data.size]; // Выделяем память для массива

        for (int i = 0; i < input_data.size; i++)
            input >> input_data.v[i]; // Заполняем массив
        if (input.fail()) {
            fail = true;
        }
    } else {
        cout << "Неверный формат данных" << endl;
        fail = true;
    }

    if (fail) {
        cout << "В первой строке должны быть указаны целые числа" << endl;
    } else {
        input_data.valid = true; // Запоминает введены ли данные
        bool found = false;
        for (int num = input_data.l; num <= input_data.r; num++) { // Поверяем есть ли числа из интервала в массиве
            bool inArray = false;
            for (int i = 0; i < input_data.size; i++) {
                if (input_data.v[i] == num)
                    inArray = true;
            }
            if (!inArray) {
                output_data.exist_number = true;
                output_data.number = num;
                cout << "Число из интервала не содержащееся в массиве: " << num << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            output_data.exist_number = false;
            cout << "Все числа из интервала содержатся в массиве" << endl;
        }
        output_data.valid = true;
    }
}

int main() {
    while (true) {
        cout << "Формат исходных данных:" << endl;
        cout << "\"Начало интервала\" \"Конец интервала\" \"Длина массива\"" << endl;
        cout << "Элементы массива через пробел" << endl;
        cout << endl;
        cout << "Введите имя входного файла" << endl;
        cout << "Enter если ввод с клавиатуры:" << endl;
        string input_filename;
        getline(cin, input_filename);
        if (input_filename.empty()) {
            cout << "Введите данные" << endl;
            process(cin); // Считываем с клавиатуры если введен Enter
            clear_cin();
            while (true && input_data.valid) {
                cout << "Сохранить исходные данные в файл?" << endl;
                cout << "Имя файла или Enter для продолжения:" << endl;
                string save_input;
                getline(cin, save_input);
                if (!save_input.empty()) {
                    ofstream save_input_stream(save_input);
                    if (save_input_stream.fail()) {
                        cout << "Не удалось создать файл" << endl;
                        continue;
                    } else {
                        save_input_stream << input_data.l << " " << input_data.r << " " << input_data.size << endl;
                        for (int i = 0; i < input_data.size; i++) { // Сохраняем исходные данные в файл
                            save_input_stream << input_data.v[i] << " ";
                        }
                        save_input_stream << endl;
                        break;
                    }
                }
                break;
            }
        } else {
            ifstream in(input_filename);
            if (in.fail()) {
                cout << "Файл не найден" << endl;
            } else {
                process(in); // Считываем данные с файла
            }
        }
        while (true && output_data.valid) {
            cout << "Сохранить результат в файл?" << endl;
            cout << "Имя файла или Enter для продолжения:" << endl;
            string save_output;
            getline(cin, save_output);
            if (!save_output.empty()) {
                ofstream save_output_stream(save_output);
                if (save_output_stream.fail()) {
                    cout << "Не удалось создать файл" << endl;
                    continue;
                } else {
                    if (output_data.exist_number) {
                        save_output_stream << "Число из интервала не содержащееся в массиве: " << output_data.number
                                           << endl;
                    } else {
                        save_output_stream << "Все числа из интервала содержатся в массиве" << endl;
                    }
                    break;
                }
            }
            break;
        }
        output_data.valid = false;

        bool exit = false;
        while (true) {
            cout << "Желаете повторить?[y/n]" << endl;
            string answer;
            getline(cin, answer);
            if (answer == "y") {
                exit = false;
                break;
            } else if (answer == "n") {
                exit = true;
                break;
            }
        }
        if (exit) {
            break;
        }
    }
    free(input_data.v);
}

