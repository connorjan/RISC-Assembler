#include "SimpleInst.h"
#include "AdvancedInst.h"
#include "File.h"
#include "Exception.h"

using namespace std;

int main(int argc, char* argv[])
{

	string usage = "usage: ./myAssembler [--help] <filename-path> [-d <depth>] [-h] [-v] [-o <name>]";

	if (argc < 2)
	{
		cout << usage << endl;
		return -1;
	}

	string inFileName = argv[1];
	string outFileName = "mc.mif";

	string temp;
	string temp2;
	string width = "1";
	string depth = "256";
	string mode = "";

	if (inFileName == "--help")
	{
		cout 		<< usage << endl 
					<< endl
					<< "Options:" << endl
					<< "--help\t\tDisplay available options" << endl
					<< "-d <value>\tSet the depth of the .mif file" << endl
					<< "-h\t\tSet the architecture mode to Harvard" << endl
					<< "-o <name>\tSpecify the output file name" << endl
					<< "-v\t\tSet the architecture mode to Von Neumann" << endl;
		return -1;
	}

	for (int i = 2; i < argc; i++)
	{
		temp = argv[i];

		if (temp == "-d")
		{
			//Checks to see if there is an argument after the -d
			if ((i+1) >= argc)
			{
				cout << "myAssembler: error: missing argument for -d" << endl;
				return -1;
			}

			temp2 = argv[i+1];

			//Checks to see if the argument for -d is purely numbers
			if (!isDigits(temp2))
			{
				cout << "myAssembler: error: invalid argument for -d: '" << temp2 << "'" << endl;
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
				cout << "myAssembler: error: missing argument for -o" << endl;
				return -1;
			}

			outFileName = argv[i+1];

			//If filename does not contain .mif, this adds it in.
			if (outFileName.compare(outFileName.size()-4,4,".mif") != 0)
			{
				outFileName.insert(outFileName.size(),".mif");
			}
		
			i++;
		}

		else if (temp == "-h")
		{
			if (mode != "")
			{
				cout << "myAssembler: error: cannot more than one instance of [-h] or [-v]" << endl;
				return -1;
			}

			mode = "h";
			//cout << "Set mode: " << mode << endl;
		}

		else if (temp == "-v")
		{
			if (mode != "")
			{
				cout << "myAssembler: error: cannot more than one instance of [-h] or [-v]" << endl;
				return -1;
			}
			mode = "v";
			//cout << "Set mode: " << mode << endl;
		}

		else
		{
			cout << "myAssembler: error: unknown option: " << argv[i] << endl;
			cout << usage << endl;
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
	myfile.open (outFileName);

	Assembler *myInst;
	vector<string> data(3);

	map<string,string> labels;

	list<string>::iterator it;

	myfile << writeHeader(inFileName, width, depth);

	int totalLines;
	
	string noLead;

	//Decodes for labels
	try
	{
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

		totalLines = counter;

		//Print map for verification

		//Decodes and outputs to mif 
		counter = 0;

		for (it = lines.begin(); it != lines.end(); ++it)
		{
			address = "";
			data = decodeLine(*it);
			noLead = removeLead(*it);

			int opCode = stoi(data[0]);
			switch (opCode)
			{
				case 0:

					if (data[2] != "")
					{
						throw ParamError();
					}

					myInst = new AddInst(*it,counter);

					((Simple*)myInst)->getComment();

					myfile << endl << *((Simple*)myInst);

					delete myInst;
					break;

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

				case 8:

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

					myInst = new JMPUInst(*it,counter, address);

					((Advanced*)myInst)->getComment();

					myfile << endl << *((Advanced*)myInst);

					counter = counter + 2;

					delete myInst;
					break;

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

				case 12:

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

					myInst = new WrInst(*it,counter, address);

					((Advanced*)myInst)->getComment();

					myfile << endl << *((Advanced*)myInst);

					counter = counter + 2;

					delete myInst;
					break;
					
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

					counter = counter + 1;

					delete myInst;
					break;

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
	catch (AddressError)
	{
		cout << "Invalid address on line: " << noLead << endl;
		goto fail;
	}
	catch(ParamError)
	{	
		cout << "Invalid parameter on line: " << noLead << endl;
		goto fail;
	}
	catch(UndefLabel)
	{
		cout << "Undefined Label on line: " << noLead << endl;
		goto fail;
	}
	catch(VonError)
	{	
		cout << "Potential program overwrite due to address on line: " << noLead << endl;
		goto fail;
	}
	catch(JmpError)
	{	
		cout << "Jumping to address outside of program bounds due to address on line: " << noLead << endl;
		goto fail;
	}
	catch(InstError)
	{	
		cout << "Invalid instruction on line: " << noLead << endl;
		goto fail;
	}

	myfile << "\n\nEND;";

	myfile.close();

	return 0;

	fail:

	myfile.close();
	const char *cstr = outFileName.c_str();
	remove(cstr);
	return -1;

}