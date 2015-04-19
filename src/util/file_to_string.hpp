
#ifndef FILE_TO_STRING
#define FILE_TO_STRING

char* fileToString(const char* fileName)
{
	
	fstream fs;
	fs.open(fileName, fstream::in);
	
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
