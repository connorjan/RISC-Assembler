#include "SimpleInst.h"
#include "AdvancedInst.h"
#include "File.h"
#include "Exception.h"

using namespace std;

int main(int argc, char* argv[])
{
	//cout << argc << endl; //Number of Params
	//cout << argv[0] << endl; //Path to executable
	//cout << argv[1] << endl; //Any subsequent params

	if (argc < 2)
	{
		cout << "usage: ./myAssembler [--help] <filename-path> [-d <depth>]" << endl;
		return -1;
	}

	string inFileName = argv[1];

	string temp;
	string temp2;
	string width = "1";
	string depth = "256";
	string mode;

	//Make it so user can do ./myAssembler --help without error about no input file!

	for (int i = 2; i < argc-1; i++)
	{
		temp = argv[i];
		temp2 = argv[i+1];

		if (temp == "--help")
		{
			cout 	<< "usage: ./myAssembler [--help] <filename-path> [-d <depth>]" << endl 
					<< endl
					<< "Options:" << endl
					<< "--help\t\tDisplay available options" << endl
					<< "-d <value>\t\tSet the depth of the .mif file" << endl
					<< "-h\t\tSet the architecture mode to Harvard" << endl
					<< "-o\t\tSpecify the output file name" << endl
					<< "-v\t\tSet the architecture mode to Von Neumann" << endl;
		}

		else if ((temp == "-d"))
		{
			depth = temp2;

			//Make sure temp2 is a number!
			i++;
		}

		else if (temp == "-h")
		{
			mode = "h";
		}

		else if (temp == "-v")
		{
			mode = "v";
		}

		else
		{
			cout << "Unknown option: " << argv[i] << endl;
			cout << "usage: ./myAssembler [--help] <filename-path> [-d <depth>]" << endl;
			return -1;
		}
	}



	list<string> lines;
	try
	{
		lines = openFile(inFileName);
	}
	catch(exception & ReadError)
	{
		cout << "myAssembler: error: no such file or directory: '" << inFileName << "'" << endl;
		cout << "myAssembler: error: no input files" << endl;
		return -1;
	}

	lines = removeComments(lines);

	int counter = 0;
	string address;

	ofstream myfile;
	myfile.open ("mc.mif");

	Assembler *myInst;
	vector<string> data(3);

	map<string,string> labels;

	list<string>::iterator it;

	myfile << writeHeader(inFileName, width, depth);

	//Decodes for labels
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


	//Print map for verification

/*	map<string, string>::iterator pos;
    for(pos = labels.begin(); pos != labels.end(); ++pos)
    {
         cout << "Key: " << pos->first << endl;
         cout << "Value: " << pos->second << endl;
    }*/

	//Decodes and outputs to mif 
	counter = 0;

	for (it = lines.begin(); it != lines.end(); ++it)
	{
		address = "";
		data = decodeLine(*it);

		int opCode = stoi(data[0]);
		
		switch (opCode)
		{
			case 0:

				if (data[2] != "")
				{
					cout << "error!" << endl;
					break;
				}

				myInst = new AddInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 1:

				if (data[2] != "")
				{
					cout << "error!" << endl;
					break;
				}

				myInst = new SubInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 2:

				if (data[2] != "")
				{
					cout << "error!" << endl;
					break;
				}
				
				myInst = new IncInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 3:

				if (data[2] != "")
				{
					cout << "error!" << endl;
					break;
				}
				
				myInst = new DecInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;
				
			case 4:

				if (data[2] != "")
				{
					cout << "error!" << endl;
					break;
				}
				
				myInst = new NotInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 5:

				if (data[2] != "")
				{
					cout << "error!" << endl;
					break;
				}
				
				myInst = new AndInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 6:

				if (data[2] != "")
				{
					cout << "error!" << endl;
					break;
				}
				
				myInst = new OrInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;
				
			case 7:

				if (data[2] != "")
				{
					cout << "error!" << endl;
					break;
				}
				
				myInst = new ShrInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 8:

				if (data[2] == "")
				{
					cout << "No argument" << endl;
				}

				if (data[2].at(0) == '@')
				{
					if (labels[data[2]] == "")
					{
						cout << "label not defined: " << data[2] << endl;
					}
					address = labels[data[2]];
				}
				else if (data[2].at(0) == '0')
				{
					address = data[2];
				}
				else
				{
					cout << "Invalid Instruction on line: " << counter << endl;
					delete myInst;
					break;
				}

				boost::to_upper(address);

				myInst = new JMPUInst(*it,counter, address);

				((Advanced*)myInst)->getComment();

				myfile << endl << *((Advanced*)myInst);

				counter = counter + 2;

				delete myInst;
				break;

			case 9:

				if (data[2] == "")
				{
					cout << "no argument" << endl;
				}

				if (data[2].at(0) == '@')
				{
					if (labels[data[2]] == "")
					{
						cout << "label not defined: " << data[2] << endl;
					}
					address = labels[data[2]];
				}
				else if (data[2].at(0) == '0')
				{
					address = data[2];
				}
				else
				{
					cout << "Invalid Instruction on line: " << counter << endl;
					delete myInst;
					break;
				}

				boost::to_upper(address);

				myInst = new JMPCInst(*it,counter, address);

				((Advanced*)myInst)->getComment();

				myfile << endl << *((Advanced*)myInst);

				counter = counter + 2;

				delete myInst;
				break;
				
			case 10:

				if (data[2] != "")
				{
					cout << "error!" << endl;
					break;
				}
				
				myInst = new SwapInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 11:

				if (data[2] != "")
				{
					cout << "error!" << endl;
					break;
				}
				
				myInst = new CpyInst(*it, counter);
			
				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 12:

				if (data[2] == "")
				{
					cout << "No argument" << endl;
				}

				if (data[2].at(0) == '@')
				{
					cout << "Can't wr to label" << endl;
					break;
				}
				else if (data[2].at(0) == '0')
				{
					address = data[2];
				}
				else
				{
					cout << "Invalid Instruction on line: " << counter << endl;
					delete myInst;
					break;
				}

				boost::to_upper(address);

				myInst = new WrInst(*it,counter, address);

				((Advanced*)myInst)->getComment();

				myfile << endl << *((Advanced*)myInst);

				counter = counter + 2;

				delete myInst;
				break;
				
			case 13:

				if (data[2] == "")
				{
					cout << "No argument" << endl;
				}

				if (data[2].at(0) == '@')
				{
					cout << "Cant rd from label!" << endl;
					break;
				}
				else if (data[2].at(0) == '0')
				{
					address = data[2];
				}
				else
				{
					cout << "Invalid Instruction on line: " << counter << endl;
					delete myInst;
					break;
				}

				boost::to_upper(address);

				myInst = new RdInst(*it,counter, address);

				((Advanced*)myInst)->getComment();

				myfile << endl << *((Advanced*)myInst);

				counter = counter + 2;

				delete myInst;
				break;

			case 14:

				if (data[2] == "")
				{
					cout << "No argument" << endl;
				}

				if (data[2].at(0) == '@')
				{
					cout << "cant in from label!" << endl;
					break;
				}
				else if (data[2].at(0) == '0')
				{
					address = data[2];
				}
				else
				{
					cout << "Invalid Instruction on line: " << counter << endl;
					delete myInst;
					break;
				}

				boost::to_upper(address);

				myInst = new InInst(*it,counter, address);

				((Advanced*)myInst)->getComment();

				myfile << endl << *((Advanced*)myInst);

				counter = counter + 1;

				delete myInst;
				break;

			case 15:

				if (data[2] == "")
				{
					cout << "No argument" << endl;
				}

				if (data[2].at(0) == '@')
				{
					cout << "cant out from label!" << endl;
					break;
				}
				else if (data[2].at(0) == '0')
				{
					address = data[2];
				}
				else
				{
					cout << "Invalid Instruction on line: " << counter << endl;
					delete myInst;
					break;
				}

				boost::to_upper(address);

				myInst = new OutInst(*it,counter, address);

				((Advanced*)myInst)->getComment();

				myfile << endl << *((Advanced*)myInst);

				counter = counter + 1;

				delete myInst;
				break;
				
			case 16:

				if (data[2] != "")
				{
					cout << "error!" << endl;
					break;
				}
				
				myInst = new PushInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 17:

				if (data[2] != "")
				{
					cout << "error!" << endl;
					break;
				}
				
				myInst = new PopInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			default:
				cout << "Invalid Instruction on line: " << *it << endl;
		}

		counter ++;
	}

	myfile << "\n\nEND;" ;
	myfile.close();

	return 0;
}