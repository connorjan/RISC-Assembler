RISC-Assembler
==============

A basic assembler for a custom set of RISC architectures.


##Installation (Mac/Linux only as of now):

	Prerequisites: [git](http://git-scm.com/book/en/Getting-Started-Installing-Git), [make](https://developer.apple.com/downloads/index.action?name=command%20line%20tools)

	1. Clone the project from the git repo:
		
		$ git clone http://github.com/connorjan/RISC-Assembler; cd RISC-Assembler

	2. Build the project using make:

		$ make


##Usage:

./myAssembler [--help] \<input-filename-path\> [-d \<depth\>] [-h] [-v] [-o \<outfilename-path\>]


1. --help

	Add this flag to view the help menu

2. \<filename-path\>   --REQUIRED

	Input assembly code file to be processed

3. -d \<depth\>

	Add this flag followed by the depth to specify how many locations exist in memory
	Default: 256

4. -h

	Add this flag to indicate a Harvard Memory Architecture
	Default: -v

5. -v 

	Add this flag to indicate a Von Neumann Memory Architecture
	Default: -v

6. -o \<name\>

	Add this flag to specify the output machine code file name
	Default: \<infilename-path\>.mif



By [Connor Goldberg](http://www.connorgoldberg.com "Connor's Website")  and [Matt Zachary](mailto:matt@grsbd.com "Matt's Email")
