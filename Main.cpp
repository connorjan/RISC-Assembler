#include "SimpleInst.h"
#include "File.h"
#include "Exception.h"

using namespace std;

int main(int argc, char* argv[])
{
	//cout << argc << endl; //Number of Params
	//cout << argv[0] << endl; //Path to executable
	//cout << argv[1] << endl; //Any subsequent params

	if (argc != 2)
	{
		cout << "usage: ./myAssembler <filename-path>" << endl;
		return -1;
	}
	string inFileName = argv[1];

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

	ofstream myfile;
	myfile.open ("mc.mif");

	Assembler *myInst;
	vector<string> data(3);

	map<string,string> labels;

	list<string>::iterator it;

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
	map<string, string>::iterator pos;
    for(pos = labels.begin(); pos != labels.end(); ++pos)
    {
         cout << "Key: " << pos->first << endl;
         cout << "Value: " << pos->second << endl;
    }




	//Decodes and outputs to mif 
	counter = 0;

	for (it = lines.begin(); it != lines.end(); ++it)
	{
		data = decodeLine(*it);
		int opCode = stoi(data[0]);
		
		switch (opCode)
		{
			case 0:
				
				myInst = new AddInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				//CHECK TO MAKE SURE DATA[2] IS EMPTY!!!!

				delete myInst;
				break;

			case 1:

				myInst = new SubInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 2:

				myInst = new IncInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 3:

				myInst = new DecInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;
				
			case 4:

				myInst = new NotInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 5:

				myInst = new AndInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 6:

				myInst = new OrInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;
				
			case 7:

				myInst = new ShrInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 8:
				counter = counter + 2;
				break;

			case 9:
				counter = counter + 2;
				break;
				
			case 10:

				myInst = new SwapInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 11:
		

				myInst = new CpyInst(*it, counter);
			
				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 12:
				counter = counter + 2;
				break;
				
			case 13:
				counter = counter + 2;
				break;

			case 14:
				counter++;
				break;

			case 15:
				counter++;
				break;
				
			case 16:

				myInst = new PushInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

				delete myInst;
				break;

			case 17:

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

	myfile.close();

	return 0;
}