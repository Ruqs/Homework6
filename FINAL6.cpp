#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

int hashTable[100000];

int extractionMethod(int number) {
	//using the extraction method to get the 3,5,7,8 digits to use as the address

    string initial = "00000";//
    char * valueC=new char[100];
    sprintf(valueC,"%i",number);
    string value=(string)valueC;

    int j = 0;

    for (int i = 0; i < value.size(); i++)
    {
        initial[i] = value[j];
        j++;
    }

    string final = "0000";
    final[0] = initial[2];
    final[1] = initial[4];
    final[2] = initial[6];
    final[3] = initial[7];
//third, fifth, seventh and eight digits

    return atoi(final.c_str());
    //return index that we want the particular number to be stored at
}

int quadraticProbing(int key, int tableSize, int number)
{
	int Max = 1000;
	int square = 1;
	int pos = (key+number)%Max;
	if (hashTable[pos]==0)
	{
		hashTable[pos]=key;
		return pos;
	}
	//mod divides by whatever number and the answer it gives you is the remainder and max is a value you get from the user and you are doing a mod by that number.
    bool isFull = true;

    for (int i =0; i<tableSize; i++) {
        if (hashTable[i] == 0) {
            isFull = false;
        }
    }


    //check if full
    if (isFull) return -1;

    for (int i = pos+1; i%Max!=pos; i=i+square*square) {
         if (hashTable[i] == 0) {
             isFull = false;
             hashTable[i]=key;
             return i%Max;
         }
     }


    /*int i = number;
    while (hashTable[key] != 0) {
        key += i * i;
        i++;
        key = key%tableSize;
        return key;
    }
    */
    return -1;//if it is full this will be returned
}

int main()
{
    for (int i = 0; i < 100000; i++) {
        hashTable[i] = 0;
    }
    ifstream infile; //input file stream
    ofstream outfile; //output file stream
    string fn;

    cout << "What is the file name: "<<endl;
    getline(cin, fn); //user input the name of the file
    infile.open(fn.c_str()); //open the input file

    while(infile.fail())// if it does not open properly then there's a while loop

    {
        cout << fn << " " << "file not found" << endl;
        cout << "Enter another file: ";
        getline(cin, fn);
        infile.open(fn.c_str());
    }
    string fC = "", temp;

	if (infile.is_open())//if the file does open
	{
		outfile.open("hashed_socials.txt"); //this is the file we want to write out to
		while (infile.peek() != EOF)//peek is reads and returns the next character

		{
		    infile >> temp;
		    fC += temp;

		}
	}
	int number;
	cout<<"Pick a number between 1 and 450 million"<<endl;//this will be used in quadratic probing
	cin>>number;

	vector<int> allNumbers;
	temp = "";
	for (int i = 0; i < fC.size(); i++) {
        if (fC[i] == ',') {
            allNumbers.push_back(atoi(temp.c_str()));
            temp = "";
        }
        else {
            temp += fC[i];
        }
	}

    int index;
	for (int i = 0; i < allNumbers.size(); i++) {
        index = extractionMethod(allNumbers[i]);
        if (hashTable[index] == 0) {
            hashTable[index] = allNumbers[i];
            cout << allNumbers[i] << " NO COLLISION" << endl;
        }
        else {
        	//int max;
        	//cout<<"What number do you want? ";
            //cin>>max;
        	cout << allNumbers[i] << " COLLISION" << endl;
            index = quadraticProbing(index, 10000, number);
            if (index != -1) {
                hashTable[index] = allNumbers[i];
                cout << "put in " << index << " instead" << endl;
            }
            else {
                cout << "FULL" << endl;
                break;
            }
        }

	}

    for (int i = 0; i < 100000; i++) {
        outfile << hashTable[i];
        if (i<99999)outfile<<",";
    }//to make sure there are commas separating all values

	infile.clear();
	outfile.clear();
	infile.close(); //close the input file
    outfile.close(); //close the output file


    cout << "Complete" << endl;
    return 0;
}
