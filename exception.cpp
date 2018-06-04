#include "exception.h"
#include<string>

Argc_error::Argc_error(string reason):logic_error(reason){}

Readfile_error::Readfile_error(string reason):logic_error(reason){}

Writefile_error::Writefile_error(string reason):logic_error(reason){}

Digit_error::Digit_error(string reason):logic_error(reason){}