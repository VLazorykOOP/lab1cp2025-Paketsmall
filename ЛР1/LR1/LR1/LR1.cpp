#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <map>
#include <stdexcept>
#include <windows.h>
#include <algorithm>
using namespace std;

// ----------------- Таблична інтерполяція -----------------
// Шукаємо значення функції для довільного x з таблиці в заданому файлі
double interpolate(double x, const string& filename) {
    ifstream file(filename);
    if (!file) throw runtime_error("Failed to open file: " + filename);

    double x0, y0, x1, y1;
    file >> x0 >> y0;

    if (x == x0) return y0;

    while (file >> x1 >> y1) {
        if (x == x1) return y1;
        if (x > x0 && x < x1)
            return y0 + (y1 - y0) * (x - x0) / (x1 - x0); // лінійна інтерполяція
        x0 = x1;
        y0 = y1;
    }

    throw out_of_range("Value " + to_string(x) + " out of range c " + filename);
}

// ----------------- Функція Y(x) -----------------
// Використовується в логарифмах. Перевіряємо допустимість підлогарифмічного виразу
double Y(double x) {
    double val = 100 * x - x * x;
    if (val <= 0) throw domain_error("Y(x): Invalid value under logarithm");
    return log(val);
}

// ----------------- Tsm(x, y) -----------------
// Частина підрахунку m: log10 виразу з Y(x) і Y(y)
double Tsm(double x, double y) {
    if (4 * x * y < 0) return 0;
    try {
        double val = 4 * x * y - Y(x) + Y(y);
        if (val <= 0) return 0;
        return log10(val);
    }
    catch (...) {
        return 0;
    }
}

// ----------------- Mts(x, y) = Tsm(x, y) - Tsm(y, x) -----------------
double Mts(double x, double y) {
    return Tsm(x, y) - Tsm(y, x);
}

// ----------------- Mtl(x, y, z) -----------------
// Обчислення змінної m, з урахуванням винятків
double Mtl(double x, double y, double z, int& m) {
    double mts1 = Mts(x, y);
    double mts2 = Mts(y, z);
    double result = mts1 + mts2;

    // Перевірки, які можуть змінити значення m
    try {
        double yx = Y(x);
        if (100 * x - x * x < 0) m = 0;
        if (100 * x - x * x < 100) m = 1;
        if (4 * x * y - yx + Y(y) < 0 || 4 * y * z - Y(y) + Y(z) < 0) m = 0;
    }
    catch (...) {
        m = 0;
    }

    return result;
}

// ----------------- GetFrom(text, x) -----------------
// Читання значення, що відповідає слову `text` з файлу dat3.dat
double GetFrom(const string& text, double x) {
    ifstream file("dat3.dat");
    if (!file) return 0;

    string key;
    double val;
    while (file >> key >> val) {
        if (key == text) return val;
    }
    return 0;
}

// ----------------- Пошук мінімального -----------------
double MinS(double x, double y, double z, const string& text) {
    return min(x, min(y, z));
}

// ----------------- Qkn(x, y) = (U(x) + T(y)) / x -----------------
double Qkn(double x, double y) {
    try {
        double Ux = interpolate(x, "dat1.dat");
        double Ty = interpolate(y, "dat2.dat");
        if (x == 0) throw domain_error("Division by zero in Qkn");
        return (Ux + Ty) / x;
    }
    catch (...) {
        throw;
    }
}

// ----------------- Qnk(x, y) = Qkn(x, y) + Qkn(y, x) -----------------
double Qnk(double x, double y) {
    return Qkn(x, y) + Qkn(y, x);
}

// ----------------- Rsv – умовна функція з 4-ма гілками -----------------
double Rsv(double x, double y, double z) {
    if (x > y && z > x) return Qnk(z, y) * z;
    else if (z > x && y > z) return Qnk(x, z) * x;
    else if (y > x && z > y) return Qnk(y, x) * y;
    else if (x == z || y == z) return Qnk(z, y) - Qnk(z, y);
    return 0;
}

// ----------------- fun_cr(x, y, z) -----------------
double fun_cr(double x, double y, double z) {
    return Rsv(x, y, z) + 0.5 * Rsv(y, z, x) + Rsv(z, x, y);
}

// ----------------- k = Ktext(x, y, z, text) -----------------
double Ktext(double x, double y, double z, const string& text) {
    if (text == "") {
        if (x + GetFrom(text, x) <= 0) return MinS(x, y, z, text);
    }
    else {
        if (text.length() - GetFrom(text, x) <= 0) return MinS(x, y, z, text);
    }
    return 1;
}

// ----------------- Основна функція з алгоритму -----------------
double func_regr(double r, double m, double k) {
    return r * m * k - 10 * r * r;
}

// ----------------- Головна функція -----------------
int main() {
    SetConsoleOutputCP(65001);
    double x, y, z;
    string text;

    cout << "Enter x, y, z and a text string (no spaces): ";
    cin >> x >> y >> z >> text;

    try {
        int m_flag = -1; // використовується для фіксації змін у m
        double r = fun_cr(x, y, z);               // розрахунок r
        double m = Mtl(x, y, z, m_flag);          // розрахунок m
        double k = Ktext(x, y, z, text);          // розрахунок k
        double result = func_regr(r, m, k);       // обчислення підсумкової функції

        cout << "\nThe results:\n";
        cout << "r = " << r << "\nm = " << m << "\nk = " << k << "\nfunc_regr = " << result << endl;
    }
    catch (const exception& e) {
        cerr << "\nError: " << e.what() << endl;
    }

    return 0;
}