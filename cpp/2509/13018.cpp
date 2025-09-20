#include <cstdio>
using namespace std;

int main() {
  int n, k;
  scanf("%d %d", &n, &k);

  if (n == k) {
    printf("Impossible\n");
    return 0;
  }

  int m = n - k;

  if (m % 2 == 0) {
    for (int i = 1; i <= m; i += 2) {
      printf("%d %d ", i + 1, i);
    }
  } else {
    printf("1 ");
    for (int i = 2; i <= m; i += 2) {
      printf("%d %d ", i + 1, i);
    }
  }

  for (int i = m + 1; i <= n; i++) printf("%d ", i);

  printf("\n");
}