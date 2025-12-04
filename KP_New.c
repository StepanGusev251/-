#include <stdio.h>
#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <locale.h>
#define _USE_MATH_DEFINES
#include <math.h>

double f1(double x);
double f2(double x);
double f3(double x);
double cal_f(double x);
double find_Min(double start, double end);
double find_Max(double start, double end);
double find_x_by_y(double Y, double eps, double a, double b);
double derivative(double x, double h);// Функция вычисления производной по формуле 


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
    return cosh(3 * x - 1); 
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

// Функция вычисления производной по формуле 
double derivative(double x, double h) {  
    return (cal_f(x + h) - cal_f(x)) / h;
}

/**
 * Поиск x такого, что |cal_f(x) - Y| < eps методом бинарного поиска.
 *
 * @param Y      Целевое значение функции
 * @param eps    Требуемая точность (положительное число)
 * @param a      Левая граница отрезка поиска
 * @param b      Правая граница отрезка поиска
 * @return       Найденное значение x или NAN при ошибке
 */
//Поиск X по Y
double find_x_by_y(double Y, double eps, double a, double b) {
    double fa, fb, fm, x;

    // Проверяем значения на границах
    fa = cal_f(a);
    fb = cal_f(b);

    // Убедимся, что Y лежит между f(a) и f(b)
    if ((fa < Y && fb < Y) || (fa > Y && fb > Y)) {
        printf("Ошибка: Y=%.6f не лежит между f(a)=%.6f и f(b)=%.6f.\n", Y, fa, fb);
        return NAN;
    }

    // Бинарный поиск
    while (b - a > eps) {
        x = (a + b) / 2.0;
        fm = cal_f(x);

        if (fm < Y) {
            a = x;  // Ищем справа (значение функции мало)
        }
        else if (fm > Y) {
            b = x;  // Ищем слева (значение функции велико)
        }
        else {
            break;  // Точное совпадение (крайне редко)
        }
    }

    // Финальное значение x — середина текущего отрезка
    x = (a + b) / 2.0;
    return x;
}

//Поиск минимума/максимума
double find_Min(double start, double end) {
    if (start >= end) {
        printf("Ошибка: start должен быть меньше end\n");
        return 0.0;
    }

    double min = cal_f(start);
    double y;

    while (start < end) {
        y = cal_f(start);
        if (min > y) {
            min = y;
        }
        start += 0.001;
    }
    return min;
}
double find_Max(double start, double end) {
    if (start >= end) {
        printf("Ошибка: start должен быть меньше end\n");
        return 0.0;
    }

    double max = cal_f(start);
    double y;

    while (start < end) {
        y = cal_f(start);
        if (max < y) {
            max = y;
        }
        start += 0.001;
    }
    return max;
}


int main() {
    int choice, count;
    double x, y, start, end, step, eps;
    double h = 1e-6;
    double deriv;

    setlocale(LC_ALL, "RUS");

    printf("|                      КУСОЧНАЯ ФУНКЦИЯ                        |\n");
    printf("|--------------------------------------------------------------|\n");
    printf("|Определена как:                                               |\n");
    printf("|f(x) = ln(1+|x|) / (1+e^(-x))           при x < -0.5          |\n");
    printf("|f(x) = cosh(3x-1)          _______      при -0.5 <= x <= 0.5  |\n");
    printf("|f(x) = sin(x^2)·cos(x) / -/(1+x^6)      при x > 0.5           |\n");
    printf("|______________________________________________________________|\n");

    do {
        printf("|                      Меню программы                          |\n");
        printf("|Команда 1. Значение функции в точке                           |\n");
        printf("|Команда 2. Таблица значений                                   |\n");
        printf("|Команда 3. Поиск минимума/максимума                           |\n");
        printf("|Команда 4. Поиск X по Y                                       |\n");
        printf("|Команда 5. Производная в точке                                |\n");
        printf("|Команда 0. Выход из программы                                 |\n");
        printf("|______________________________________________________________|\n");
        printf("|Необходимо выбрать команду:");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("|Значение функции в точке                                      |\n");
            printf("|Введите x = ");
            scanf("%lf", &x);
            printf("|f(%.2f) = %.6f                                            |\n", x, cal_f(x));
            printf("|--------------------------------------------------------------|\n");
            break;

        case 2:
            printf("Начало интервала: ");
            scanf("%lf", &start);
            printf("Шаг: ");
            scanf("%lf", &step);

            printf("Количество отсчетов: ");
            scanf("%d", &count);
            if (count <= 0) {
                printf("Ошибка! Количество отсчетов должно быть положительным.\n");
                break;
            }

            printf("\n|================================|\n");
            printf("|  Таблица значений функции      |\n");
            printf("|================================|\n");
            printf("|   x              f(x)          |\n");
            printf("|================================|\n");

            x = start;
            for (int i = 0; i < count; i++) {
                y = cal_f(x);
                if (isnan(y)) {
                    printf("|%10.6f   не определена  |\n", x);
                }
                else {
                    printf("|%10.6f   %12.8f       |\n", x, y);
                }
                x += step;
            }
            printf("|================================|\n");
            printf("Всего значений: %d\n", count);
            printf("|--------------------------------------------------------------|\n");
            break;
        case 3:
            printf("|Поиск минимума и максимума \n");
            printf("Начало интервала: ");
            scanf("%lf", &start);
            printf("Конец интервала: ");
            scanf("%lf", &end);

            if (start >= end) {
                printf("Ошибка! Начало должно быть меньше конца.\n");
                break;
            }

            printf("Max в интервале %.5lf\n", find_Max(start, end));
            printf("Min в интервале %.5lf\n", find_Min(start, end));
            printf("|--------------------------------------------------------------|\n");
            break;

        case 4:
            printf("Введите Y: ");
            scanf("%lf", &y);
            printf("Начало поиска: ");
            scanf("%lf", &start);
            printf("Конец поиска: ");
            scanf("%lf", &end);

            if (start > end) {
                printf("Ошибка! Начало поиска должно быть меньше конца.\n");
                break;
            }

            printf("Точность совпадения: ");
            scanf("%lf", &eps);

            if (eps <= 0) {
                printf("Ошибка! Точность должна быть положительной.\n");
                break;
            }
            x = find_x_by_y(y, eps, start, end);
            if (!isnan(x)) {
                double fm = cal_f(x);
                printf("Найденное x: %.8f\n", x);
                printf("f(x) = %.8f, отклонение = %.8f\n", fm, fabs(fm - y));
            }
            printf("|--------------------------------------------------------------|\n");
            break;
        case 5:
            printf("Введите значение x: ");
            scanf("%lf", &x);

            deriv = derivative(x, h);

            printf("f'(%.6f) = %.6f\n", x, deriv);
            printf("|--------------------------------------------------------------|\n");
            break;
        case 0:
            printf("Выход! Работа программы завершена!\n");
            break;
        default:
            printf("Неверный выбор!\n");
        }
    } while (choice != 0);
}