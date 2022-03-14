#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct number_t {
	double imagPart;
	double realPart;
}number_t;

typedef struct root_t {
	number_t x1;
	number_t x2;
}root_t;

root_t Initialization() {
	root_t roots;
	roots.x1.realPart = 0.0;
	roots.x2.realPart = 0.0;
	roots.x1.imagPart = 0.0;
	roots.x2.imagPart = 0.0;
	return roots;
}

root_t Solution(double coeff[]) {
	root_t roots = Initialization();
	double D = 0.0;
	if (fabs(coeff[2] - 0.0) < 0.0000001) {
		roots.x1.realPart = -coeff[1] / coeff[0];
		return roots;
	}
	D = coeff[1] * coeff[1] - 4.0 * coeff[0] * coeff[2];
	if (fabs(D - 0.0) < 0.0000001) {
		roots.x1.realPart = -coeff[1] / (2.0 * coeff[0]);
		roots.x2.realPart = roots.x1.realPart;
		return roots;
	}
	if (D > 0.0) {
		D = sqrt(D);
		roots.x1.realPart = (-coeff[1] + D) / (2.0 * coeff[0]);
		roots.x2.realPart = (-coeff[1] - D) / (2.0 * coeff[0]);
		return roots;
	}
	roots.x1.realPart = -coeff[1] / (2.0 * coeff[0]);
	roots.x2.realPart = roots.x1.realPart;
	roots.x1.imagPart = sqrt(-D) / (2.0 * coeff[0]);
	roots.x2.imagPart = -roots.x1.imagPart;
	return roots;
}

void WorkWithClient(double coeff[]) {
	printf("Enter the coefficients of the equation starting with x^2 and ending with the free term separated by a space\n\n");
	scanf_s("%lf %lf %lf", &coeff[0], &coeff[1], &coeff[2]);
}

void Print(root_t roots) {
	if (fabs(roots.x1.imagPart - roots.x2.imagPart) < 0.0000001 && fabs(roots.x1.realPart - roots.x2.realPart) < 0.0000001 && fabs(roots.x1.imagPart - 0.0) < 0.0000001) {
		printf("\nRoot: %.5f", roots.x1.realPart);
		return;
	}
	if (fabs(roots.x1.imagPart - roots.x2.imagPart) < 0.0000001 && fabs(roots.x1.realPart - roots.x2.realPart) < 0.0000001) {
		printf("\nRoot: %.5f + %.5fi", roots.x1.realPart, roots.x1.imagPart);
		return;
	}
	printf("\nRoots:");
	if (fabs(roots.x1.imagPart - 0.0) < 0.0000001)
		printf("%.5f; ", roots.x1.realPart);
	else
		printf("%.5f + %.5fi; ", roots.x1.realPart, roots.x1.imagPart);
	if (fabs(roots.x2.imagPart - 0.0) < 0.0000001) {
		printf("%.5f", roots.x2.realPart);
		return;
	}
	printf("%.5f + %.5fi", roots.x2.realPart, roots.x2.imagPart);
}

int main() {
	double coeff[3];
	int i = 0;
	for (; i < 3; i++)
		coeff[i] = 0.0;
	WorkWithClient(coeff);
	root_t roots = Solution(coeff);
	Print(roots);
	return 0;
}