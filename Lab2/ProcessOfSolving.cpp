#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <format>
#include <time.h>

using namespace std;

const double PI = 3.1415926;  // PI и E в ответах означают,
const double E = 2.7182818;  // что нет действительных решений

vector <vector <double>> tasks;
vector <string> surnames;

class Student {
public:
	string surname;
	vector <vector <double>> answers;
	Student(string surname) {
		this->surname = surname;
	};
	virtual void Solve(vector <vector <double>> tasks) {};
};

vector <Student*> students;

class GoodStudent : public Student {
public:
	GoodStudent(string surname) : Student(surname) { Solve(tasks); };

	void Solve(vector <vector <double>> tasks) override {
		double x1, x2, D, a, b, c;
		for (int i = 0; i < tasks.size(); i++) {
			a = tasks[i][0];
			b = tasks[i][1];
			c = tasks[i][2];
			D = b * b - 4 * a * c;

			if (D >= 0) {
				answers.push_back({ (-b + sqrt(D)) / 2 / a, (-b - sqrt(D)) / 2 / a });
			}
			else {
				answers.push_back({ PI, E });
			}
		}
	};


};
class BadStudent : public Student {
public:
	BadStudent(string surname) : Student(surname) { Solve(tasks); };

	void Solve(vector <vector <double>> tasks) override {
		for (int i = 0; i < tasks.size(); i++) {
			answers.push_back({ 0, 0 });
		}
	};


};
class MiddleStudent : public Student {
public:
	MiddleStudent(string surname) : Student(surname) { Solve(tasks); };

	void Solve(vector <vector <double>> tasks) override {
		double x1, x2, D, a, b, c;
		int student_knowledge;
		for (int i = 0; i < tasks.size(); i++) {
			a = tasks[i][0];
			b = tasks[i][1];
			c = tasks[i][2];
			D = b * b - 4 * a * c;
			student_knowledge = rand() % 2;

			if (student_knowledge) {
				if (D >= 0) {
					answers.push_back({ (-b + sqrt(D)) / 2 / a, (-b - sqrt(D)) / 2 / a });
				}
				else {
					answers.push_back({ PI, E });
				}
			}
			else {
				answers.push_back({ 0, 0 });
			}
		}
	};

};


class Teacher {
protected:
	vector <vector <double>> right_answers;
public:

	void GetRightAnswers() {
		double x1, x2, D, a, b, c;
		for (int i = 0; i < tasks.size(); i++) {
			a = tasks[i][0];
			b = tasks[i][1];
			c = tasks[i][2];
			D = b * b - 4 * a * c;

			if (D >= 0) {
				right_answers.push_back({ (-b + sqrt(D)) / 2 / a, (-b - sqrt(D)) / 2 / a });
			}
			else {
				right_answers.push_back({ PI, E });
			}
		}
	};

	int Check(Student* student) {
		int scores = 0;
		for (int i = 0; i < tasks.size(); i++) {
			if (right_answers[i] == student->answers[i]) scores += 1;
		}
		return scores;
	}

	void PrintProgressTable() {
		for (int i = 0; i < students.size(); i++) {
			cout << students[i]->surname << "  " << Check(students[i]) << "  " << tasks.size() << endl;
		}
	}

};


void input() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	double a, b, c;
	string surname;

	ifstream in1("tasks.txt");
	if (in1.is_open()) {
		while (in1 >> a >> b >> c) {
			tasks.push_back({ a, b ,c });
		}
	}
	in1.close();


	ifstream in2("surnames.txt");
	if (in2.is_open()) {
		while (getline(in2, surname))
		{
			surnames.push_back(surname);
		}
	}
	in2.close();

	int intellect;
	for (int i = 0; i < surnames.size(); i++) {
		intellect = rand() % 3;
		switch (intellect) {
		case 0:
			students.push_back(new GoodStudent(surnames[i]));
			break;
		case 1:
			students.push_back(new BadStudent(surnames[i]));
			break;
		case 2:
			students.push_back(new MiddleStudent(surnames[i]));
			break;
		}
	}

	Teacher teacher = Teacher();
	teacher.GetRightAnswers();
	teacher.PrintProgressTable();
}

void main() {
	input();
}