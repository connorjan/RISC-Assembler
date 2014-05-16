#ifndef __ADVANCEDINST_H
#define __ADVANCEDINST_H

#include "Assembler.h"

using namespace std;

class JMPUInst : public Advanced
{

public:
	JMPUInst(string, int, string);
	~JMPUInst();

private:
	string line;
	int counter;
	string opCode;
	string address;

};

class JMPCInst : public Advanced
{

public:
	JMPCInst(string, int, string);
	~JMPCInst();

private:
	string line;
	int counter;
	string opCode;
	string address;

};

class WrInst : public Advanced
{

public:
	WrInst(string, int, string);
	~WrInst();

private:
	string line;
	int counter;
	string opCode;
	string address;

};

class RdInst : public Advanced
{

public:
	RdInst(string, int, string);
	~RdInst();

private:
	string line;
	int counter;
	string opCode;
	string address;

};

class InInst : public Advanced
{

public:
	InInst(string, int, string);
	~InInst();

private:
	string line;
	int counter;
	string opCode;
	string address;

};

class OutInst : public Advanced
{

public:
	OutInst(string, int, string);
	~OutInst();

private:
	string line;
	int counter;
	string opCode;
	string address;

};

#endif