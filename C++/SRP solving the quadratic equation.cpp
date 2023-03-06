#include <iostream>

using namespace std;


void CheckingDiscriminant(float D) {
	if (D < 0) {
		throw logic_error("Discriminant less than zero.");
	}
}

void CheckingHigherCoef(float* coef) {
	if (*coef == 0) {
		throw logic_error("The leading coefficient is 0 - this is not a quadratic equation.");
	}
}

float Discriminant(float a, float b, float c) {
	try {
		float D = b * b - 4 * a * c;
		CheckingDiscriminant(D);
	}
	catch (const exception& e) {
		cerr << e.what();
		exit(2);
	}
	return b * b - 4 * a * c;
}

float* Solution(float a, float b, float c) {
	float* result = (float*)malloc(sizeof(float) * 2);
	float D = Discriminant(a, b, c);
	*result = (-b + sqrt(D)) / (2 * a);
	*(result + 1) = (-b - sqrt(D)) / (2 * a);
	return result;
}

float* input() {
	float* coef = (float*)malloc(sizeof(float) * 3);
	try {
		cin >> *coef >> *(coef + 1) >> *(coef + 2);
		CheckingHigherCoef(coef);
	}
	catch (const exception& e) {
		cerr << e.what();
		exit(1);
	}
	return coef;
}

void output(float* coef) {
	float a = *coef;
	float b = *(coef + 1);
	float c = *(coef + 2);
	float* res = Solution(a, b, c);
	if (*res == *(res + 1)) {
		cout << "The equation has one root: " << *res << endl;
	}
	else {
		cout << "Equation roots: x1 = " << *res << ", x2 = " << *(res + 1);

	}
}

int main() {
	float* coef = input();
	output(coef);
	return 0;
}