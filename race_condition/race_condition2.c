#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

int shared_variable = 0; // Общая переменная для состояния гонки
pthread_mutex_t mutex; // Мьютекс для синхронизации доступа

// Целевая функция для фаззинга: проверка наличия заглавной буквы в начале строки.
void *increment(void *arg) {
    int *increment_value = (int *)arg;
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex); // Захватываем мьютекс
        *increment_value += 1; // Изменение общей переменной
        pthread_mutex_unlock(&mutex); // Освобождаем мьютекс
    }
    return NULL;
}

// Функция Fuzz, вызываемая фаззером с разными входными данными.
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // Преобразуем входные данные в строку (с нулевым завершением).
    char input[size + 1];
    for (size_t i = 0; i < size; i++) {
        input[i] = (char)data[i];
    }
    input[size] = '\0';

    pthread_t thread1, thread2; // Объявляем потоки здесь

    pthread_mutex_init(&mutex, NULL); // Инициализируем мьютекс

    // Создаем два потока и передаем им указатель на общую переменную shared_variable
    pthread_create(&thread1, NULL, increment, &shared_variable);
    pthread_create(&thread2, NULL, increment, &shared_variable);

    // Ждем завершения потоков
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex); // Уничтожаем мьютекс

    // Выводим значение общей переменной после состояния гонки
    printf("Значение shared_variable: %d\n", shared_variable);

    return 0;
}
