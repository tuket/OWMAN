#include "file_to_string.hpp"

using namespace std;

char* fileToString(const char* fileName)
{

	fstream fs;
	fs.open(fileName, fstream::in);
	if( !fs.is_open() ) return 0;

	fs.seekg(0, fs.end);
	int length = fs.tellg();
	fs.seekg(0, fs.beg);

	char *buffer;
	buffer = new char[length+1];
	fs.read(buffer, length);
	buffer[length] = '\0';

	return buffer;

}
