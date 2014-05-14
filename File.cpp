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

list<string> removeComments(list<string> l)
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

vector<string> decodeLine(string line)
{
	vector<string> data(3);
	// data[0] = opCode
	// data[1] = before label
	// data[2] = after label or address


	string labelBefore;
	string labelAfter;

	int posEnd = 0;

	//detects @ and removes

	int posAt = line.find_first_of('@');
	if (posAt != -1)
	{
		posEnd = line.find_first_of(" \t;", posAt);

		//Checks to see if label is before or after OpCode
		if (labelIsBefore(line))
		{
			data[1] = line.substr(posAt, posEnd-posAt);
		}
		else 
		{
			data[2] = line.substr(posAt, posEnd-posAt);
		}

		line.erase(posAt, posEnd-posAt);

	}

	posAt = line.find_first_of('@');
	if (posAt != -1)
	{
		int posEnd = line.find_first_of(" \t;", posAt);

		data[2] = line.substr(posAt, posEnd-posAt);

		line.erase(posAt, posEnd-posAt);
	}

	//detects address and removes
	int posZero = line.find_first_of('0');
	int posX	= line.find_first_of('X');
	int posx 	= line.find_first_of('x');

	if (((posX-posZero == 1) or (posx-posZero==1)) and ((line[posZero-1] == ' ') or (line[posZero-1] == '\t')))
	{
		int posEnd = line.find_first_of(" \t;", posZero);

		if (posEnd-posZero != 4)
		{
			throw AddressError();
		}


		data[2] = line.substr(posZero, posEnd-posZero);

		line.erase(posZero, posEnd-posZero);
	}

	line.erase (remove ((line).begin(), (line).end(), ' '), (line).end());
	(line).erase (remove ((line).begin(), (line).end(), '\t'), (line).end());
	(line).erase (remove ((line).begin(), (line).end(), ';'), (line).end());


	boost::to_upper(line);

	if (line == "ADD") {
		data[0] = "0";}
	else if (line == "SUB") {
		data[0] = "1";}
	else if (line == "INC") {
		data[0] = "2";}
	else if (line == "DEC") {
		data[0] = "3";}
	else if (line == "NOT") {
		data[0] = "4";}
	else if (line == "AND") {
		data[0] = "5";}
	else if (line == "OR") {
		data[0] = "6";}
	else if (line == "SHR") {
		data[0] = "7";}
	else if (line == "JMPU") {
		data[0] = "8";}
	else if (line == "JMPC") {
		data[0] = "9";}
	else if (line == "SWAP") {
		data[0] = "10";}
	else if (line == "CPY") {
		data[0] = "11";}
	else if (line == "WR") {
		data[0] = "12";}
	else if (line == "RD") {
		data[0] = "13";}
	else if (line == "IN") {
		data[0] = "14";}
	else if (line == "OUT") {
		data[0] = "15";}
	else if (line == "PUSH") {
		data[0] = "16";}
	else if (line == "POP") {
		data[0] = "17";}
	else 
		data[0] = "-1";

	return data;
}

bool labelIsBefore(string line)
{
	string label;

	line.erase (remove ((line).begin(), (line).end(), ' '), (line).end());
	line.erase (remove ((line).begin(), (line).end(), '\t'), (line).end());

	return (line[0]=='@');
}


string toHex(int dec)
{

  stringstream stream;
  stream << "0x" 
         << setfill ('0') << setw(2) 
         << hex << uppercase << dec;
  return stream.str();
}

int toDec(string h)
{
	int dec;
	stringstream ss;
	ss  << h;
	ss >> hex >> dec;
	return dec;
}

string writeHeader(string fileName, string width, string depth)
{
	stringstream stream;

	stream 	<< "-- Assembled from " << fileName << endl
			<< "-- Created with RISC Assembler by Connor Goldberg and Matthew Zachary" << endl
			<< endl
			<< "WIDTH = " << width << ";" << endl
			<< "DEPTH = " << depth << ";" << endl
			<< "ADDRESS_RADIX = HEX;" << endl
			<< "DATA_RADIX = HEX;" << endl
			<< endl
			<< "CONTENT BEGIN" << endl;

	return stream.str();
}

bool isDigits(string str)
{
    return ((str.find_first_not_of("0123456789") == -1));
}

string removeLead(string line)
{
	return line.substr(line.find_first_not_of(" \t"), line.length()-line.find_first_not_of(" \t"));
}