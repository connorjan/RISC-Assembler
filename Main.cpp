#include "SimpleInst.h"
#include "AdvancedInst.h"
#include "File.h"
#include "Exception.h"

using namespace std;

//main
int main(int argc, char* argv[])
{

	string usage = "usage: ./myAssembler [--help] <filename> [-d <depth>] [-h] [-v] [-o <filename>]";

	if (argc < 2)
	{
		cout << usage << endl;
		return -1;
	}

	//initialization of strings taken from the user from the command line
	string inFileName = argv[1];
	string outFileName;
	string temp;
	string temp2;
	string width = "4";
	string depth = "256";
	string mode = "";

	//Sets the default output name to the input filename.mif
	outFileName = (inFileName.substr(0, inFileName.find_first_of(".")));
	outFileName.append(".mif");

	//displays help info
	if (inFileName == "--help")
	{
		cout 		<< usage << endl 
					<< endl
					<< "Options:" << endl
					<< "--help\t\tDisplay available options" << endl
					<< "-d <value>\tSet the depth of the .mif file. Default = 256" << endl
					<< "-h\t\tSet the architecture mode to Harvard" << endl
					<< "-o <name>\tSpecify the output file name" << endl
					<< "-v\t\tSet the architecture mode to Von Neumann. This is the default." << endl;
		return -1;
	}

	//loops through user input flags starting after the filename
	for (int i = 2; i < argc; i++)
	{
		temp = argv[i];

		if (temp == "-d")
		{
			//Checks to see if there is an argument after the -d
			if ((i+1) >= argc)
			{
				cout << "error: missing argument for -d" << endl;
				return -1;
			}

			temp2 = argv[i+1];

			//Checks to see if the argument for -d is purely numbers
			if (!isDigits(temp2))
			{
				cout << "error: invalid argument for -d: '" << temp2 << "'" << endl;
				return -1;
			}

			depth = temp2;
		
			i++;
		}

		else if (temp == "-o")
		{
			//Checks to see if there is a argument after the -o
			if ((i+1) >= argc)
			{
				cout << "error: missing argument for -o" << endl;
				return -1;
			}

			outFileName = argv[i+1];

			//If filename does not contain .mif, this adds it in.
			//Not sure if a program should do this for the user
			/*if (outFileName.compare(outFileName.size()-4,4,".mif") != 0)
			{
				outFileName.insert(outFileName.size(),".mif");
			}*/
		
			i++;
		}

		else if (temp == "-h")
		{
			//make sure there are not two -h or -v flags
			if (mode != "")
			{
				cout << "error: cannot more than one instance of [-h] or [-v]" << endl;
				return -1;
			}

			mode = "h";
		}

		else if (temp == "-v")
		{
			//make sure there are not two -h or -v flags
			if (mode != "")
			{
				cout << "error: cannot more than one instance of [-h] or [-v]" << endl;
				return -1;
			}
			mode = "v";
		}

		else
		{
			cout << "error: unknown option: " << argv[i] << endl;
			cout << usage << endl;
			return -1;
		}
	}

	list<string> lines;

	//adds every line of the input file to a list of strings
	try
	{
		lines = openFile(inFileName);
	}
	catch(exception & ReadError)
	{
		cout << "error: no such file or directory: '" << inFileName << "'" << endl;
		cout << "error: no input files" << endl;
		return -1;
	}

	//removes all comment lines from input file list
	lines = removeComments(lines);

	//counter that keeps track of machine code line
	int counter = 0;

	//Opens a file to write the machine code to, and then writes the header needed for the machine code.
	ofstream myfile;
	myfile.open (outFileName);
	myfile << writeHeader(inFileName, width, depth);

	//instantiates variables for use in the decoding of each instruction
	string address;
	vector<string> data(3);
	map<string,string> labels;
	list<string>::iterator it;
	int totalLines;
	string noLead;

	//Makes a pointer to the base class, Assembler!
	Assembler *myInst;

	//Try block for catching all errors in the assembly code
	try
	{
		//Goes through the assembly code.
		//First pass which adds all labels to a map with their value
		for (it = lines.begin(); it != lines.end(); ++it)
		{
			data = decodeLine(*it);
			int opCode = stoi(data[0]);

			if (data[1] != "")
			{
				labels[data[1]] = toHex(counter);
			}

			//Handles the counter
			if ((opCode == 8) or (opCode == 9) or (opCode == 12) or (opCode == 13))
			{
				counter = counter+2;
			}
			else if ((opCode == 14) or (opCode == 15))
			{
				counter++;
			}

			counter++;
		}

		//Sets the total number of lines used in Von Neumann mode
		totalLines = counter;

		if (totalLines > stoi(depth))
		{
			throw DepthError();
		}

		//Resets counter for second pass
		counter = 0;

		//Second pass of assembly. This is where the instructions are written to the file.
		for (it = lines.begin(); it != lines.end(); ++it)
		{
			address = "";
			//Sets a vector of strings equal to the results from decode line.
			//This is where the magic happens.
			data = decodeLine(*it);

			//Converts the string opcode to a int for the switch
			int opCode = stoi(data[0]);

			//Switches between which instruction is found
			switch (opCode)
			{
				//ADD Instruction (case 0-7,10,11,16,17 follow the same form)
				case 0:

					//Makes sure there is no parameter after ADD
					if (data[2] != "")
					{
						throw ParamError();
					}

					//Points the Assembler pointer to an instance of AddInst
					myInst = new AddInst(*it,counter);

					//Downcasts the pointer to assembler to its derived class Simple
					//This then sets the member variable to the original instruction
					//from the assembly code
					((Simple*)myInst)->getComment();

					//Uses the operator overload to write the information from the class to
					//the machine code file
					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;

				//Sub
				case 1:

					if (data[2] != "")
					{
						throw ParamError();
					}

					myInst = new SubInst(*it,counter);

					((Simple*)myInst)->getComment();

					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;

				//Inc
				case 2:

					if (data[2] != "")
					{
						throw ParamError();
					}
					
					myInst = new IncInst(*it,counter);

					((Simple*)myInst)->getComment();

					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;

				//Dec
				case 3:

					if (data[2] != "")
					{
						throw ParamError();
					}
					
					myInst = new DecInst(*it,counter);

					((Simple*)myInst)->getComment();

					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;
					
				//Not
				case 4:

					if (data[2] != "")
					{
						throw ParamError();
					}
					
					myInst = new NotInst(*it,counter);

					((Simple*)myInst)->getComment();

					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;

				//And
				case 5:

					if (data[2] != "")
					{
						throw ParamError();
						break;
					}
					
					myInst = new AndInst(*it,counter);

					((Simple*)myInst)->getComment();

					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;

				//Or
				case 6:

					if (data[2] != "")
					{
						throw ParamError();
					}
					
					myInst = new OrInst(*it,counter);

					((Simple*)myInst)->getComment();

					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;
				
				//Shift Right
				case 7:

					if (data[2] != "")
					{
						throw ParamError();
					}
					
					myInst = new ShrInst(*it,counter);

					((Simple*)myInst)->getComment();

					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;

				//Case 8 and 9 are the jump instructions
				//Jump Unconditionally
				case 8:

					//Makes sure there is a parameter to jump to
					if (data[2] == "")
					{
						throw ParamError();
					}

					//Checks to see if the parameter is a label
					if (data[2].at(0) == '@')
					{
						//Checks to see if the label is defined
						if (labels[data[2]] == "")
						{
							throw UndefLabel();
						}

						//Gets the value from the map using the label as a key
						address = labels[data[2]];
					}

					//Checks to see if the parameter is a hex address
					else if (data[2].at(0) == '0')
					{
						address = data[2];
					}
					else
					{
						throw InstError();
					}

					//makes the address uppercase
					boost::to_upper(address);

					//CHecks to make sure the jump address does not exceed the program length
					if (toDec(address) > totalLines)
					{
						throw JmpError();
					}


					myInst = new JMPUInst(*it,counter, address);

					((Advanced*)myInst)->getComment();

					myfile << endl << *((Advanced*)myInst);

					//upcounter the counter 2 times because jump takes 3 lines of machine code
					counter = counter + 2;

					delete myInst;
					break;

				//Jump conditionally
				case 9:

					if (data[2] == "")
					{
						throw ParamError();
					}

					if (data[2].at(0) == '@')
					{
						if (labels[data[2]] == "")
						{
							throw UndefLabel();
						}
						address = labels[data[2]];
					}
					else if (data[2].at(0) == '0')
					{
						address = data[2];
					}
					else
					{
						throw InstError();
					}

					boost::to_upper(address);

					if (toDec(address) > totalLines)
					{
						throw JmpError();
					}

					myInst = new JMPCInst(*it,counter, address);

					((Advanced*)myInst)->getComment();

					myfile << endl << *((Advanced*)myInst);

					counter = counter + 2;

					delete myInst;
					break;
					
				//Swap
				case 10:

					if (data[2] != "")
					{
						throw ParamError();
					}
					
					myInst = new SwapInst(*it,counter);

					((Simple*)myInst)->getComment();

					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;

				//Copy
				case 11:

					if (data[2] != "")
					{
						throw ParamError();
					}
					
					myInst = new CpyInst(*it, counter);
				
					((Simple*)myInst)->getComment();

					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;

				//Write instruction 
				case 12:

					//checks to make sure there is a parameter
					if (data[2] == "")
					{
						throw ParamError();
					}

					//makes sure the parameter is not a label
					if (data[2].at(0) == '@')
					{
						throw ParamError();
					}

					//makes sure the address is formatted correctly
					else if (data[2].at(0) == '0')
					{
						address = data[2];
					}
					else
					{
						throw InstError();
					}

					boost::to_upper(address);

					//Checks to see if it is in Von Neumann mode so the user
					//does not overwrite the program
					if ((mode != "h") and ((toDec(address) < totalLines)))
					{
						throw VonError();
					}

					myInst = new WrInst(*it,counter, address);

					((Advanced*)myInst)->getComment();

					myfile << endl << *((Advanced*)myInst);

					//This instruction takes three machine code lines
					counter = counter + 2;

					delete myInst;
					break;
				
				//Read instruction, follows same form as Write
				case 13:

					if (data[2] == "")
					{
						throw ParamError();
					}

					if (data[2].at(0) == '@')
					{
						throw ParamError();
					}
					else if (data[2].at(0) == '0')
					{
						address = data[2];
					}
					else
					{
						throw InstError();
					}

					boost::to_upper(address);

					if ((mode != "h") and ((toDec(address) < totalLines)))
					{
						throw VonError();
					}

					myInst = new RdInst(*it,counter, address);

					((Advanced*)myInst)->getComment();

					myfile << endl << *((Advanced*)myInst);

					counter = counter + 2;

					delete myInst;
					break;

				//In instruction
				case 14:

					if (data[2] == "")
					{
						throw ParamError();
					}

					if (data[2].at(0) == '@')
					{
						throw ParamError();
					}
					else if (data[2].at(0) == '0')
					{
						address = data[2];
					}
					else
					{
						throw InstError();
					}

					boost::to_upper(address);

					myInst = new InInst(*it,counter, address);

					((Advanced*)myInst)->getComment();

					myfile << endl << *((Advanced*)myInst);

					//This instruction takes 2 lines of machine code
					counter = counter + 1;

					delete myInst;
					break;

				//Out instruction, follows the same form as In
				case 15:

					if (data[2] == "")
					{
						throw ParamError();
					}

					if (data[2].at(0) == '@')
					{
						throw ParamError();
					}
					else if (data[2].at(0) == '0')
					{
						address = data[2];
					}
					else
					{
						throw InstError();
					}

					boost::to_upper(address);

					myInst = new OutInst(*it,counter, address);

					((Advanced*)myInst)->getComment();

					myfile << endl << *((Advanced*)myInst);

					counter = counter + 1;

					delete myInst;
					break;
				
				//Push
				case 16:

					if (data[2] != "")
					{
						throw ParamError();
					}
					
					myInst = new PushInst(*it,counter);

					((Simple*)myInst)->getComment();

					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;

				//Pop
				case 17:

					if (data[2] != "")
					{
						throw ParamError();
					}
					
					myInst = new PopInst(*it,counter);

					((Simple*)myInst)->getComment();

					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;

				default:
					throw InstError();
			}

			counter ++;
		}
	}

	//Catches the errors and goes to fail
	//removeLead() removes any leading spaces or tabs from the line
	catch (DepthError)
	{
		cout << "error: entered a depth of '" << depth << "' which is smaller than the total number of lines" << endl;
		goto fail;
	}
	catch (AddressError)
	{
		cout << "error: invalid address on line: " << removeLead(*it) << endl;
		goto fail;
	}
	catch(ParamError)
	{	
		cout << "error: invalid parameter on line: " << removeLead(*it) << endl;
		goto fail;
	}
	catch(UndefLabel)
	{
		cout << "error: undefined Label on line: " << removeLead(*it) << endl;
		goto fail;
	}
	catch(VonError)
	{	
		cout << "error: program overwrite due to address on line: " << removeLead(*it) << endl;
		goto fail;
	}
	catch(JmpError)
	{	
		cout << "error: jumping to address outside of program bounds due to address on line: " << removeLead(*it) << endl;
		goto fail;
	}
	catch(InstError)
	{	
		cout << "error: invalid instruction on line: " << removeLead(*it) << endl;
		goto fail;
	}

	//Writes the footer
	myfile << "\n\nEND;";

	//Closes out the file
	myfile.close();

	//Returns 0 if the program was successful
	return 0;


//If an error was encountered the program ends up here
fail:

	//Closes the file
	myfile.close();

	//Converts the output file name to a char* array
	const char *cstr = outFileName.c_str();

	//Deletes the machine code file
	remove(cstr);

	return -1;

}