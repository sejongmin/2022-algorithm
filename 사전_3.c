#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

int main() {
	char c;
	int a, b, m, cnt;
	scanf("%d %d %d", &a, &b, &cnt);

	getchar();
	while (cnt) {
		scanf("%c", &c);
		m = (a + b) / 2;

		if (c == 'N')
			b = m;
		if (c == 'Y')
			a = m + 1;

		cnt--;
	}
	printf("%d", a);

	return 0;
}