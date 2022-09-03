#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

	/************* You complete *************/

	ifstream ifile(argv[1]);
	if(ifile.fail()){
		cout << "Couldn't open file, quitting program" << endl;
		return -1;
	}

	int base;
	string d_string, n_string;
	ifile >> base >> d_string >> n_string;
	if(ifile.fail()){
		cout << "Failure to read base, d, or n, quitting program" << endl;
		return -1;
	}
  // These two BigInts could be here but better to put it in the try{}
	// BigInt d(d_string, base); // privateKey
	// BigInt n(n_string, base); // modulus

	while(!ifile.fail()){
    //The try block lets you enclose one or more statements
    //that might throw an exception.
    try{
	    BigInt d(d_string, base); // privateKey
	    BigInt n(n_string, base); // modulus

      string secret_code_string;
      ifile >> secret_code_string;
      BigInt secret_code(secret_code_string, base);
      BigInt result(base);

      result = modPow(secret_code, d, n); // Decipher message (BigInt form)
      char result_int = result.to_int(); // Get ASCII value of int form
      cout << result_int;
    }
    //The catch block will 'catch' an exception thrown by a statement in the try block.
    //Since our custom exceptions inherit from std::exception, we can
    //catch them all with std::exception type like so.
    catch(const exception& e){
        cout<<e.what()<<endl;//print the message of the exception defined in its "what" function.
        return -1;//end the program and return status != 0 to indicate that there is an error.
    }
	}
  cout << endl; // Comes after deciphering the whole message
  ifile.close();
  return 0;
}
