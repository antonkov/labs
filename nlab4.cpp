#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

typedef vector<double> row_t; // Тип для короткой записи типа строки матрицы
typedef vector<row_t> matrix_t; // Тип для короткой записи типа матрицы

// Вывод матрицы
void print(matrix_t const &mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Транспонирование матрицы
matrix_t transpose(matrix_t const &mat) {
    int n = mat.size();
    int m = mat[0].size();
    matrix_t res(m, row_t(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = mat[j][i];
        }
    }
    return res;
}

// Умножение матрицы на вектор
row_t multiply(matrix_t const &mat, row_t const &vec) {
    int n = mat.size();
    int m = mat[0].size();
    row_t res(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res[i] += mat[i][j] * vec[j];
        }
    }
    return res;
}

// Перемножение матриц
matrix_t multiply(matrix_t const &mat1, matrix_t const &mat2) {
    int n = mat1.size();
    int k = mat2.size();
    assert(mat1[0].size() == k);
    int m = mat2[0].size();
    matrix_t res(n, row_t(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int it = 0; it < k; it++) {
                res[i][j] += mat1[i][it] * mat2[it][j];
            }
        }
    }
    return res;
}

// Нахождение обратноя для матрицы 2 на 2
matrix_t inverse2(matrix_t const & mat) {
    int n = mat.size();
    assert(mat[0].size() == n);
    assert(n == 2);

    double a = mat[0][0];
    double b = mat[0][1];
    double c = mat[1][0];
    double d = mat[1][1];

    double det = a * d - b * c;
    assert(abs(det) > 1e-6);
    matrix_t res(2, row_t(2));
    res[0][0] = d / det;
    res[0][1] = -b / det;
    res[1][0] = -c / det;
    res[1][1] = a / det;

    {
        // Проверка
        matrix_t identity = multiply(mat, res);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                assert((i == j && abs(identity[i][j] - 1) < 1e-6) || (i != j && abs(identity[i][j]) < 1e-6));
            }
        }
    }
    return res;
}

// Тип для представления точки
struct point_t {
    double x, y;

    point_t(double x, double y) :
            x(x), y(y) {}

    point_t() {}
};

// Тип для представления уравнения прямой в виде y = kx + b
struct line_t {
    double k, b;

    line_t(double k, double b) :
            k(k), b(b) {}
};

// Построение прямой для набора точек по формуле линейной регрессии (метод наименьших квадратов)
line_t linear_regression(vector<point_t> const &pts) {
    matrix_t A(pts.size(), row_t(2));
    row_t ys(pts.size());
    for (int i = 0; i < pts.size(); i++) {
        A[i][0] = 1;
        A[i][1] = pts[i].x;
        ys[i] = pts[i].y;
    }
    matrix_t At = transpose(A);
    matrix_t AtA = multiply(At, A);
    matrix_t A1 = inverse2(AtA);
    matrix_t A2 = multiply(A1, At);
    row_t w = multiply(A2, ys);
    return line_t(w[1], w[0]);
}

// Чтение набора точек, false - если не смогли считать, true - если удачно считали
bool read(vector<point_t> &pts) {
    int n;
    if (!(cin >> n)) {
        return false;
    }
    if (n <= 1) {
        return false;
    }
    pts = vector<point_t>(n);
    for (int i = 0; i < n; i++) {
        double x, y;
        if (!(cin >> x >> y)) {
            return false;
        }
        pts[i] = point_t(x, y);
    }
    return true;
}

int main() {
    while (true) {
        cout << "Формат исходных данных:" << endl;
        cout << "Количество точек N (N >= 2)" << endl;
        cout << "2N чисел задающие точки по порядку, координаты точки в порядке x, y" << endl;

        bool fail = false;
        vector<point_t> pts;
        if (!read(pts)) {
            cout << "Неверный формат ввода. Попробуйте еще раз." << endl;
            continue;
        }

        line_t res = linear_regression(pts);
        cout << "Результирующая прямая:" << endl;
        cout << "y = " << res.k << " x + " << res.b << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
}
