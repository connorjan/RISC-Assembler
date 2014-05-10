#include "Assembler.h"

Assembler::Assembler(string line) {}

Assembler::~Assembler(){}

void Assembler::getComment(){}

ostream& operator << (ostream& out, const Simple& s)
{	
	out << s.counter << " : " << s.opCode << ";\t" << '%' << ' ' << s.comment << ' ' << '%';
	return out;
}

void Simple::getComment()
{
	string line = this->line;

	//Removes label
	int posAt = line.find_first_of('@');
	if (posAt != -1)
	{
		int posEnd = line.find_first_of(" \t", posAt);
		line.erase(posAt, posEnd-posAt);
	}

	//Removes spaces, tabs, and semicolons
	line.erase (remove ((line).begin(), (line).end(), ' '), (line).end());
	(line).erase (remove ((line).begin(), (line).end(), '\t'), (line).end());
	(line).erase (remove ((line).begin(), (line).end(), ';'), (line).end());

	this->comment = line;
}

Advanced::Advanced(string line, int counter, string opCode) : Assembler(line), line(line), counter(counter), opCode(opCode){}

Advanced::~Advanced(){}

void Advanced::getComment()
{
	string line = this->line;

	//Removes label
	int posAt = line.find_first_of('@');
	if (posAt != -1)
	{
		int posEnd = line.find_first_of(" \t", posAt);
		line.erase(posAt, posEnd-posAt);
	}

	//Removes spaces, tabs, and semicolons
	line.erase (remove ((line).begin(), (line).end(), ' '), (line).end());
	(line).erase (remove ((line).begin(), (line).end(), '\t'), (line).end());
	(line).erase (remove ((line).begin(), (line).end(), ';'), (line).end());

	this->comment = line;
}


