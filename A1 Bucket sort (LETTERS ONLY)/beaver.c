#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 33554432 /* 128 ^ 3 */

int hash(char* word) {
    return (word[0] << 16) + (word[1] << 8) + word[2];
}

void unhash(char* to, int from) {
  to[2] = from & 0xff;
  from >>= 8;
  to[1] = from & 0xff;
  from >>= 8;
  to[0] = from & 0xff;
}

int main() {
  FILE* input = fopen("input.txt", "r");
  FILE* output = fopen("output.txt", "w+");
  int n;
  fscanf(input, "%d", &n);

  int* buckets = (int*)calloc(sizeof(int), ARRAY_SIZE);
  char* word = (char*)malloc(sizeof(char) * 3);
  for (int i = 0; i < n; ++i) {
    fscanf(input, "%3s", word);
    buckets[hash(word)] += 1;
  }

  for (int i = 0; i < ARRAY_SIZE; ++i) {
    for (int j = 0; j < buckets[i]; ++j) {
      unhash(word, i);
      fprintf(output, "%3s\n", word);
    }
  }

  return 0;
}

