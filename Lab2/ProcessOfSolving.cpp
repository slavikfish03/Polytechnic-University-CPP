#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const double PI = 3.1415926;  // PI и E в ответах означают, 
const double E = 2.7182818;  // что нет действительных решений


vector<double> SolveQuadraticEquation(double a, double b, double c) {
    double D = b * b - 4 * a * c;
    vector<double> roots;

    if (D >= 0.0) {
        double x1 = (-b + sqrt(D)) / (2 * a);
        double x2 = (-b - sqrt(D)) / (2 * a);
        roots.push_back(x1);
        roots.push_back(x2);
    }
    else {
        roots.push_back(PI);
        roots.push_back(E);
    }

    return roots;
}


class Student {
public:
    string surname;
    vector<vector<double>> answers;

    Student(string surname) : surname(surname) {}

    virtual void Solve(vector<vector<double>> tasks) = 0;
};


class GoodStudent : public Student {
public:
    GoodStudent(string surname) : Student(surname) {}

    void Solve(vector<vector<double>> tasks) override {
        for (const vector<double>& task : tasks) {
            answers.push_back(SolveQuadraticEquation(task[0], task[1], task[2]));
        }
    }
};


class BadStudent : public Student {
public:
    BadStudent(string surname) : Student(surname) {}

    void Solve(vector<vector<double>> tasks) override {
        for (const vector<double>& task : tasks) {
            answers.push_back({ 0, 0 });
        }
    }
};


class MiddleStudent : public Student {
public:
    MiddleStudent(string surname) : Student(surname) {}

    void Solve(vector<vector<double>> tasks) override {
        for (const vector<double>& task : tasks) {
            if (rand() % 2 == 0) {
                answers.push_back(SolveQuadraticEquation(task[0], task[1], task[2]));
            }
            else {
                answers.push_back({ 0, 0 });
            }
        }
    }
};


class Teacher {
protected:
    vector<vector<double>> right_answers;

public:
    void GetRightAnswers(const vector<vector<double>>& tasks) {
        for (const vector<double>& task : tasks) {
            right_answers.push_back(SolveQuadraticEquation(task[0], task[1], task[2]));
        }
    }

    int Check(const Student* student) {
        int scores = 0;
        for (size_t i = 0; i < right_answers.size(); i++) {
            if (right_answers[i] == student->answers[i]) {
                scores++;
            }
        }
        return scores;
    }

    void PrintProgressTable(const vector<Student*>& students) {
        for (int i = 0; i < students.size(); i++) {
            cout << students[i]->surname << "  " << Check(students[i]) << "  " << right_answers.size() << endl;
        }
    }

};


void input() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    ifstream fin_surnames("surnames.txt");
    vector<string> surnames;
    if (fin_surnames) {
        string surname;
        while (getline(fin_surnames, surname)) {
            surnames.push_back(surname);
        }
        fin_surnames.close();
    }

    ifstream fin_tasks("tasks.txt");
    vector<vector<double>> tasks;
    if (fin_tasks) {
        double a, b, c;
        while (fin_tasks >> a >> b >> c) {
            tasks.push_back({ a, b, c });
        }
        fin_tasks.close();
    }

    vector<Student*> students;
    for (const string& surname : surnames) {
        Student* student = nullptr;

        int intellect = rand() % 3;
        switch (intellect) {
        case 0:
            student = new GoodStudent(surname);
            break;
        case 1:
            student = new BadStudent(surname);
            break;
        case 2:
            student = new MiddleStudent(surname);
            break;
        }
        student->Solve(tasks);
        students.push_back(student);
    }

    Teacher teacher = Teacher();
    teacher.GetRightAnswers(tasks);
    teacher.PrintProgressTable(students);
}

void main() {
    input();
}
