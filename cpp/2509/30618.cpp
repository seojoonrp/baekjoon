#include <cstdio>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);

  if (n % 2 == 0) {
    for (int i = 1; i <= n / 2; i++) {
      printf("%d ", i * 2);
    }
    for (int i = n / 2; i >= 1; i--) {
      printf("%d ", i * 2 - 1);
    }
  } else {
    for (int i = 1; i <= n / 2; i++) {
      printf("%d ", i * 2);
    }
    printf("%d ", n);
    for (int i = n / 2; i >= 1; i--) {
      printf("%d ", i * 2 - 1);
    }
  }
  printf("\n");
}