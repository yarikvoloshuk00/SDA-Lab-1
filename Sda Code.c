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
void sortATMs();
void insertATMAtPosition();
void removeATMByIndex();

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    do {
        printf("\n--- МЕНЮ БАНКОМАТОВ ---\n");
        printf("1. Добавить банкомат\n");
        printf("2. Вывести все банкоматы\n");
        printf("3. Найти банкомат\n");
        printf("4. Редактировать банкомат\n");
        printf("5. Удалить последний банкомат\n");
        printf("6. Сортировать банкоматы\n");
        printf("7. Вставить банкомат на указанную позицию\n");
        printf("8. Удалить банкомат по индексу\n");
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
            case 6: sortATMs(); break;
            case 7: insertATMAtPosition(); break;
            case 8: removeATMByIndex(); break;
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

void sortATMs() {
    if (count == 0) {
        printf("\nСписок банкоматов пуст!\n");
        return;
    }

    int field;
    printf("\n--- Сортировка банкоматов ---\n");
    printf("Выберите поле для сортировки:\n");
    printf("1. ID\n");
    printf("2. Наличные\n");
    printf("3. Лимит\n");
    printf("4. Статус\n");
    printf("Ваш выбор: ");
    scanf("%d", &field);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int needSwap = 0;

            switch (field) {
                case 1:
                    if (atms[j].id > atms[j + 1].id) needSwap = 1;
                    break;
                case 2:
                    if (atms[j].cash > atms[j + 1].cash) needSwap = 1;
                    break;
                case 3:
                    if (atms[j].limit > atms[j + 1].limit) needSwap = 1;
                    break;
                case 4:
                    if (atms[j].status > atms[j + 1].status) needSwap = 1;
                    break;
                default:
                    printf("Неверное поле для сортировки.\n");
                    return;
            }

            if (needSwap) {
                ATM temp = atms[j];
                atms[j] = atms[j + 1];
                atms[j + 1] = temp;
            }
        }
    }

    printf("Сортировка выполнена успешно!\n");
}

void insertATMAtPosition() {
    int position;

    printf("\n--- Вставка банкомата на позицию ---\n");
    printf("Введите позицию для вставки (от 0 до %d): ", count);
    scanf("%d", &position);

    if (position < 0 || position > count) {
        printf("Ошибка: неверная позиция.\n");
        return;
    }

    expandArray(1);

    for (int i = count; i > position; i--) {
        atms[i] = atms[i - 1];
    }

    printf("Введите ID: ");
    scanf("%d", &atms[position].id);

    printf("Введите наличные: ");
    scanf("%lf", &atms[position].cash);

    printf("Введите лимит: ");
    scanf("%lf", &atms[position].limit);

    printf("Введите статус (1 - Активен, 0 - Не работает): ");
    scanf("%d", &atms[position].status);

    count++;
    printf("Банкомат успешно вставлен на позицию %d!\n", position);
}

void removeATMByIndex() {
    int index;

    if (count == 0) {
        printf("\nОшибка: список банкоматов пуст!\n");
        return;
    }

    printf("\n--- Удаление банкомата по индексу ---\n");
    printf("Введите индекс для удаления (от 0 до %d): ", count - 1);
    scanf("%d", &index);

    if (index < 0 || index >= count) {
        printf("Ошибка: неверный индекс.\n");
        return;
    }

    for (int i = index; i < count - 1; i++) {
        atms[i] = atms[i + 1];
    }

    if (count - 1 == 0) {
        free(atms);
        atms = NULL;
        count = 0;
    } else {
        ATM *newAtms = (ATM*)malloc((count - 1) * sizeof(ATM));

        if (newAtms == NULL) {
            printf("Ошибка: память не выделена!\n");
            exit(1);
        }

        for (int i = 0; i < count - 1; i++) {
            newAtms[i] = atms[i];
        }

        free(atms);
        atms = newAtms;
        count--;
    }

    printf("Банкомат по индексу %d успешно удалён!\n", index);
}
