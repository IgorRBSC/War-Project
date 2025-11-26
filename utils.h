#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

void clear_input_buffer(void);
int read_int(const char *prompt);
char *read_line(const char *prompt);
bool str_equal_ignore_case(const char *a, const char *b);

#endif
