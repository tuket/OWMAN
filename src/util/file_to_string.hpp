#include <fstream>

#ifndef FILE_TO_STRING
#define FILE_TO_STRING

char* fileToString(const char* fileName)
{
	
	std::fstream fs;
	fs.open(fileName, std::fstream::in);
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

#endif
