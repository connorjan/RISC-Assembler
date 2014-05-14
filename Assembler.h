#ifndef __ASSEMBLER_H
#define __ASSEMBLER_H

#include <string.h>
#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctype.h>
#include <iomanip>
#include <cstdio>
#include <boost/algorithm/string/case_conv.hpp>

using namespace std;

class Assembler
{

public:
	Assembler(string);
	virtual ~Assembler();
	virtual void getComment();
private:
	string line;

};


class Simple : public Assembler
{

public:
	Simple(string, int, string);
	~Simple();
	void getComment();
	friend ostream& operator << (ostream&, const Simple&);

private:
	string line;
	int counter;
	string opCode;
	string comment;

};

class Advanced : public Assembler
{

public:
	Advanced(string, int, string, string);
	~Advanced();
	void getComment();
	friend ostream& operator << (ostream&, const Advanced&);

private:
	string line;
	int counter;
	string opCode;
	string comment;
	string address;

};

#endif