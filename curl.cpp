#include <cstring>
//#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "curl/curl.h"
#include <cstdlib>
using namespace std;
static char errorBuffer [CURL_ERROR_SIZE];
static string buffer;
int result;
int count = 0, count2 = 0;
string* dis;
string disstr;
static int writer(char *data, size_t size, size_t nmemb, string *buffer)
{
	result = 0;
	if (buffer != NULL)
	{
		buffer->append(data, size * nmemb);
		result = size * nmemb;
	}
	return result;
}
//func translate
string trans(string word)
{
	buffer = "";
	CURL *curl;
	CURLcode res;
	
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);		

		//mrak
		char *newword = new char[word.size()];
  	strcpy(newword, word.c_str());
		char* http1 = "http://api.multillect.com/translate/plain/1.0/326/?method=translate/api/translate&from=eng&to=rus&text=";
		char* http2 = "&sig=755757a6df03f9a1ca7fddc7bd3d532d";
		int l1 = strlen(http1);
		int l2 = strlen(newword);
		int l3 = strlen(http2);
		char* http = new char[l1+l2+l3+1];
		strcpy(http, http1);
		strcat(http, newword);
		strcat(http, http2);
		delete[] newword;
		//stop mrak pls
		
		curl_easy_setopt(curl, CURLOPT_URL, http);
		delete[] http;
		//curl_easy_setopt(curl, CURLOPT_URL, "translate.yandex.net/api/v1.5/tr/translate?key=trnsl.1.1.20160704T232541Z.be0863499208fc51.a590d8ee12c687384fcbc9af9f0b10f97dc70ee0 &text=I need your love&lang=eu-ru");
		//curl_easy_setopt(curl, CURLOPT_PROXY, "proxy:8080");
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);		
		result = curl_easy_perform(curl);
		if (result == CURLE_OK)
		{	//cout << "Perevod sdelan" << endl;
			return buffer;
		}		
		else
			cout << "Error!" << errorBuffer << endl;
	}	
	curl_easy_cleanup(curl);
}
//end of func translate

//schitavanie
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
//proverka
int prover(string word)
{
	for(int i = 0; i < count2; i++)
	{
		if ((word == dis[i]) || (word == " "))
			return 1;
		
	}
	return 0;
}
//razbienie na slova s proverkoi
string* newwords(string s)
{
	string word;
	stringstream ss(s);
	string* array;
	//int count = 0;
	while (ss>>word)
		count++;
		ss.clear();
		ss.seekg(0, ios::beg);
		array = new string[count];
		int i = 0;
	while (ss>>word)
	{
		if (prover(word) == 0)		
			array[i++] = word;
		else
			count--;
	}	
	return array;
}	
//razbienie na slova 
string* onwords(string s)
{
	string word;
	stringstream ss(s);
	string* array;
	//int count = 0;
	while (ss>>word)
		count2++;
		ss.clear();
		ss.seekg(0, ios::beg);
		array = new string[count2];
		int i = 0;
	while (ss>>word)	
		array[i++] = word;
	return array;
}	
//


int main(int argc, char* argv[])//
{	
	char olddis[] = "/home/user/dis.txt";//dictionary
	disstr = read(olddis);//read text
	dis = onwords(disstr);	
	//read text to string
	char tp[30];//tema
	cout << "Input topic" << endl;
	cin >> tp;
	string str = read(argv[1]);//read text
	//cout << endl << str << endl;
	//	
	//strcpy(name2, name);
	//strcat(name2, "trans.txt");
	//ofstream fout(name2);
	//string strper = trans(str);
	//fout << strper;
	//fout.close();
	//integrate in massiv	
	string* array = newwords(str);

	//go  to translate
	//string per[count] ;
	string *per = new string[count];
	for (int j = 0; j < count; j++)
	{
		per[j] = trans(array[j]);
	}
	//
	char name[50];
	strcpy(name, argv[1]);
	strcat(tp, ".txt");
	strcat(name, tp);
	ofstream f2(name);
	for (int j = 0; j < count; j++)
	{
		cout << array[j] << endl;
		f2 << array[j];
		f2 << "\t" << per[j] << endl;
	}
	f2.close();


	//end test
	delete[] dis;
	delete[] array;
	delete[] per;
	//cout << endl << "Translation" << endl << per << endl;
	return 0;
}
