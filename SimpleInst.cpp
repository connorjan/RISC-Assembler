#include "SimpleInst.h"

Simple::Simple(string line, int counter, string opCode) : Assembler(line), line(line), counter(counter), opCode(opCode){}

Simple::~Simple(){}

AddInst::AddInst(string line, int counter) : Simple(line, counter, "0"), line(line), opCode("0"), counter(counter){}

AddInst::~AddInst(){}

SubInst::SubInst(string line, int counter) : Simple(line, counter, "1"), line(line), opCode("1"), counter(counter){}

SubInst::~SubInst(){}

IncInst::IncInst(string line, int counter) : Simple(line, counter, "2"), line(line), opCode("2"), counter(counter){}

IncInst::~IncInst(){}

DecInst::DecInst(string line, int counter) : Simple(line, counter, "3"), line(line), opCode("3"), counter(counter){}

DecInst::~DecInst(){}

NotInst::NotInst(string line, int counter) : Simple(line, counter, "4"), line(line), opCode("4"), counter(counter){}

NotInst::~NotInst(){}

AndInst::AndInst(string line, int counter) : Simple(line, counter, "5"), line(line), opCode("5"), counter(counter){}

AndInst::~AndInst(){}

OrInst::OrInst(string line, int counter) : Simple(line, counter, "6"), line(line), opCode("6"), counter(counter){}

OrInst::~OrInst(){}

ShrInst::ShrInst(string line, int counter) : Simple(line, counter, "7"), line(line), opCode("7"), counter(counter){}

ShrInst::~ShrInst(){}

SwapInst::SwapInst(string line, int counter) : Simple(line, counter, "A"), line(line), opCode("A"), counter(counter){}

SwapInst::~SwapInst(){}

CpyInst::CpyInst(string line, int counter) : Simple(line, counter, "B"), line(line), opCode("B"), counter(counter){}

CpyInst::~CpyInst(){}

PushInst::PushInst(string line, int counter) : Simple(line, counter, "E"), line(line), opCode("E"), counter(counter){}

PushInst::~PushInst(){}

PopInst::PopInst(string line, int counter) : Simple(line, counter, "F"), line(line), opCode("F"), counter(counter){}

PopInst::~PopInst(){}
