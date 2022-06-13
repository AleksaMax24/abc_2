#include "quadeq.hpp"
#include "examquadeq.hpp"

string Letter::getQuadEq() { return quadEq; }     
string Letter::getSolution() { return solution; }
string Letter::getName() { return name; }


void Letter::setLetter(string equality, string sol, string studname)
{
	quadEq = equality;
	solution = sol;
	name = studname;
}

void Letter::printLetter() 
{
	cout << quadEq << endl << solution << endl << name << endl << endl;
}

Student::Student(string studname) { name = studname; } 

string Student::getName() { return name; } 

Letter TheGood::solveEq(QuadEq equality)
{
	equality.solveQuadEq(); 

	Letter letterToTeacher;
	letterToTeacher.setLetter(equality.getQuadEq(), equality.getQuadEqSol(), getName());

	return letterToTeacher;
}

Letter TheBad::solveEq(QuadEq equality) 
{
	ostringstream solIntoString;
	solIntoString << "x = " << 0 << endl; 

	Letter letterToTeacher;
	letterToTeacher.setLetter(equality.getQuadEq(), solIntoString.str(), getName()); 

	return letterToTeacher;
}

Letter TheUgly::solveEq(QuadEq equality)
{
	int uglyRng = rand() % 2; 
	if (uglyRng == studGood)
	{
		return TheGood::solveEq(equality);
	}
	else
	{
		return TheBad::solveEq(equality);
	}
}

void Teacher::StartExam(const char* tasks, vector <Student*> studGroup, stack <Letter>& LetterStack)
{
	ifstream taskbook(tasks); 
	QuadEq equalityExam;

	while (!taskbook.eof()) 
	{
		equalityExam.setQuadEq(taskbook); 
		int counterStudents = 0;

		for (vector <Student*> ::iterator it = studGroup.begin(); it < studGroup.end(); it++) 
		{
			LetterStack.push(studGroup.at(counterStudents)->solveEq(equalityExam));
			counterStudents++;
		}
	}
}

void Teacher::checkLetter(Letter studLetter, map <string, int>& ReportMap) 
{
	QuadEq checkSolution;

	checkSolution.setQuadEq(studLetter.getQuadEq());  
	checkSolution.solveQuadEq();

	string solute = checkSolution.getQuadEqSol();
	map <string, int> ::iterator it;
	it = ReportMap.find(studLetter.getName()); 

	if (it == ReportMap.end()) 
	{
		ReportMap.insert(make_pair(studLetter.getName(), 0)); 
		it = ReportMap.find(studLetter.getName()); 
		if (solute == studLetter.getSolution()) 
			it->second = it->second + 1; 
	}
	else 
		if (solute == studLetter.getSolution()) 
			it->second = it->second + 1; 
}

void Teacher::createReport(stack <Letter> LetterStack, map <string, int>& ReportMap) 
{
	while (!LetterStack.empty()) 
	{
		checkLetter(LetterStack.top(), ReportMap); 
		LetterStack.pop();
	}
}

void Teacher::printReport(map <string, int> ReportMap) 
{
	map <string, int> ::iterator it = ReportMap.begin();
	for (; it != ReportMap.end(); it++)
	{
		cout << it->first << " " << it->second << endl; 
	}

}

void Teacher::printReport(const char* filenameReport, map <string, int> ReportMap) 
{
	ofstream outReport(filenameReport);
	map <string, int> ::iterator it = ReportMap.begin();
	for (; it != ReportMap.end(); it++)
	{
		outReport << it->first << " " << it->second << endl;
	}
	outReport.close();
}