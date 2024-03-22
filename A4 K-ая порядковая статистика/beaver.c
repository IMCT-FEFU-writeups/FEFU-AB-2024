#include <stdio.h>

void swap(int *a, int *b) {
  int t;
  t = *a;
  *a = *b;
  *b = t;
}

int partition(int a[], int l, int r) {
  int t;
  int x = a[r];

  for (int i = l; i <= r - 1; i++) {
    if (a[i] <= x) {

      swap(&a[l], &a[i]);

      l++;
    }
  }
  t = a[l];
  a[l] = a[r];
  a[r] = t;
  return l;
}

int findOrderStatistics(int a[], int l, int r, int k) {
  int pivot = partition(a, l, r);
  if (pivot - l == k - 1) {
    return a[pivot];
  } else if (pivot - l > k - 1) {
    return findOrderStatistics(a, l, pivot - 1, k);
  }
  return findOrderStatistics(a, pivot + 1, r, k - pivot + l - 1);
}

int main() {
  int q, v, p, n, k;
  FILE *in = fopen("input.txt", "r");
  FILE *out = fopen("output.txt", "w");

  fscanf(in, "%d %d %d %d %d", &q, &v, &p, &n, &k);
  int a[n];
  a[0] = p;
  for (int i = 1; i < n; ++i) {
    a[i] = (a[i - 1] * q) % v;
  }

  int result = findOrderStatistics(a, 0, n - 1, k);
  fprintf(out, "%d", result);
  return 0;
}
