#ifndef __SIMPLEINST_H
#define __SIMPLEINST_H

#include "Assembler.h"

using namespace std;

class AddInst : public Simple
{

public:
	AddInst(string, int);
	~AddInst();

private:
	string line;
	int counter;
	string opCode;

};

class SubInst : public Simple
{

public:
	SubInst(string, int);
	~SubInst();

private:
	string line;
	int counter;
	string opCode;

};

class IncInst : public Simple
{

public:
	IncInst(string, int);
	~IncInst();

private:
	string line;
	int counter;
	string opCode;

};

class DecInst : public Simple
{

public:
	DecInst(string, int);
	~DecInst();

private:
	string line;
	int counter;
	string opCode;

};

class NotInst : public Simple
{

public:
	NotInst(string, int);
	~NotInst();

private:
	string line;
	int counter;
	string opCode;

};

class AndInst : public Simple
{

public:
	AndInst(string, int);
	~AndInst();

private:
	string line;
	int counter;
	string opCode;

};

class OrInst : public Simple
{

public:
	OrInst(string, int);
	~OrInst();

private:
	string line;
	int counter;
	string opCode;

};

class ShrInst : public Simple
{

public:
	ShrInst(string, int);
	~ShrInst();

private:
	string line;
	int counter;
	string opCode;

};

class SwapInst : public Simple
{

public:
	SwapInst(string, int);
	~SwapInst();

private:
	string line;
	int counter;
	string opCode;

};

class CpyInst : public Simple
{

public:
	CpyInst(string, int);
	~CpyInst();

private:
	string line;
	int counter;
	string opCode;

};

class PushInst : public Simple
{

public:
	PushInst(string, int);
	~PushInst();

private:
	string line;
	int counter;
	string opCode;

};

class PopInst : public Simple
{

public:
	PopInst(string, int);
	~PopInst();

private:
	string line;
	int counter;
	string opCode;

};

#endif