RISC-Assembler
==============

A basic assembler for a custom set of RISC architectures.


##Installation (Mac/Linux only as of now):

1. (MAC ONLY, LINUX USERS GOTO #2) Install homebrew:

	$ ruby -e "$(curl -fsSL https://raw.github.com/Homebrew/homebrew/go/install)"

2. Install the c++ boost library (if already installed edit makefile to use correct directory) 
	and git from their repo using the installer of your choice:

	$ brew install boost git

3. Clone the project from the git repo:

	$ git clone http://github.com/connorjan/RISC-Assembler; cd RISC-Assembler

4. Verify that the makefile containts the correct path to your installation of boost. 

5. Build the project using make:

	$ make


##Usage:

./myAssembler [--help] \<infilename-path\> [-d \<depth\>] [-h] [-v] [-o \<outfilename-path\>]


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
