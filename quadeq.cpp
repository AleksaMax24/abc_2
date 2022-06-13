#include "quadeq.hpp"



Coeffs::Coeffs(int count)
{
	countOfCoeffs = count;     
	coeff = new double[count]; 
}

void processString(string& str) // функция обработки строки
								// превращает строку -1.525*x^2-9.135*x-4.123=0
								// в строку -1.525 -9.135 -4.123
{
	int charCounter = 0;
	while (str[charCounter] != '=')
	{
		if (str[charCounter] != '-' && str[charCounter] != '.' && !(str[charCounter] >= '0' && str[charCounter] <= '9'))
		{
			if (str[charCounter] == '^')
			{
				str[charCounter] = ' ';
				charCounter++;
			}
			str[charCounter] = ' ';
		}
		charCounter++;
	}
	str[charCounter] = ' ';
	str[charCounter + 1] = ' ';
}

void Coeffs::parseCoeffs(ifstream& filestream) 
											   
{
	string str;
	filestream >> str; 
	processString(str);
	stringstream stream(str);

	stream >> coeff[A] >> coeff[B] >> coeff[C];
}

void Coeffs::parseCoeffs(string equality)
{
	processString(equality);
	stringstream stream(equality);

	stream >> coeff[A] >> coeff[B] >> coeff[C];
}

QuadEq::QuadEq() 
{
	abc = new Coeffs(quadEq); 
	discriminant = abc->coeff[B] * abc->coeff[B] - 4 * abc->coeff[A] * abc->coeff[C]; 
}

void QuadEq::setQuadEq(ifstream& filestream) 
{
	abc->parseCoeffs(filestream);
	discriminant = abc->coeff[B] * abc->coeff[B] - 4 * abc->coeff[A] * abc->coeff[C]; 
}

void QuadEq::setQuadEq(string equality) 
{
	abc->parseCoeffs(equality);
	discriminant = abc->coeff[B] * abc->coeff[B] - 4 * abc->coeff[A] * abc->coeff[C];
}

string QuadEq::getQuadEq()  
{
	ostringstream streamIntoString;

	if (abc->coeff[A] != 0)
		streamIntoString << abc->coeff[A] << "x^2";

	if (abc->coeff[B] < 0)
		streamIntoString << "-" << fabs(abc->coeff[B]) << "x";
	else if (abc->coeff[B] > 0)
		streamIntoString << "+" << abc->coeff[B] << "x";

	if (abc->coeff[C] < 0)
		streamIntoString << "-" << fabs(abc->coeff[C]);
	else if (abc->coeff[C] > 0)
		streamIntoString << "+" << abc->coeff[C];

	streamIntoString << "=0";

	return streamIntoString.str();
}

caseSols QuadEq::checkDiscriminant() 
{
	if (discriminant < 0)
		return caseSols::complexSols;
	else
		return discriminant > 0 ? caseSols::twoSols : caseSols::oneSol;
}

void QuadEq::solveQuadEq() 
{
	auto caseDis = checkDiscriminant(); 

	if (caseDis == caseSols::oneSol) 
	{
		solution = new double(-abc->coeff[B] / (2 * abc->coeff[A]));
	}
	else if (caseDis == caseSols::twoSols)
	{
		solution = new double[static_cast<int>(caseSols::twoSols)];
		solution[0] = (-abc->coeff[B] + sqrt(discriminant)) / (2 * abc->coeff[A]);
		solution[1] = (-abc->coeff[B] - sqrt(discriminant)) / (2 * abc->coeff[A]);
	}
	else if (caseDis == caseSols::complexSols)
	{
		double x00 = 0, x01 = 0, x02 = 0;
		x00 = -abc->coeff[B] / 2 * abc->coeff[A];
		x01 = std::sqrt(-discriminant) / (2 * abc->coeff[A]);
		x02 = -std::sqrt(-discriminant) / (2 * abc->coeff[A]);

		if (x01 < 0 && x02 < 0)
		{
			x01 = abs(x01);
			x02 = abs(x02);
			sol[0] = { x00, -x01 };
			sol[1] = { x00, -x02 };
		}
		else if (x01 > 0 && x02 < 0)
		{
			x02 = abs(x02);
			sol[0] = { x00, x01 };
			sol[1] = { x00, -x02 };
		}
		else if (x01 < 0 && x02 > 0)
		{
			x01 = abs(x01);
			sol[0] = { x00, -x01 };
			sol[1] = { x00, x02 };
		}
		else if (x01 > 0 && x02 > 0)
		{
			sol[0] = { x00, x01 };
			sol[1] = { x00, x02 };
		}


	}
}

string QuadEq::getQuadEqSol() { 
	ostringstream streamIntoString;
	if (checkDiscriminant() == caseSols::zeroSols)
	{
		streamIntoString << "No Solutions";
	}
	else if (checkDiscriminant() == caseSols::oneSol)
	{
		streamIntoString << "x = " << solution[0];
	}
	else if (checkDiscriminant() == caseSols::twoSols)
	{
		streamIntoString << "x1 = " << solution[0] << endl << "x2 = " << solution[1];
	}
	else if (checkDiscriminant() == caseSols::complexSols) {
		streamIntoString << "x1 = " << sol[0] << ' ' << "x2 = " << sol[1] << endl;
	}
	return streamIntoString.str();
}
