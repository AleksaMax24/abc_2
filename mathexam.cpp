#include "quadeq.hpp"
#include "examquadeq.hpp"

vector <Student*> readStudents(const char* studentlistname) 
{
	vector <Student*> studGroup;
	Student* studInit;

	string studname;
	int studRng;

	ifstream studBook(studentlistname);

	while (!studBook.eof())  
	{
		studBook >> studname; 
		studRng = rand() % 3 + 1; 
		if (studRng == studGood) 
		{
			studInit = new TheGood(studname);
		}
		else if (studRng == studBad) 
		{
			studInit = new TheBad(studname);
		}
		else  
		{
			studInit = new TheUgly(studname);
		}
		studGroup.push_back(studInit); 
	}

	studBook.close();

	return studGroup;
}

int main() {
	Teacher SenSei;

	vector <Student*> studGroup = readStudents("studentlist.txt"); 

	stack <Letter> LetterStack;
	SenSei.StartExam("taskbook.txt", studGroup, LetterStack); 

	map <string, int> ReportMap;
	SenSei.createReport(LetterStack, ReportMap); 

	SenSei.printReport(ReportMap); 
	SenSei.printReport("report.txt", ReportMap); 
}