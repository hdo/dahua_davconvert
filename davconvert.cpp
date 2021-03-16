//============================================================================
// Name        : davconvert.cpp
// Author      : Huy Do (huydo1@gmail.com)
// Version     : 2021-03-16
// Description : DAV to AVI convert for DAHUA NVR
//============================================================================

#include <iostream>
#include <unistd.h> // for sleep
#include <string>
#include <fstream>
#include "lib/dhplay.h"
using namespace std;

#define PORT 0
#define SOURCEBUF_SIZE (500 * 1024)


bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

int main(int argc, char* argv[]) {
    cout << "Dahua DHPlay Convert" << endl; 
   
    if (argc < 3) {
       cout << "Error: Missing params!" << endl;
       return 1;
    }
  
    if (!is_file_exist(argv[1])) {
       cout << "Error: File dos not exists! " << argv[1] << endl;
       return 1;
    }

    cout << "Input: " << argv[1] << endl;
    cout << "Output: " << argv[2] << endl;

    PLAY_SetStreamOpenMode(PORT, STREAME_FILE);
    PLAY_OpenStream(PORT, NULL, 0, SOURCEBUF_SIZE);
    PLAY_Play(PORT, NULL);
    BOOL retValue = PLAY_StartDataRecord(PORT, argv[2], 1);
    cout << "init: " << retValue <<endl;

    FILE *fp;
    const int READ_LEN = 8 * 1024;
    unsigned char readBuf[READ_LEN] = {0};
    unsigned int readbytes = 0;

    if (!retValue)
    {
        cout << "failed" << endl;
        return 1;
    }
    else {
        cout << "Converting ..." << endl;
        fp = fopen(argv[1], "r");
        readbytes = fread(readBuf, 1, READ_LEN, fp);
        while(readbytes > 0) 
        {
            while (!PLAY_InputData(PORT, readBuf, readbytes))
            {
	    		usleep(10);
            }
    
            readbytes = fread(readBuf, 1, READ_LEN, fp);
        }
        PLAY_StopDataRecord(PORT);
    }
    PLAY_Stop(PORT);
    PLAY_CloseStream(PORT);
    cout << "Done." << endl;

    return 0;
}

