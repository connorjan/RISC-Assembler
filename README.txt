RISC Assembler by Connor Goldberg and Matthew Zachary
-----------------------------------------------------

Installation (mac/linux only as of now):
---------------------------------------

	1. (MAC ONLY, LINUX USERS GOTO #2) Install homebrew:
		
		$ ruby -e "$(curl -fsSL https://raw.github.com/Homebrew/homebrew/go/install)"

	2. Install the c++ boost library and git from their repo using the installer of your choice:
		
		$ brew install boost git

	3. Clone the project from the git repo:
		
		$ git clone http://github.com/connorjan/RISC-Assembler; cd RISC-Assembler

	4. Build the project using make:

		$ make


Usage:
-----

	./myAssembler [--help] <filename-path> [-d <depth>] [-h] [-v] [-o <name>]

	
	1. --help

		Add this flag to view the help menu

	2. <filename-path>   --REQUIRED

		Input assembly code file to be processed

	3. -d <depth>

		Add this flag followed by the depth to specify how many locations exist in memory
		Default: 256

	4. -h

		Add this flag to indicate a Harvard Memory Architecture
		Default: -v

	5. -v 

		Add this flag to indicate a Von Neumann Memory Architecture
		Default: -v

	6. -o <name>

		Add this flag to specify the output machine code file name
		Default: MachineCode.mif



