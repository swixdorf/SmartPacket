#pragma once
#pragma warning(disable : 5208)
using namespace std;
#include <iostream>
#include <map>
typedef unsigned short BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

typedef struct {
	WORD offset;
	WORD len;
	string read()
	{
		char* c = (char*)((uint32_t)&offset + offset);
		string str(c, len);
		return str;
	}
} STRING;

extern class SmartPacket {
private:
	char* buffer;
	DWORD bufferLength = 0;
	char* stringBuffer;
	DWORD stringBufferLength = 0;
	map<int, int> stringPositions;
public:
	SmartPacket();
	~SmartPacket();
	template <typename T> SmartPacket* push(T data);
	SmartPacket* build();
	char* packet();
	WORD length();
	void log();
	template <typename T> static T* parse(char* data);
	template <typename T> T* parse();
};


template < typename T >
SmartPacket* SmartPacket::push(T data)
{
	if (typeid(data) == typeid(BYTE) /*|| typeid(data) == typeid(WORD)*/ || typeid(data) == typeid(DWORD))
	{
		memcpy(&buffer[bufferLength], &data, sizeof(data));
		bufferLength += sizeof(data);
	}
	else if (typeid(data) == typeid(string))
	{
		string str = *(string*)(void*)&data;

		*(WORD*)&buffer[bufferLength] = 0;
		memcpy(&stringBuffer[stringBufferLength], str.c_str(), str.length());
		stringPositions[bufferLength] = stringBufferLength;
		bufferLength += sizeof(WORD);
		stringBufferLength += str.length();

		*(WORD*)&buffer[bufferLength] = (WORD)str.length();
		bufferLength += sizeof(WORD);
	}
	else {
		cout << "Packet :: Unknown Data Type \n";
	}
	return this;
}

template <typename T>
static T* SmartPacket::parse(char* data)
{
	T* swx = (T*)&data[0];
	return swx;
}
template <typename T>
T* SmartPacket::parse()
{
	T* swx = (T*)&buffer[0];
	return swx;
}