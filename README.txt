RISC Assembler by Connor Goldberg and Matthew Zachary
-----------------------------------------------------

Installation (Mac/Linux only as of now):
---------------------------------------

	Prerequisites: git, make

	1. Clone the project from the git repo:
		
		$ git clone http://github.com/connorjan/RISC-Assembler; cd RISC-Assembler

	2. Build the project using make:

		$ make


Usage:
-----

	./myAssembler [--help] <input-filename-path> [-d <depth>] [-h] [-v] [-o <name>]

	
	1. --help

		Add this flag to view the help menu

	2. <filename-path>   --REQUIRED

		Input assembly code file to be processed

	3. -d <depth>

		Add this flag followed by the depth to specify how many locations exist in memory
		Default: 256

	4. -h

		Add this flag to indicate a Harvard Memory Architecture

	5. -v 

		Add this flag to indicate a Von Neumann Memory Architecture (this is the default)

	6. -o <name>

		Add this flag to specify the output machine code file name
		Default: <filename-path>.mif

By Connor Goldberg and Matt Zachary.

