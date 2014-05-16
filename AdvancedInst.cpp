#include "AdvancedInst.h"
#include "File.h"

Advanced::Advanced(string line, int counter, string opCode, string address) : Assembler(line), line(line), counter(counter), opCode(opCode), address(address){}

Advanced::~Advanced(){}

void Advanced::getComment()
{
	string line = this->line;

	//Removes first label from line
	int posAt = line.find_first_of('@');
	if (posAt != -1)
	{
		int posEnd = line.find_first_of(" \t;", posAt);
		line.erase(posAt, posEnd-posAt);
	}

	//Removes second label from line
	posAt = line.find_first_of('@');
	if (posAt != -1)
	{
		int posEnd = line.find_first_of(" \t;", posAt);
		line.erase(posAt, posEnd-posAt);
	}

	//Finds and erases the address
	int posZero = line.find_first_of('0');
	int posX	= line.find_first_of('X');
	int posx 	= line.find_first_of('x');

	if (((posX-posZero == 1) or (posx-posZero==1)) and ((line[posZero-1] == ' ') or (line[posZero-1] == '\t')))
	{
		line.erase(posZero, 4);
	}

	//Removes spaces, tabs, and semicolons
	line.erase (remove ((line).begin(), (line).end(), ' '), (line).end());
	(line).erase (remove ((line).begin(), (line).end(), '\t'), (line).end());
	(line).erase (remove ((line).begin(), (line).end(), ';'), (line).end());

	this->comment = line;
}

//Outputs the information to the machine code file
ostream& operator << (ostream& out, const Advanced& a)
{	
	//Checks to see if the instruction is IN or OUT
	if ((a.opCode == "E") or (a.opCode == "F"))
	{
		out << toHex(a.counter).at(2) << toHex(a.counter).at(3) << " : " << a.opCode << ";\t" << '%' << ' ' << a.comment << ' ' << '%' << endl;
		out << toHex(a.counter + 1).at(2) << toHex(a.counter + 1).at(3) << " : " << a.address[3] << ";";
		return out;
	}
	else 
	{
		out << toHex(a.counter).at(2) << toHex(a.counter).at(3) << " : " << a.opCode << ";\t" << '%' << ' ' << a.comment << ' ' << '%' << endl;
		out << toHex(a.counter + 1).at(2) << toHex(a.counter + 1).at(3) << " : " << a.address[2] << ";" << endl;
		out << toHex(a.counter + 2).at(2) << toHex(a.counter + 2).at(3) << " : " << a.address[3] << ";";
	return out;
	}
}

JMPUInst::JMPUInst(string line, int counter, string address) : Advanced(line, counter, "8", address), line(line), opCode("8"), counter(counter), address(address){}

JMPUInst::~JMPUInst(){}

JMPCInst::JMPCInst(string line, int counter, string address) : Advanced(line, counter, "9", address), line(line), opCode("9"), counter(counter), address(address){}

JMPCInst::~JMPCInst(){}

WrInst::WrInst(string line, int counter, string address) : Advanced(line, counter, "C", address), line(line), opCode("C"), counter(counter), address(address){}

WrInst::~WrInst(){}

RdInst::RdInst(string line, int counter, string address) : Advanced(line, counter, "D", address), line(line), opCode("D"), counter(counter), address(address){}

RdInst::~RdInst(){}

InInst::InInst(string line, int counter, string address) : Advanced(line, counter, "E", address), line(line), opCode("E"), counter(counter), address(address){}

InInst::~InInst(){}

OutInst::OutInst(string line, int counter, string address) : Advanced(line, counter, "F", address), line(line), opCode("F"), counter(counter), address(address){}

OutInst::~OutInst(){}