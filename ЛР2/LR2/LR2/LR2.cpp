#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <mutex>

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Глобальні параметри
const float V = 1.0f;         // швидкість руху
const int N = 3;              // період зміни напрямку для трутнів (в секундах)
const int SIM_DURATION = 20; // тривалість симуляції (секунди)

// М'ютекс для синхронізації виводу в консоль
std::mutex cout_mutex;

// Клас бджоли-робочої
class WorkerBee {
    float x, y;               // поточна позиція
    float origin_x, origin_y;// координати точки народження
    bool to_zero = true;     // прапорець: рух до [0,0] або назад

public:
    WorkerBee(float startX, float startY)
        : x(startX), y(startY), origin_x(startX), origin_y(startY) {
    }

    void move() {
        while (true) {
            // Обчислення вектора напрямку
            float dx = (to_zero ? -x : origin_x - x);
            float dy = (to_zero ? -y : origin_y - y);
            float dist = sqrt(dx * dx + dy * dy);

            // Якщо близько до цілі — змінюємо напрямок
            if (dist < V) {
                x = (to_zero ? 0 : origin_x);
                y = (to_zero ? 0 : origin_y);
                to_zero = !to_zero;
            }
            else {
                // Переміщення на крок у напрямку цілі
                x += V * dx / dist;
                y += V * dy / dist;
            }

            // Вивід позиції (із захистом м'ютексом)
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                cout << "[WorkerBee] Position: (" << x << ", " << y << ")" << endl;
            }

            // Пауза 500 мс
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
};

// Клас трутня
class Drone {
    float x, y;                     // позиція
    float dirX, dirY;               // напрям руху
    std::mt19937 rng;              // генератор випадкових чисел
    std::uniform_real_distribution<float> angle_dist; // розподіл кутів

public:
    Drone(float startX, float startY)
        : x(startX), y(startY), rng(random_device{}()),
        angle_dist(0, 2 * M_PI) {
        changeDirection(); // ініціалізація напрямку
    }

    // Випадкова зміна напрямку
    void changeDirection() {
        float angle = angle_dist(rng);
        dirX = cos(angle);
        dirY = sin(angle);
    }

    void move() {
        int counter = 0;
        while (true) {
            // Зміна напрямку кожні N секунд (~N*2 кроки по 500мс)
            if (counter % (N * 2) == 0) {
                changeDirection();
            }

            // Переміщення
            x += V * dirX;
            y += V * dirY;

            // Вивід позиції
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                cout << "[Drone] Position: (" << x << ", " << y << ")" << endl;
            }

            ++counter;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
};

int main() {
    vector<thread> threads;

    // Створюємо 3 бджоли-робочі
    for (int i = 0; i < 3; ++i) {
        WorkerBee bee(10.0f + i * 5, 10.0f + i * 5);
        threads.emplace_back(&WorkerBee::move, bee); // потік викликає метод move()
    }

    // Створюємо 2 трутнів
    for (int i = 0; i < 2; ++i) {
        Drone drone(20.0f + i * 5, 20.0f + i * 5);
        threads.emplace_back(&Drone::move, drone);
    }

    // Очікуємо завершення симуляції
    this_thread::sleep_for(chrono::seconds(SIM_DURATION));

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        cout << "Simulation complete. Press Ctrl+C to terminate." << endl;
    }

    return 0; // Програма не завершує потоки (для демонстрації)
}
