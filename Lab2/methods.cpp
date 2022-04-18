#include "header.hpp"

bool Solution::operator == (const Solution ans) const {
	if (this->numOfX == ans.numOfX && this->x1 == ans.x1 && this->x2 == ans.x2)
		return true;
	return false;
}

Solution QuadraticEquation::RightSolve() const {
	Solution result;
	double d = b * b - 4.0 * a * c;
	if (fabs(d) < 0.0000000001) {
		result.numOfX = 1;
		result.x1 = -b / (2.0 * a);
		result.x2 = result.x1;
		return result;
	}
	if (d < 0) {
		result.numOfX = 0;
		return result;
	}
	result.numOfX = 2;
	result.x1 = (b + sqrt(d)) / (2.0 * a);
	result.x2 = (b - sqrt(d)) / (2.0 * a);
	return result;
}

void Student::SendAnswers(Teacher& message) {
	for (int i = 0; i < roots.size(); ++i) {
		Letter letter(message.eqList.at(i), this->roots.at(i), this->fullName);
		message.letters.push(letter);
	}
}

void GoodStudent::SolveEq(Teacher& message) {
	for (int i = 0; i < message.eqList.size(); ++i)
		roots.push_back(message.eqList.at(i).RightSolve());
}

void BadStudent::SolveEq(Teacher& message) {
	for (int i = 0; i < message.eqList.size(); ++i) {
		Solution ans;
		ans.numOfX = 1;
		ans.x1 = ans.x2 = 0.0;
		roots.push_back(ans);
	}
}

void MiddleStudent::SolveEq(Teacher& message) {
	for (int i = 0; i < message.eqList.size(); ++i) {
		if (rand() % 11 <= 5)
			roots.push_back(message.eqList.at(i).RightSolve());
		else {
			Solution ans;
			ans.numOfX = 1;
			ans.x1 = ans.x2 = 0;
			roots.push_back(ans);
		}
	}
}

void Teacher::CheckWorks() {
	bool studentNameInResult = false;
	while (letters.empty() != true) {
		studentNameInResult = false;
		for (int i = 0; i < results.size(); ++i) {
			if (results.at(i).name == letters.front().name) {
				studentNameInResult = true;
				if (letters.front().solve == letters.front().qe.RightSolve())
					++results.at(i).numRightSolves;
			}
		}
		if (studentNameInResult == false) {
			Result result;
			result.name = letters.front().name;
			if (letters.front().solve == letters.front().qe.RightSolve())
				result.numRightSolves = 1;
			else
				result.numRightSolves = 0;
			results.insert(results.end(), result);
		}
		letters.pop();
	}
}

void Teacher::PrintTable() {
	for (int i = 0; i < results.size(); ++i)
		std::cout << results.at(i).name << " " << results.at(i).numRightSolves << std::endl;
}