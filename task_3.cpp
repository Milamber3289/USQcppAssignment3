#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include<cctype>
#include<iomanip>
#include <ctime>
#include "exception.h"
using namespace std;

string openFile(ifstream& in, string str);
/**Loads the file named in 'str' to the input file stream 'in'. 
If the file cannot be opened, the user is prompted to input a new file name.
Returns the name of the file that was opened. This may not be the same file originally named in the function call.
@param in input file stream which will open the file.
@param str the name of the file to be opened in string form. 
*/


string openFile(ofstream& out, string str);
/**Loads the file named in 'str' to the output file stream 'out'. 
If the file cannot be opened, the user is prompted to input a new file name.
Returns the name of the file that was opened. This may not be the same file originally named in the function call.
@param out output file stream which will open the file. 
@param str the name of the file to be opened in string form. 
*/

double string_to_double(string number_string);
/**Takes a string as an argument and returns a double.
number_string must consist of numbers only to avoid logic errors.
@param number_string A string of digits representing the number value. 
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

	//validate opened input file
	string proceed_command = " ";
	if(opened_input_file!=arg_input_file_name)
	{
		cout<<"Cannot open "<<arg_input_file_name<<", "<<opened_input_file<<" opened instead."<<endl;
		cout<<"Do you want to proceed? ('y' to proceed) ";
		getline(cin,proceed_command);
		if(proceed_command!="y"&&proceed_command!="Y")
		{
			cout<<"Cannot proceed further. Program is closing down.";
			return 2;
		}
	}
	
	//validate opened output file
	if(opened_output_file!=arg_output_file_name)
	{
		cout<<"Cannot open "<<arg_output_file_name<<", "<<opened_output_file<<" opened instead."<<endl;
		cout<<"Do you want to proceed? ('y' to proceed) ";
		getline(cin,proceed_command);
		if(proceed_command!="y"&&proceed_command!="Y")
		{
			cout<<"Cannot proceed further. Program is closing down.";
			return 3;
		}
	}

	//read each line of input file and calculate summary figures. Skip a line if payment is not a number
	double total_payments=0.0;
	int count_payments=0;
	double average_payments=0.0;
	
	const int name_chars = 40;
	const int payment_chars = 10;
	string this_line = "";
	string this_payment = "";
	
	string digit_error_msg="";
	
	//Loop through each line of the input file and read payments. 
	//Check if payment is valid, and either display an error message or increment total & count
	while(!in.eof())
	{
		getline(in,this_line);
		string this_payment = this_line.substr(name_chars, payment_chars);
		
		try
		{
		//loop through each character in this_payment and check if it's a digit. Throw error if it's not
			for(int i=0;i<payment_chars;i++)
			{
				if(!(isdigit(this_payment[i])||this_payment[i]==' '))
				{
					digit_error_msg = "Number contains non digits: "+this_payment;
					throw Digit_error(digit_error_msg);
				}
			}
		//increment total and count
		total_payments+=string_to_double(this_payment);
		count_payments++;
		}
		catch(Digit_error Digit_error_text)
		{
			cout<<Digit_error_text.what()<<endl;
			cout<<"Current line will be skipped!"<<endl<<endl;
		}
	}
	
	//calculate average payment
	average_payments=total_payments/count_payments;
	
	//get current time
	time_t current_time;
	time( &current_time );
	// format time
	struct tm *local_time;
	local_time = localtime ( &current_time );
	char current_time_string[30];
	strftime(current_time_string, 30, "Date: %x %X", local_time);

	//write output file
	out<<current_time_string<<endl;
	out<<"Total payment: $"<<total_payments<<endl;
	out<<"Average payment: $"<<setprecision(2)<<fixed<<average_payments<<endl;
	
	//close streams
	in.close();
	out.close();	
	
	//open output file as input stream
	ifstream saved_output;
	openFile(saved_output, opened_output_file);
		
	//display output file
	while(!saved_output.eof())
	{
		getline(saved_output,this_line);
		cout<<this_line<<endl;
	}
	saved_output.close();
	
	
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
	string error_msg="";
	out.open(str.c_str());
	try
	{
		if(out.fail())
			{
				error_msg="cannot open data file "+str+". Please input the correct data file name:";
				throw Writefile_error(error_msg);
			}
	}
	catch(Writefile_error Writefile_error_text)
	{
		cout<<Writefile_error_text.what();
		getline(cin,str);
		return openFile(out, str);
	}
	return str;
}

double string_to_double(string number_string) 
{
	istringstream instr(number_string);
	double number;
	instr >> number;
	return number;
}