#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

typedef struct {
    int id;
    double cash;
    double limit;
    int status;
} ATM;

ATM *atms = NULL;
int count = 0;  

void addATM();
void printatms();
void searchATM();
void editATM();
void removeLastATM();
void freeAllMemory();
void expandArray(int n);

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    do {
        printf("\n--- МЕНЮ БАНКОМАТОВ ---\n");
        printf("1. Добавить банкомат\n");
        printf("2. Вывести все банкоматы\n");
        printf("3. Найти банкомат\n");
        printf("4. Редактировать банкомат\n");
        printf("5. Удалить последний банкомат\n"); // <-- НОВЫЙ ПУНКТ
        printf("0. Выход\n");
        printf("Выберите действие: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); 
            choice = -1;
        }

        switch (choice) {
            case 1: addATM(); break;
            case 2: printatms(); break;
            case 3: searchATM(); break;
            case 4: editATM(); break;
            case 5: removeLastATM(); break;
            case 0: 
                freeAllMemory();
                printf("Выход из программы...\n"); 
                break;
            default: printf("Неверный выбор.\n");
        }
    } while (choice != 0);
}

void addATM() {
    expandArray(1);

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

void removeLastATM() {
    if (count == 0) {
        printf("\nОшибка: Список банкоматов уже пуст!\n");
        return;
    }

    if (count == 1) {
        free(atms);
        atms = NULL;
        count = 0;
    } else {
        ATM *newAtms = (ATM*)malloc((count - 1) * sizeof(ATM));
        
        if (newAtms == NULL) {
            printf("Критическая ошибка: Не удалось выделить память!\n");
            exit(1);
        }

        for (int i = 0; i < count - 1; i++) {
            newAtms[i] = atms[i];
        }

        free(atms);
        atms = newAtms;
        count--;
    }

    printf("\nПоследний банкомат успешно удален, память освобождена!\n");
}

void freeAllMemory() {
    if (atms != NULL) {
        free(atms);
        atms = NULL;
        count = 0;
    }
    printf("\nВся память успешно освобождена!\n");
}
void expandArray(int n) {
    ATM *newAtms = (ATM*)malloc((count + n) * sizeof(ATM));
    
    if (newAtms == NULL) {
        printf("Ошибка: память не выделена!\n");
        exit(1);
    }

    if (atms != NULL) {
        for (int i = 0; i < count; i++) {
            newAtms[i] = atms[i];
        }
        free(atms);
    }

    atms = newAtms;
}