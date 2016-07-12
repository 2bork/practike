#include <cstring>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
//a.txtwords.txt
int count = 0;
string read(char* name)
{
	ifstream text(name);
	string s1, s2;
	while (!text.eof())
	{
		if (text.eof()) break;
		s2 = s2 + " " + s1;	
		text >> s1;		
	}
	text.close();
	return s2;
}
string* english(string s)//read english words
{
	string word;
	stringstream ss(s);
	string* array;
	//int count = 0;
	while (ss>>word)
		count++;
		ss.clear();
		ss.seekg(0, ios::beg);
		array = new string[count/2];
		int i = 0, flag = 0;
	while (ss>>word)
	{
		if (flag == 0)
		{	
			array[i++] = word;
			flag = 1;
		}
		else
			flag = 0;
	}
	return array;
}	
string* russian(string s)//read russian words
{
	string word;
	stringstream ss(s);
	string* array;
	//int count = 0;
	while (ss>>word)
		count++;
		ss.clear();
		ss.seekg(0, ios::beg);
		array = new string[count/4];
		int i = 0, flag = 0;
	while (ss>>word)
	{
		if (flag == 0)
		{	
			//array[i++] = word;
			flag = 1;
		}
		else
		{			
			array[i++] = word;
			flag = 0;
		}	
	}
	return array;
}	

int main()
{
	//char path[30] = "/home/user/a.txtanimal.txt";
	char* path1 = "/home/user/a.txt";
	char path2[30];
	cout << "Input topic of test" << endl;
	cin >> path2;
	char* path3 = ".txt";
	int l1 = strlen(path1);
  //int l2 = strlen(path2);
	int l3 = strlen(path3);
	char* path = new char[l1+30+l3+1];
	strcpy(path, path1);
	strcat(path, path2);
	strcat(path, path3);
	string str = read(path);//read text
	delete[] path;
	string* array = english(str);//eng
	string* per = russian(str);//ru
	
	//start test

	string vvod;
	string sl1;

	int i=0;
	int j=0;
	int k=0;
	int z=0;
		//for (int i=0; i<count; i++){
	cout << count << endl;	
	count = count/4;
	cout << count << endl;
	do
	{
		j=rand() % (count);
		cout<<"Enter a translation of the word "<<endl; 
    cout<< array[j]<<endl;
		cin>>vvod; 
		sl1=per[j];

		if (sl1 == vvod){ 
			cout << "It is right"<<endl; 
		}
		else{
			cout << "It is wrong"<<endl; 
			//i--;
		} 
		cout<<"Continue? 1-no, other number-yes"<<endl;
		cin>>z;
	}while( z!= 1);
	delete[] array;
	delete[] per;
	return 0;
}//main
