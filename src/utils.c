#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void trim_newline(char *s) {
    s[strcspn(s, "\r\n")] = '\0';
}

void read_line(const char *prompt, char *out, size_t size) {
    printf("%s", prompt);
    if (fgets(out, (int)size, stdin)) trim_newline(out);
    else { out[0] = '\0'; clearerr(stdin); }
}

int read_int(const char *prompt, int min, int max) {
    char buf[64], *end;
    long v;
    for (;;) {
        read_line(prompt, buf, sizeof(buf));
        v = strtol(buf, &end, 10);
        if (*buf && *end == '\0' && v >= min && v <= max) return (int)v;
        printf("Invalid input. Enter a number from %d to %d.\n", min, max);
    }
}

void timestamp_now(char out[32]) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(out, 32, "%Y-%m-%d %H:%M:%S", t);
}

int contains_icase(const char *h, const char *n) {
    if (!*n) return 1;
    for (; *h; h++) {
        const char *a = h, *b = n;
        while (*a && *b && tolower((unsigned char)*a) == tolower((unsigned char)*b)) { a++; b++; }
        if (!*b) return 1;
    }
    return 0;
}
