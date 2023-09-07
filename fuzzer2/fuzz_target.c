#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Целевая функция для фаззинга: проверка наличия заглавной буквы в начале строки.
bool hasUpperCase(const char *input) {
    if (input == NULL || input[0] == '\0') {

        return false;
    }
    return input[0] >= 'A' && input[0] <= 'Z';
}

// Функция Fuzz, вызываемая фаззером с разными входными данными.
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // Преобразуем входные данные в строку (с нулевым завершением).
    char input[size + 1];
    for (size_t i = 0; i < size; i++) {
        input[i] = (char)data[i];
    }
    input[size] = '\0';

    (void)hasUpperCase(input);

    return 0;
}
