#include <iostream>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "compare.h"
using namespace std;

#define TYPE_INIT		0x00
#define TYPE_DIGIT		0x01
#define TYPE_CHAR		0x02
#define TYPE_REVERSE	0x03
#define TYPE_ERROR		0x09

bool CheckArgNum(int argc);
char GetType(char s);
int GetSubStringType(char *str);
int CompareStr(char *str1, char *str2);
int CompareDigit(char *str1, char *str2);

void testCompareSubString()
{
	char *str1 = "01";
	char *str2 = "1";
	assert(CompareSubString(str1, str2) == 1);
	
	str1 = "\\1B";
	str2 = "\\1C";
	assert(CompareSubString(str1, str2) == -1);
	
	str1 = "bb";
	str2 = "bb";
	assert(CompareSubString(str1, str2) == 0);
	
	cout<<"testCompareSubString : ok"<<endl;
}

void testGetSubStringType()
{
	char *str1 = "\\1B";
	assert( GetSubStringType(str1) == TYPE_CHAR);
	
	str1 = "bb";
	assert( GetSubStringType(str1) == TYPE_CHAR);
	
	str1 = "sdb";
	assert( GetSubStringType(str1) == TYPE_CHAR);
	
	str1 = "\\B134";
	assert( GetSubStringType(str1) == TYPE_DIGIT);
	
	str1 = "134";
	assert( GetSubStringType(str1) == TYPE_DIGIT);

	str1 = "\\\\sdb";
	assert( GetSubStringType(str1) == TYPE_ERROR);
	
	cout<<"testGetSubStringType : ok"<<endl;
}

void testCompareStr()
{
	char *str1 = "B\\1B";
	char *str2 = "B\\1B";
	assert( CompareStr(str1, str2) == 0);
	
	str1 = "\\1B";
	str2 = "B";
	assert( CompareStr(str1, str2) == -1);
}


void testGetTruelyString()
{
	char *str1 = "\\1B";
	assert( strcmp(GetTruelyString(str1), "1B") == 0);
	
	str1 = "\\123";
	assert(strcmp(GetTruelyString(str1), "123") == 0);
	
	str1 = "aB\\123";
	assert(strcmp(GetTruelyString(str1), "aB123") == 0);
	
	cout<<"testGetDigitStrValue : ok"<<endl;
}



void testGetDigitStrValue()
{
	char *str1 = "01";
	assert(GetDigitStrValue(str1) == 1);
	
	char *str2 = "101";
	assert(GetDigitStrValue(str2) == 101);
	
	char *str3 = "10\\A";
	assert(GetDigitStrValue(str3) == 165);
	
	char *str4 = "1\\A0";
	assert(GetDigitStrValue(str4) == 750);
	
	char *str5 = "\\B10";
	assert(GetDigitStrValue(str5) == 6610);
	
	cout<<"testGetDigitStrValue : ok"<<endl;
}


void testSplitSotrage()
{
	char **array = SplitSotrage("B01");
	assert(strcmp(array[0], "B")==0);
	assert(strcmp(array[1], "01")==0);
	
	array = SplitSotrage("B1");
	assert(strcmp(array[0], "B")==0);
	assert(strcmp(array[1], "1")==0);

	array = SplitSotrage("B2");
	assert(strcmp(array[0], "B")==0);
	assert(strcmp(array[1], "2")==0);

	array = SplitSotrage("B11");
	assert(strcmp(array[0], "B")==0);
	assert(strcmp(array[1], "11")==0);
		
	cout<<"testSplitSotrage : ok"<<endl;
}


void testCompareDigit()
{
	char *str1 = "01";
	char *str2 = "1";
	assert(CompareDigit(str1, str2) == 1);
	
	str1 = "101";
	str2 = "11";
	assert(CompareDigit(str1, str2) == 1);
	
	str1 = "101";
	str2 = "\\A1";
	assert(CompareDigit(str1, str2) == -1);
	
	str1 = "\\A1";
	str2 = "\\A1";
	assert(CompareDigit(str1, str2) == 0);
	
	cout<<"testCompareDigit : ok"<<endl;
}




void testCompareString()
{
	char *str1 = "01\\B";
	char *str2 = "1";
	assert(CompareString(str1, str2) == 1);
	
	str1 = "A\\1B";
	str2 = "A\\1C";
	assert(CompareString(str1, str2) == -1);
	
	str1 = "bb\\11";
	str2 = "bb";
	assert(CompareString(str1, str2) == 1);
	
	cout<<"testCompareSubString : ok"<<endl;
}

void main_test()
{
	testCompareString();
	testCompareSubString();
	testGetSubStringType();
	testGetTruelyString();
	testCompareDigit();
	testCompareStr();
	testGetType();
	testSplitSotrage();
	testGetDigitStrValue();

}