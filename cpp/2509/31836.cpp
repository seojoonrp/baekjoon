#include <cstdio>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);

  if ((n % 3 == 0) || (n % 3 == 1)) {
    printf("%d\n", n * 2 / 3);
    for (int i = 1; i <= n / 3; i++) {
      printf("%d\n%d\n", i * 3 - 2, i * 3 - 1);
    }
    printf("%d\n", n / 3);
    for (int i = 1; i <= n / 3; i++) {
      printf("%d\n", i * 3);
    }
  } else {
    printf("%d\n", (n - 2) * 2 / 3 + 1);
    printf("1\n");
    for (int i = 1; i <= n / 3; i++) {
      printf("%d\n%d\n", i * 3, i * 3 + 1);
    }
    printf("%d\n", n / 3 + 1);
    printf("2\n");
    for (int i = 1; i <= n / 3; i++) {
      printf("%d\n", i * 3 + 2);
    }
  }
}