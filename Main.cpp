#include "SimpleInst.h"
#include "File.h"
#include "Exception.h"

using namespace std;

int main(int argc, char* argv[])
{
	//cout << argc << endl; //Number of Params
	//cout << argv[0] << endl; //Path to executable
	//cout << argv[1] << endl; //Any subsequent params

	//cout << "Please enter the filename of the assembly file: ";
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

	lines = removeJunk(lines);

	int counter = 0;

	ofstream myfile;
	myfile.open ("mc.mif");

	Assembler *myInst;
	for (list<string>::iterator it = lines.begin(); it != lines.end(); ++it)
	{
			
		switch (decodeLine(*it))
		{
			case 0:
				
				myInst = new AddInst(*it,counter);

				((Simple*)myInst)->getComment();

				myfile << endl << *((Simple*)myInst);

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
				break;

			case 9:

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

				break;
				
			case 13:

				break;

			case 14:

				break;

			case 15:

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
				cout << "Invalid Instruction on line:\t" << *it << endl;
		}

		counter ++;
	}

	myfile.close();

	return 0;
}