#include "File.h"
#include "Exception.h"

using namespace std;

//Returns a list which containts a string for each line in a file
list<string> openFile(string fileName)
{
	ifstream inFile;

	inFile.open(fileName, ofstream::in);

	//Makes sure the file exists
	if (!inFile.is_open())
	{
		throw ReadError();
	}

	string line;
	list<string> lines;
	stringstream ss;

	//Pushes the line into the list
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

//Prints a list of strings
void print(list<string> l)
{
	for (list<string>::iterator it = l.begin(); it != l.end(); ++it)
	{
		cout << *it << endl;
	}
}

//Removes any lines that start with a semicolon from a list of strings ()
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

//This is where the magic happens
vector<string> decodeLine(string line)
{
	//Creates the data that is needed for the decode of each line
	vector<string> data(3);
	// data[0] = instruction opCode
	// data[1] = a definition label
	// data[2] = a jump label

	//defines strings for the label handling
	string labelBefore;
	string labelAfter;

	int posEnd = 0;

	//Looks for the first label, adds it to data, then removes it from the line
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

	//Looks for a second label, adds it to data, then removes it from the line
	posAt = line.find_first_of('@');
	if (posAt != -1)
	{
		int posEnd = line.find_first_of(" \t;", posAt);

		data[2] = line.substr(posAt, posEnd-posAt);

		line.erase(posAt, posEnd-posAt);
	}

	//Detects a hex address, adds it to data, and then removes
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

	//Removes the rest of the whitespace and semicolon from the line
	line.erase (remove ((line).begin(), (line).end(), ' '), (line).end());
	(line).erase (remove ((line).begin(), (line).end(), '\t'), (line).end());
	(line).erase (remove ((line).begin(), (line).end(), ';'), (line).end());

	//Makes the line all uppercase
	line = makeUpper(line);

	//Decodes for which instruction the line is, then returns a code for the switch in main()
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

//Checks to see if the first label that is found in a line comes before or after the instruction
bool labelIsBefore(string line)
{
	string label;

	line.erase (remove ((line).begin(), (line).end(), ' '), (line).end());
	line.erase (remove ((line).begin(), (line).end(), '\t'), (line).end());

	return (line[0]=='@');
}

//Converts a decimal to a 2-bit hex number formatted like: 0x00
string toHex(int dec)
{

  stringstream stream;
  stream << "0x" 
         << setfill ('0') << setw(2) 
         << hex << uppercase << dec;
  return stream.str();
}

//Converts a hex string to an int in decimal
int toDec(string h)
{
	int dec;
	stringstream ss;
	ss  << h;
	ss >> hex >> dec;
	return dec;
}

//Writes the header for the file taking into account the depth and width.
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

//Returns true if a string contains only digits
bool isDigits(string str)
{
    return ((str.find_first_not_of("0123456789") == -1));
}

//Removes any leading whitespace on a string
string removeLead(string line)
{
	return line.substr(line.find_first_not_of(" \t"), line.length()-line.find_first_not_of(" \t"));
}

string makeUpper(string str)
{
	transform(str.begin(), str.end(),str.begin(), ::toupper);
	return str;
}