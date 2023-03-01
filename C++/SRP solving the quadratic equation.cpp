#include <iostream>

float Discriminant(float a, float b, float c) {
	return b * b - 4 * a * c;
}

float X1(float a, float b, float c, float D) {
	return (-b + sqrt(D)) / (2 * a);
}

float X2(float a, float b, float c, float D) {
	return (-b - sqrt(D)) / (2 * a);
}


void Solution(float D, float X1, float X2) {
	if (D < 0) {
		std::cout << "Решения в вещественных числах нет.";
	}
	else if (D > 0) {
		std::cout << "Решения уравнения: х1 = " << X1 << ", х2 = " << X2 << std::endl;
		}
	else {
		std::cout << "У уравнения совпали корни: х = " << X1 << std::endl;
	}
}

void main() {
	float a, b, c;
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите коэффициенты квадратного уравнения: a, b, c." << std::endl;
	std::cin >> a >> b >> c;
	if (a == 0) {
		std::cout << "Ваше уравнение не является квадратным." << std::endl;
	}
	else {
		Solution(Discriminant(a, b, c), X1(a, b, c, Discriminant(a, b, c)), X2(a, b, c, Discriminant(a, b, c)));
	}
}