#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

int shared_variable = 0;

// Целевая функция для фаззинга: проверка наличия заглавной буквы в начале строки.
void *increment(void *arg) {
    char *input = (char *)arg;
    int increment_value = atoi(input); // Преобразуем строку в целое число
    for (int i = 0; i < 1000000; i++) {
        shared_variable += increment_value;
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

    // Создаем два потока и передаем в них строку как аргумент
    pthread_create(&thread1, NULL, increment, input);
    pthread_create(&thread2, NULL, increment, input);

    // Ждем завершения потоков
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
