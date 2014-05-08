#ifndef __FILE_H
#define __FILE_H

#include "Assembler.h"

list<string> openFile(string);

void print(list<string>);

list<string> removeJunk(list<string>);

int decodeLine(string line);

#endif