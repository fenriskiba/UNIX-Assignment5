#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <climits>

using namespace std;

int findLargestInFile(string fileName);

int main(int argc, char *argv[])
{
    char* fileName1 = argv[1];
    char* fileName2 = argv[2];
    
    pthread_t thread1;
    pthread_t thread2;
    
    int fileMax1;
    int fileMax2;
    
    pthread_create( &thread1, NULL, findLargestInFile, (void*) fileName1);
    pthread_create( &thread2, NULL, print_message_function, (void*) fileName2);

    pthread_join(thread1,(void **)&fileMax1);
    pthread_join(thread2,(void **)&fileMax2);

    cout << largestNumber;
    return 0;
}

int findLargestInFile(void *rawFileName)
{
    string fileName = (string)rawFileName;
    int largest = INT_MAX;
    int current;
    string line;
    ifstream myfile(fileName.c_str());
    
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            current = atoi(line.c_str());
            if(largest == INT_MAX)
            {
                largest = current;
            }
            else if(largest < current)
            {
                largest = current;
            }
        }
        
        myfile.close();
    }
    
    pthread_exit((void *)largest);
    
    return largest;
}
