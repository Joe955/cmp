#include <iostream>
#include <string.h>
#include <assert.h>
#include <math.h>

using namespace std;

#define TYPE_INIT		00
#define TYPE_DIGIT		01
#define TYPE_CHAR		02
#define TYPE_REVERSE	03

bool checkArgNum(int argc);
char GetType(char s);

class ruleStorage
{
	
};

char* GetTruelyString(char* str)
{
	char *p= str + strlen(str);
	int result_len = sizeof(char) * strlen(str) + 1;
	char *result = malloc(result_len)
	memset(result, 0, result_len);
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

bool CompareStr(char *str1, char *str2)
{
	
}

void testCompareStr(char *str1, char *str2)
{
	
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

void testGetDigitStrValue()
{
	char *str1 = "01";
	assert(GetDigitStrValue(str1) == 1);
	
	char *str2 = "101";
	assert(GetDigitStrValue(str2) == 101);
	
	char *str3 = "10\A";
	assert(GetDigitStrValue(str3) == 165);
	
	char *str4 = "1\A0";
	assert(GetDigitStrValue(str4) == 750);
	
	char *str5 = "\B10";
	assert(GetDigitStrValue(str5) == 6610);
	
	cout<<"testGetDigitStrValue : ok"<<endl;
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

void testCompareDigit()
{
	char *str1 = "01";
	char *str2 = "1";
	assert(CompareDigit(str1, str2) == 1);
	
	str1 = "101";
	str2 = "11";
	assert(CompareDigit(str1, str2) == 1);
	
	str1 = "101";
	str2 = "\A1";
	assert(CompareDigit(str1, str2) == -1);
	
	str1 = "\A1";
	str2 = "\A1";
	assert(CompareDigit(str1, str2) == 0);
	
	cout<<"testCompareDigit : ok"<<endl;
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

class clsBaseObj
{
public:
	clsBaseObj(char* s)
	{
		int size = sizeof(char*)*strlen(s)+1;	

		storage = (char*)malloc(size);
		memset(storage, 0, size); 
		strcpy(storage, s);

		cout<<storage<<endl;
	}
	virtual ~clsBaseObj()
	{
		cout<<"free mem:"<<storage<<endl;
		free(storage);
	}
private:
	char *storage;
};

int main(int argc, char *argv[])
{
	if( !checkArgNum(argc))
	{
		cout<<"argc != 2!"<<endl;
		return -2;
	}

	cout<<"arg[1]:"<<argv[1]<<endl;
	clsBaseObj a = clsBaseObj(argv[1]);
	cout<<"arg[2]:"<<argv[2]<<endl;
	cout<<strcmp(argv[1], argv[2])<<endl;
	
	testCompareDigit();
	testGetType();
	testSplitSotrage();
	testGetDigitStrValue();
	return 0;
}
bool checkArgNum(int argc)
{
	return (argc==3);
}



