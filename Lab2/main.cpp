#include "header.hpp"
#include <fstream>

const char* NAMES[7] = {"Dikareva Maria", "Rubanova Valeria", "Pustynnaia Julia", "Tronyagina Aleksandra", "Krasnikov Roman", "Felini Terial", "Sharkis Zuo"};
const int numStudents = 7;

void ReadFile(Teacher& equals) {
	std::ifstream file("coeff.txt", std::ios::in);
	if (file.is_open() == false)
		return;
	QuadraticEquation coeff;
	while (file >> coeff.a >> coeff.b >> coeff.c)
		equals.eqList.push_back(coeff);
	file.close();
}

void StudentsDoEqs(const char** names, const int numStudents, Teacher& message) {
	for (int i = 0; i < numStudents / 3.0; ++i) {
		MiddleStudent student(names[i]);
		student.SolveEq(message);
		student.SendAnswers(message);
	}
	for (int i = static_cast <int> (ceil(numStudents / 3.0)); i < 2.0 * numStudents / 3.0; ++i) {
		GoodStudent student(names[i]);
		student.SolveEq(message);
		student.SendAnswers(message);
	}
	for (int i = static_cast <int> (ceil(2.0 * numStudents / 3.0)); i < numStudents; ++i) {
		BadStudent student(names[i]);
		student.SolveEq(message);
		student.SendAnswers(message);
	}
}

int main() {
	Teacher check;
	ReadFile(check);
	StudentsDoEqs(NAMES, numStudents, check);
	check.CheckWorks();
	check.PrintTable();
	return 0;
}