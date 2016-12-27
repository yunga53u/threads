#include <iostream>
#include <stdexcept>
#include "reader.h"

using namespace std;

int main(int argc, char **argv)
{
    try
    {
    	Reader reader;
	    reader.work();
    }
    catch(const char * ex)
    {
    	std::cerr << "Exception: " << ex << std::endl;
	    return 1;
    }
    catch(std::exception &ex)
    {
	    std::cerr << "Exception: " << ex.what() << std::endl;
	    return 1;
    }
    catch(...)
    {
	    std::cerr << "Unknown Exception" << std::endl;
	    return 1;
    }

    return 0;
}

