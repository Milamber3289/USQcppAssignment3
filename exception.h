#ifndef Exception_H
#define Exception_H
#include <iostream>
#include <stdexcept>
#include <cctype>

using namespace std;

class Argc_error : public logic_error{
	public:
	// Constructor with initial value. string reason can be returned using what() member function from logic_error class
	Argc_error (string reason);
	};
	
class Readfile_error : public logic_error{
	public:
	// Constructor with initial value. string reason can be returned using what() member function from logic_error class
		Readfile_error (string reason);
	};
	
class Digit_error : public logic_error{
	public:
	// Constructor with initial value. string reason can be returned using what() member function from logic_error class
		Digit_error (string reason);
	};
	
class Writefile_error : public logic_error{
	public:
	// Constructor with initial value. string reason can be returned using what() member function from logic_error class
		Writefile_error (string reason);
	};
	
#endif
