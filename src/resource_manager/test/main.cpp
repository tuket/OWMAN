#include "../resource_manager.hpp"
#include <iostream>
#include <string>

using namespace std;

#ifdef _WIN32

    #include <windows.h>

    void mySleep(unsigned milliseconds)
    {
        Sleep(milliseconds);
    }
    
#else

    #include <unistd.h>

    void mySleep(unsigned milliseconds)
    {
        usleep(milliseconds * 1000);
    }
    
#endif


using namespace std;

int main()
{
	
	ResourceManager resourceManager;
	resourceManager.launch();
	
	ResourceText* resourceText = resourceManager.obtainText("rufol");
	
	while( resourceText->getStatus() != Resource::Status::LOADED )
	{
		mySleep(10);
	}
	
	cout << resourceText->getText() << endl;
	
}
