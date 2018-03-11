#include <iostream>
#include <string.h>
#include <assert.h>
#include <math.h>

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
void main_test();

int CompareSubString(char *str1, char *str2)
{
	if(GetSubStringType(str1) == GetSubStringType(str2)) 
	{
		if(GetSubStringType(str1) == TYPE_CHAR)
		{
			return CompareStr(str1, str2);
		}
		else
		{
			return CompareDigit(str1, str2);
		}
	}
	else if(GetSubStringType(str1) == TYPE_CHAR && GetSubStringType(str2) == TYPE_DIGIT) 
	{
		return 1;
	}
	else if(GetSubStringType(str1) == TYPE_DIGIT && GetSubStringType(str2) == TYPE_CHAR) 
	{
		return -1;
	}
	else
	{
		return -2;
	}
	
}

int GetSubStringType(char *str)
{
	char *p = str;
	if(GetType(*p) == TYPE_CHAR) 
	{
		return TYPE_CHAR;
	}
	
	if(GetType(*p) == TYPE_REVERSE && GetType(*(p+1)) == TYPE_DIGIT)
	{
		return TYPE_CHAR;
	}
	
	if(GetType(*p) == TYPE_DIGIT) 
	{
		return TYPE_DIGIT;
	}
	
	if(GetType(*p) == TYPE_REVERSE && GetType(*(p+1)) == TYPE_CHAR)
	{
		return TYPE_DIGIT;
	}
	
	return TYPE_ERROR;
}


char* GetTruelyString(char *str)
{
	char *p = str;
	int result_len = sizeof(char) * strlen(str) + 1;
	
	char *result = (char*)malloc(result_len);
	char *p_r = result;
	memset(result, 0, result_len);
	
	int counter = 0;
	for(;*p!='\0';p++)
	{

		if((int(GetType(*p)) == TYPE_DIGIT) || (int(GetType(*p)) == TYPE_CHAR))
		{
			*p_r = *p;
			p_r++;
		}
		
	}
	return result;
}

int CompareStr(char *str1, char *str2)
{
	return strcmp(GetTruelyString(str1), GetTruelyString(str2));
}



double GetDigitStrValue(char *str1)
{
	char *p= str1 + strlen(str1);
	
	int counter = 0;
	double result = 0;
	for(;p!=str1;p--)
	{
		if(GetType(*(p-1)) == TYPE_DIGIT)
		{
			result += double(*(p-1) - 48) * pow(10, counter);
			counter++;
		}
		
		if(GetType(*(p-1)) == TYPE_CHAR)
		{
			result += double(*(p-1)) * pow(10, counter);
			counter++;
		}
		
	}
	return result;
}

int CompareDigit(char *str1, char *str2)
{
	double value_str1 = GetDigitStrValue(str1);
	double value_str2 = GetDigitStrValue(str2);
	
	if(value_str1 > value_str2)
	{
		return 1;
	}else if(value_str1 == value_str2)
	{
		if(strlen(str1)> strlen(str2))
		{
			return 1;
		}else if(strlen(str1) == strlen(str2))
		{
			return 0;
		}else{
			return -1;
		}
	}else{
		return -1;
	}
	
}


char GetType(char s)
{
	
	if(s>='0' && s<='9')
	{
		return TYPE_DIGIT;
	}
	
	if((s>='A' && s<='Z') || (s>='a' && s<='z'))
	{
		return TYPE_CHAR;
	}
	
	if(s == '\\')
	{
		return TYPE_REVERSE;
	}
	
	return TYPE_INIT;
}

char testGetType()
{
	assert(GetType('1') == TYPE_DIGIT);
	assert(GetType('0') == TYPE_DIGIT);
	assert(GetType('A') == TYPE_CHAR);
	assert(GetType('B') == TYPE_CHAR);
	assert(GetType('\\') == TYPE_REVERSE);
	assert(GetType('\n') == TYPE_INIT);
	cout<<"testGetFlag : ok"<<endl;
}
/*
{
	if(GetType(*s) == TYPE_REVERSE)
			{
				// string start with '\'
				if(sub_string_flag == TYPE_INIT)
				{
					reverse_flag = true;
					sub_string_flag = GetType(*s);
					continue;
				}
				
				// not string start with '\'
				// 1. previous char is '\', illigle!
				if(*(s-1) == '\n')
				{
					return NULL;
				}
				
				// 2. normal
				sub_string_flag = (sub_string_flag + 1)%2
				
				reverse_flag = true;
				continue;
			}
}
*/
char **SplitSotrage(char *s)
{
	char **tmp = NULL;
	tmp = new char*[100];
	memset(tmp, 0, sizeof(char*) * 100);
	char sub_string_flag = TYPE_INIT;// 0x00 init; 0x01 digit; 0x10 char; 0x11 reverse
	bool reverse_flag = false;
	
	int sub_string_start_pos = 0;
	int sub_string_end_pos = 0;
	int sub_string_index = 0;
	
	char *p = s;
	for(int i=1;*p!='\0';p++,i++)
	{

		
		if(*(p+1)=='\0')
		{
			sub_string_end_pos = i;
			
			int sub_length = sub_string_end_pos - sub_string_start_pos + 1;
			
			char * sub_tmp = new char[sub_length + 1];
			memset(sub_tmp, 0, sub_length+1);
			memcpy(sub_tmp, s + sub_string_start_pos, sub_length-1);
			
			tmp[sub_string_index] = sub_tmp;
			
			break;
		}
		
		if(int(GetType(*p)) * int(GetType(*(p+1))) == 2) 
		{
			sub_string_end_pos = i;
			
			int sub_length = sub_string_end_pos - sub_string_start_pos + 1;

			char * sub_tmp = new char[sub_length + 1];
			memset(sub_tmp, 0, sub_length+1);
			memcpy(sub_tmp, s + sub_string_start_pos, sub_length-1);

			tmp[sub_string_index] = sub_tmp;
			
			sub_string_start_pos = i;
			sub_string_index++;

		}		
		
	}

	return  tmp;
}

int CompareString(char *str1, char *str2)
{
	char **arrayStr1 = SplitSotrage(str1);
	char **arrayStr2 = SplitSotrage(str2);
	
	int result = 0;
	for(int i=0; i<100; i++)
	{
		
		if(arrayStr1[i]!=NULL && arrayStr2[i]!=NULL)
		{
			result = CompareSubString(arrayStr1[i], arrayStr2[i]);
			if(0==result)
			{
				continue;
			}
			
			//cout<<"result:"<<result<<endl;
			return result;
		}
		if(arrayStr1[i]!=NULL)
		{
			//cout<<"larger, result:"<<1<<endl;
			return 1;
		}
		else
		{
			//cout<<"small, result:"<<-1<<endl;
			return -1;
		}
	}
}

bool CheckArgNum(int argc)
{
	return (argc==3);
}

int main(int argc, char *argv[])
{
	main_test();
	
	if( !CheckArgNum(argc))
	{
		cout<<"argc != 2!"<<endl;
		return -2;
	}
	
	int result = CompareString(argv[1], argv[2]);
	
	cout<<"result:"<<result<<endl;
	
	return result;
}


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