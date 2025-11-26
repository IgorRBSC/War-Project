#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int read_int(const char *prompt) {
    int val;
    printf("%s", prompt);
    while (scanf("%d", &val) != 1) {
        clear_input_buffer();
        printf("Entrada inválida. Tente novamente: ");
    }
    clear_input_buffer();
    return val;
}

char *read_line(const char *prompt) {
    printf("%s", prompt);
    size_t size = 128;
    char *buf = malloc(size);
    if (!buf) return NULL;
    if (!fgets(buf, (int)size, stdin)) { free(buf); return NULL; }
    // remove newline
    size_t len = strlen(buf);
    if (len && buf[len-1] == '\n') buf[len-1] = '\0';
    // if buffer was full, try to read remaining chars
    if (len == size-1 && buf[len-1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
    return buf;
}

bool str_equal_ignore_case(const char *a, const char *b) {
    if (!a || !b) return false;
    while (*a && *b) {
        char ca = (*a >= 'A' && *a <= 'Z') ? (*a - 'A' + 'a') : *a;
        char cb = (*b >= 'A' && *b <= 'Z') ? (*b - 'A' + 'a') : *b;
        if (ca != cb) return false;
        a++; b++;
    }
    return *a == *b;
}
