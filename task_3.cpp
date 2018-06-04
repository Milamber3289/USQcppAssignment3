#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include <ctime>
#include "exception.h"
using namespace std;

string openFile(ifstream& in, string str);
/**

@param ifstream 
@param str 
*/


string openFile(ofstream& out, string str);
/**

@param ifstream 
@param str 
*/

double string_to_double(string number_string);
/**

@param ifstream 
@param str 
*/

int main(int argc, char* argv[])
{
	//test correct number of arguments and capture variables
	try
	{
		if(argc!=3)
		{
			throw Argc_error("Usage: app_name data_file_name output_file_name.");
		}
	}
	catch(Argc_error Argc_error_text)
	{
		cout<<Argc_error_text.what();
		return 1;
	}
	string arg_input_file_name=argv[1];
	string arg_output_file_name=argv[2];
	//open input and output streams
	ifstream in;
	ofstream out;
	string opened_input_file = openFile(in, arg_input_file_name);
	string opened_output_file = openFile(out, arg_output_file_name);


	
	//get current time
	time_t current_time;
	time( &current_time );
	// format time
	struct tm *local_time;
	local_time = localtime ( &current_time );
	char current_time_string[30];
	strftime(current_time_string, 30, "Date: %x %X", local_time);


	
	
	
	//////////////////////////////////////////////////////
	//testing couts - delete after program is finished
	
	cout<<opened_input_file<<endl;
	cout<<opened_output_file<<endl;
	
	cout << current_time_string << endl;
	
	//testing couts - delete after program is finished
	//////////////////////////////////////////////////////
	
	
	
	
	//close streams
	in.close();
	out.close();	
	
	
	
	
	
	
	return 0;
}

string openFile(ifstream& in, string str)
{
	string error_msg="";
	in.open(str.c_str());
	try
	{
		if(in.fail())
			{
				error_msg="cannot open data file "+str+". Please input the correct data file name:";
				throw Readfile_error(error_msg);
			}
	}
	catch(Readfile_error Readfile_error_text)
	{
		cout<<Readfile_error_text.what();
		getline(cin,str);
		return openFile(in, str);
	}
	return str;
}

string openFile(ofstream& out, string str)
{
	return str;
}

double string_to_double(string number_string) 
{
	istringstream instr(number_string);
	double number;
	instr >> number;
	return number;
}