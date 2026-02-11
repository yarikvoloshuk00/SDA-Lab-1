#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

typedef struct {
    int id;
    double cash;
    double limit;
    int status;
} ATM;

ATM atms[10];
int count = 0;

void addATM();
void printatms();
void searchATM();
void editATM();

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    do {
        printf("\n--- МЕНЮ БАНКОМАТОВ ---\n");
        printf("1. Добавить банкомат\n");
        printf("2. Вывести все банкоматы\n");
        printf("3. Найти банкомат\n");
        printf("4. Редактировать банкомат\n");
        printf("0. Выйти\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addATM();
                break;
            case 2:
                printatms();
                break;
            case 3:
                searchATM();
                break;
            case 4:
                editATM();
                break;
            case 0:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}

void addATM() {
    if (count >= 10) {
        printf("Ошибка: Память переполнена!\n");
        return;
    }

    printf("\n--- Добавление нового банкомата ---\n");
    
    printf("Введите ID: ");
    scanf("%d", &atms[count].id);

    printf("Введите наличные: ");
    scanf("%lf", &atms[count].cash);

    printf("Введите лимит: ");
    scanf("%lf", &atms[count].limit);

    printf("Введите статус (1 - Активен, 0 - Не работает): ");
    scanf("%d", &atms[count].status);

    count++;
    printf("Банкомат успешно добавлен!\n");
}

void printatms() {
    if (count == 0) {
        printf("\nСписок банкоматов пуст!\n");
        return;
    }

    printf("\n--- Список всех банкоматов ---\n");

    for (int i = 0; i < count; i++) {
        printf("\n[Банкомат №%d]\n", i + 1);
        printf("ID: %d\n", atms[i].id);
        printf("Наличные: %.2f\n", atms[i].cash);
        printf("Лимит: %.2f\n", atms[i].limit);

        if (atms[i].status == 1) {
            printf("Статус: Активен\n");
        } else {
            printf("Статус: Не работает\n");
        }
    }
}

void searchATM() {
    int id;
    int found = 0;

    printf("\n--- Поиск банкомата ---\n");
    printf("Введите ID для поиска: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (atms[i].id == id) {
            printf("\nБанкомат найден!\n");
            printf("ID: %d\n", atms[i].id);
            printf("Наличные: %.2f\n", atms[i].cash);
            printf("Лимит: %.2f\n", atms[i].limit);
            
            if (atms[i].status == 1) {
                printf("Статус: Активен\n");
            } else {
                printf("Статус: Не работает\n");
            }
            
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Банкомат с ID %d не найден.\n", id);
    }
}

void editATM() {
    int id;
    int found = 0;

    printf("\n--- Редактирование банкомата ---\n");
    printf("Введите ID банкомата, который хотите изменить: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (atms[i].id == id) {
            found = 1;
            printf("\nБанкомат найден! Введите новые данные.\n");

            printf("Новая сумма наличных: ");
            scanf("%lf", &atms[i].cash);

            printf("Новый лимит: ");
            scanf("%lf", &atms[i].limit);

            printf("Новый статус (1 - Активен, 0 - Не работает): ");
            scanf("%d", &atms[i].status);

            printf("Данные успешно обновлены!\n");
            break;
        }
    }

    if (found == 0) {
        printf("Ошибка: Банкомат с ID %d не найден.\n", id);
    }
}