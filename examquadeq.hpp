#pragma once
#include "quadeq.hpp"
#include <stack>
#include <vector>
#include <map>
#include <iterator>
#include <fstream>
#include <string> 
#include <iostream>


struct Letter { 
private:
	string quadEq;  
	string solution;
	string name;    
public:
	string getQuadEq();  
	string getSolution();
	string getName();

	void setLetter(string equality, string sol, string studname); 
	void printLetter(); 
};

enum studClassificator { 
	studGood = 1,
	studBad,
	studUgly
};

class Student { 
private:
	string name; 
public:
	Student() {}
	Student(string studname); 

	virtual Letter solveEq(QuadEq equality) = 0; 
	string getName(); 
};

class TheGood : virtual public Student {
public:
	TheGood() {}
	TheGood(string& studname) : Student(studname) {} 
	Letter solveEq(QuadEq equality); 
};

class TheBad : virtual public Student {  
public:
	TheBad() {}
	TheBad(string& studname) : Student(studname) {}
	Letter solveEq(QuadEq equality);
};

class TheUgly : public TheBad, public TheGood { 
public:
	TheUgly(string& studname) : Student(studname) {}
	Letter solveEq(QuadEq equality);
};

class Teacher { // класс учитель
public:

	void StartExam(const char* tasks, vector <Student*> studGroup, stack <Letter>& LetterStack); 
	void checkLetter(Letter studLetter, map <string, int>& ReportMap); 
	void createReport(stack <Letter> LetterStack, map <string, int>& ReportMap);

	void printReport(map <string, int> ReportMap); 
	void printReport(const char* filenameReport, map <string, int> ReportMap);

};
