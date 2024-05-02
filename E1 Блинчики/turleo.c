#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fin = fopen("input.txt", "r");
  FILE *fout = fopen("output.txt", "w");

  int n;
  fscanf(fin, "%d", &n);
  char* pancakes = malloc(sizeof(char) * (n + 1));
  for (int i = 0; i < n; ++i) {
    fscanf(fin, " %c", &pancakes[n - i]);
  }
  pancakes[0] = 'W';
  int down = 0;
  for (int i = 1; i < n + 1; ++i) {
    if (pancakes[i] != pancakes[i - 1]) {
      down++;
    }
  }
  fprintf(fout, "%d", down);
}

