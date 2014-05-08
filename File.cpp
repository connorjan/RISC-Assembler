#include "File.h"
#include "Exception.h"

using namespace std;

list<string> openFile(string fileName)
{
	ifstream inFile;

	inFile.open(fileName, ofstream::in);

	
	if (!inFile.is_open())
	{
		throw ReadError();
	}

	string line;

	list<string> lines;

	stringstream ss;

	while (!inFile.eof())
	{
		getline(inFile, line, '\n');
		ss.clear();
		ss.str("");

		ss << line;

		lines.push_back(line);
	}


	return lines;
}

void print(list<string> l)
{
	for (list<string>::iterator it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << endl;
	}
}

list<string> removeJunk(list<string> l)
{
	string copy;
	for (list<string>::iterator it = l.begin(); it != l.end(); ++it)
	{
		copy = *it;
		copy.erase (remove ((copy).begin(), (copy).end(), ' '), (copy).end());
		(copy).erase (remove ((copy).begin(), (copy).end(), '\t'), (copy).end());	
		if ((*copy.begin() == ';') || copy.empty())
		{
			l.erase(it);
		}

	}

	return l;
}

int decodeLine(string line)
{
	//detects @ and removes
	int posAt = line.find_first_of('@');
	if (posAt != -1)
	{
		int posEnd = line.find_first_of(" \t", posAt);
		//cout << posAt << " : " << posEnd << endl;
		line.erase(posAt, posEnd-posAt);
	}

	//detects address and removes
	int posAdrs = line.find_first_of('0');
	if (posAdrs != -1)
	{
		line.erase(posAdrs, 4);
	}



		line.erase (remove ((line).begin(), (line).end(), ' '), (line).end());
		(line).erase (remove ((line).begin(), (line).end(), '\t'), (line).end());
		(line).erase (remove ((line).begin(), (line).end(), ';'), (line).end());


		if (line == "ADD") {
			return 0;}
		else if (line == "SUB") {
			return 1;}
		else if (line == "INC") {
			return 2;}
		else if (line == "DEC") {
			return 3;}
		else if (line == "NOT") {
			return 4;}
		else if (line == "AND") {
			return 5;}
		else if (line == "OR") {
			return 6;}
		else if (line == "SHR") {
			return 7;}
		else if (line == "JMPU") {
			return 8;}
		else if (line == "JMPC") {
			return 9;}
		else if (line == "SWAP") {
			return 10;}
		else if (line == "CPY") {
			return 11;}
		else if (line == "WR") {
			return 12;}
		else if (line == "RD") {
			return 13;}
		else if (line == "IN") {
			return 14;}
		else if (line == "OUT") {
			return 15;}
		else if (line == "PUSH") {
			return 16;}
		else if (line == "POP") {
			return 17;}
		else 
			return -1;
		
}

string getLabel(string line)
{
	string label;

	
	return label;
}






