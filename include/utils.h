#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void trim_newline(char *s);
void read_line(const char *prompt, char *out, size_t size);
int read_int(const char *prompt, int min, int max);
void timestamp_now(char out[32]);
int contains_icase(const char *haystack, const char *needle);

#endif
