#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORD_LENGTH 15

char* parts[4];
FILE* fin;
FILE* fout;
int* hashes;
int used_hashes = 0;

// a < b? 1
int cmp(char* a, char* b) {
  int i = 0;
  while (a[i] != 0 || b[i] != 0) {
    if (a[i] > b[i]) {
      return 0;
    } else if (a[i] < b[i]) {
      return 1;
    }
    i++;
  }
  if (a[i] == 0) {
    return 0;
  }
  return 1;
}

int partition(char* a[], int l, int r) {
    char* t;

    char* x = a[r]; 
    for (int j = l; j <= r - 1; j++) { 
        if (cmp(a[j], x)) { 
            
            t = a[l];
            a[l] = a[j];
            a[j] = t;
            
            l++; 
        } 
    } 
    t = a[l];
    a[l] = a[r];
    a[r] = t;
    return l; 
}

void sort(char* numbers[], int l, int r)
{
    int index = partition(numbers, l, r);
    if (l < index){
        sort(numbers, l, index - 1);
    }
    if (r > index) {
        sort(numbers, index + 1, r);
    }
}

int check_ip() {
  char* ip = calloc(sizeof(char), 16);
  int p = 0;
  for (int i = 0; i < 4; ++i) {
    int len = strlen(parts[i]);
    memmove(ip + p, parts[i], len);
    p += len;
  }
  char* number = calloc(sizeof(char), 16);
  int number_pointer = 0;
  int dots = 0;
  int hash = 0;
  for (int i = 0; i < p; ++i) {
    if (ip[i] == '.') {
      dots += 1;
      if (!number_pointer) {
        return 0;
      }
      if (number_pointer > 1 && number[0] == '0') {
        return 0;
      }
      int n = atoi(number);
      if (n < 0 || n > 255) {
        return 0;
      }
      hash += n << (8 * (4 - dots));
      for (int k = 0; k < 16; ++k) {
        number[k] = 0;
      }
      number_pointer = 0;
    } else {
      number[number_pointer] = ip[i];
      number_pointer++;
    }
  }
  if (!number_pointer) {
    return 0;
  }
  if (number_pointer > 1 && number[0] == '0') {
    return 0;
  }
  int n = atoi(number);
  if (n < 0 || n > 255) {
    return 0;
  }
  hash += n;
  for (int i = 0; i < used_hashes; ++i) {
    if (hashes[i] == hash) {
      return 0;
    }
  }
  hashes[used_hashes] = hash;
  used_hashes++;
  return dots == 3;
}

void permutation(int l, int r) {
  if (l == r) {
    check_ip();
    return;
  } else {
    char* temp;
    for (int i = l; i < r; ++i) {
      temp = parts[i];
      parts[i] = parts[l];
      parts[l] = temp;
      permutation(l + 1, r);
      temp = parts[i];
      parts[i] = parts[l];
      parts[l] = temp;
    }
  }
}

int main() {
  fin = fopen("input.txt", "r");
  fout = fopen("output.txt", "w");
  for (int i = 0; i < 4; ++i) {
    parts[i] = calloc(sizeof(char), WORD_LENGTH);
    fscanf(fin, "%s", parts[i]);
  }
  hashes = calloc(sizeof(int), 30);
  permutation(0, 4);
  char* ips[30];
  for (int i = 0; i < used_hashes; ++i) {
    ips[i] = calloc(sizeof(char), 30);
    int pointer = 0;
    char* a = calloc(sizeof(char), 10);
    sprintf(a, "%d", (hashes[i] & 0xff000000) >> 24);
    memcpy(ips[i], a, strlen(a));
    pointer += strlen(a);
    *(ips[i] + pointer) = '.';
    pointer++;

    free(a);
    a = calloc(sizeof(char), 10);

    sprintf(a, "%d", (hashes[i] & 0xff0000) >> 16);
    memcpy(ips[i] + pointer, a, strlen(a));
    pointer += strlen(a);
    *(ips[i] + pointer) = '.';
    pointer++;

    free(a);
    a = calloc(sizeof(char), 10);

    sprintf(a, "%d", (hashes[i] & 0xff00) >> 8);
    memcpy(ips[i] + pointer, a, strlen(a));
    pointer += strlen(a);
    *(ips[i] + pointer) = '.';
    pointer++;

    free(a);
    a = calloc(sizeof(char), 10);

    sprintf(a, "%d", (hashes[i] & 0xff));
    memcpy(ips[i] + pointer, a, strlen(a));
  }
  sort(ips, 0, used_hashes - 1);
  for (int i = 0; i < used_hashes; ++i) {
    fprintf(fout, "%s\n", ips[i]);
  }
  return 0;
}
