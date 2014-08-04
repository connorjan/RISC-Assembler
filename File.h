#ifndef __FILE_H
#define __FILE_H

#include "Assembler.h"

list<string> openFile(string);

void print(list<string>);

list<string> removeComments(list<string>);

vector<string> decodeLine(string);

bool labelIsBefore(string);

string toHex(int);

string writeHeader(string, string, string);

bool isDigits(string);

int toDec(string);

string removeLead(string);

string makeUpper(string);

#endif