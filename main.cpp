#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <climits>

using namespace std;

void* findLargestInFile(void* fileName);

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2;
    char *message1 = argv[1];
    char *message2 = argv[2];
    int  max1, max2;

    pthread_create(&thread1, NULL, findLargestInFile, (void*)message1);
    pthread_create(&thread2, NULL, findLargestInFile, (void*)message2);

    pthread_join( thread1, (void **)&max1);
    pthread_join( thread2, (void **)&max2); 

    cout << "Maximum number for both files is " << (max1 > max2 ? max1 : max2) << endl;
    
    return 0;
}

void* findLargestInFile(void* rawFileName)
{
    char* fileName = (char*)rawFileName;
    int largest = INT_MAX;
    int current;
    string line;
    ifstream myfile(fileName);
    
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
    
    return 0;
}
