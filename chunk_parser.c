#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHUNK_SIZE 8192
#define OVERLAP 5

// This is the function Python will call
long count_errors(const char* filename, const char* search_str) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return -1;

    char buffer[CHUNK_SIZE + OVERLAP];
    long count = 0;
    size_t bytesRead;
    size_t search_len = strlen(search_str);

    bytesRead = fread(buffer, 1, CHUNK_SIZE, fp);
    while (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        char *ptr = buffer;
        while ((ptr = strstr(ptr, search_str)) != NULL) {
            count++;
            ptr += 1;
        }

        if (bytesRead == CHUNK_SIZE) {
            memcpy(buffer, buffer + CHUNK_SIZE - search_len, search_len);
            bytesRead = fread(buffer + search_len, 1, CHUNK_SIZE - search_len, fp);
            if (bytesRead > 0) bytesRead += search_len;
        } else {
            break;
        }
    }
    fclose(fp);
    return count;
}
