#include <stdio.h>
#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <locale.h>
#define _USE_MATH_DEFINES
#include <math.h>

// Функция вычисления f(x) для x < -0.5
double f1(double x) {
    return log(1 + fabs(x)) / (1 + exp(-x));
}

// Функция вычисления f(x) для x > 0.5
double f2(double x) {
    return sin(x * x) * cos(x) / sqrt(1 + pow(x, 6));
}

// Функция вычисления f(x) для -0.5 <= x <= 0.5 
double f3(double x) {
    return cosh(3 * x - 1) / cosh(3 * x - 1); // Всегда равно 1
}

// Основная функция вычисления f(x)
double cal_f(double x) {
    if (x < -0.5) {
        return f1(x);
    }
    else if (x > 0.5) {
        return f2(x);
    }
    else if (x >= -0.5 && x <= 0.5) {
        return f3(x);
    }
    else {
        return NAN; // Неопределено
    }
}
int main() {
    int choice;
    double x, start, end, step;
    setlocale(LC_ALL, "RUS");

    printf("КУСОЧНАЯ ФУНКЦИЯ\n");

    do {
        printf("\n1 - Вычислить f(x)\n");
        printf("2 - Таблица значений\n");
        printf("3 - Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("x = ");
            scanf("%lf", &x);
            printf("f(%.2f) = %.6f\n", x, cal_f(x));
            break;

        case 2:
            printf("Начало: ");
            scanf("%lf", &start);
            printf("Конец: ");
            scanf("%lf", &end);
            printf("Шаг: ");
            scanf("%lf", &step);

            printf("\n   x      f(x)\n");
            printf("----------------\n");
            for (double x = start; x <= end; x += step) {
                printf("%6.2f  %8.4f\n", x, cal_f(x));
            }
            break;

        case 3:
            printf("Выход\n");
            break;

        default:
            printf("Неверный выбор!\n");
        }
    } while (choice != 3);
}