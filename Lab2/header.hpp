#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <queue>

struct Solution {
	double x1;
	double x2;
	int numOfX;
	bool operator == (const Solution ans) const;
};

class QuadraticEquation;
class Letter;
struct Result;
class Teacher;
class Student;
class GoodStudent;
class BadStudent;

class QuadraticEquation {
public:
	double a;
	double b;
	double c;
	Solution RightSolve() const;
};

class Letter {
public:
	Letter(const QuadraticEquation qe, const Solution solve, const std::string name) : name(name), qe(qe), solve(solve) {};
	QuadraticEquation qe;
	Solution solve;
	std::string name;
};

class Teacher {
public:
	void CheckWorks();
	void PrintTable();
	std::queue <Letter> letters;
	std::vector <Result> results;
	std::vector <QuadraticEquation> eqList;
};

class Student {
public:
	Student(std::string fullName) : fullName(fullName) {}
	std::string fullName;
	std::vector <Solution> roots;
	void SendAnswers(Teacher& message);
};

class GoodStudent : public Student {
public:
	GoodStudent(std::string fullname) : Student(fullname) {};
	void SolveEq(Teacher& message);
};

class BadStudent : public Student {
public:
	BadStudent(std::string fullname) : Student(fullname) {};
	void SolveEq(Teacher& message);
};

class MiddleStudent : public Student {
public:
	MiddleStudent(std::string fullname) : Student(fullname) {};
	void SolveEq(Teacher& message);
}; 

struct Result {
	std::string name;
	int numRightSolves;
};
