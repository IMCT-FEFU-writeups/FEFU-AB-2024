#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Team {
  int team, solves, time;
  int wrong_solves[21];
} t[1005];

struct Package {
  int c, p, ti, r;
} d[1005];

int C, N;
FILE *in;
FILE *out; 

int cmp(const void *a, const void *b) {
  struct Team *t1 = (struct Team *)a, *t2 = (struct Team *)b;
  if (t1->solves != t2->solves)
    return t2->solves - t1->solves;
  else if (t1->time != t2->time)
    return t1->time - t2->time;
  else
    return t1->team - t2->team;
}

int cmp2(const void *a, const void *b) {
  struct Package *d1 = (struct Package *)a, *d2 = (struct Package *)b;
  return d1->ti - d2->ti;
}

int main() {
  extern FILE* in;
  extern FILE* out;
  in = fopen("input.txt", "r");
  out = fopen("output.txt", "w");
  fscanf(in, "%d %d", &C, &N);
  memset(t, 0, sizeof(t[0]) * C);
  for (int i = 1; i <= C; ++i) {
    t[i].team = i;
  }
  for (int i = 0; i < N; ++i) {
    fscanf(in, "%d %d %d %d", &d[i].c, &d[i].p, &d[i].ti, &d[i].r);
  }
  qsort(d, N, sizeof(d[0]), cmp2);
  for (int i = 0; i < N; ++i) {
    int c = d[i].c, p = d[i].p, ti = d[i].ti, r = d[i].r;
    if (r == 1) {
      if (t[c].wrong_solves[p] != -1) {
        t[c].time += (ti + t[c].wrong_solves[p] * 20 * 60);
        t[c].solves++;
      }
      t[c].wrong_solves[p] = -1;
    } else {
      if (t[c].wrong_solves[p] != -1) {
        t[c].wrong_solves[p]++;
      }
    }
  }
  qsort(t + 1, C, sizeof(t[0]), cmp);
  for (int i = 1; i <= C; ++i) {
    fprintf(out, i == 1 ? "%d" : " %d", t[i].team);
  }
  puts("");
  return 0;
}
