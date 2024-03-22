#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_LEN 100001

FILE* in;
FILE* out;

typedef struct list_item{
  struct list_item* next;
  int value;
} list_item;

typedef struct list {
  list_item* start;
  list_item* end;
  bool is_empty;
} list;

void add_value_to_list(list* list, int value) {
  list_item* new = malloc(sizeof(list_item));
  new->value = value;
  
  if (list->is_empty) {
    list->start = new;
    list->end = new;
    list->is_empty = false;
    return;
  }
  list->end->next = new;
  list->end = new;
}

void print_list(list* list) {
  extern FILE* out;
  list_item* i = list->start;
  if (list->is_empty) {
    return;
  }
  while (true) {
    fprintf(out, "%d ", i->value);
    if (i == list->end){
      break;
    }
    i = i->next;
  }
}

int main() {
  extern FILE* in;
  extern FILE* out;
  int  n, key, value;
  list hash_table[HASH_TABLE_LEN];
  
  in = fopen("input.txt", "r");
  out = fopen("output.txt", "w");
  for (int i = 0; i < HASH_TABLE_LEN; i++) {
    hash_table[i].is_empty = true;
  }
  fscanf(in, "%d", &n);
  for (int i = 0; i < n; i++){
      fscanf(in, "%d %d", &key, &value);
      add_value_to_list(&hash_table[key], value);
  }

  for (int i = 0; i < HASH_TABLE_LEN; i++){
      print_list(&hash_table[i]);
  }
  return 0;
}
