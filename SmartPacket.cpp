#include "SmartPacket.h"

SmartPacket::SmartPacket() {
	buffer = (char*)malloc(65535);
	stringBuffer = (char*)malloc(65535);
}
SmartPacket::~SmartPacket() {
	free(buffer);
	free(stringBuffer);
}
SmartPacket* SmartPacket::build()
{
	for (auto const& x : stringPositions)
	{
		WORD absStrPos = bufferLength + x.second - x.first;
		*(WORD*)&buffer[x.first] = absStrPos;
	}
	memcpy(&buffer[bufferLength], stringBuffer, stringBufferLength);
	return this;
}
char* SmartPacket::packet() {
	return buffer;
}
WORD SmartPacket::length() {
	return bufferLength + stringBufferLength;
}
void SmartPacket::log()
{
	cout << "\n";
	for (int i = 0;i < bufferLength;i++)
		printf("%02X ", buffer[i]);
	cout << "| ";
	for (int i = 0;i < stringBufferLength;i++)
		printf("%02X ", stringBuffer[i]);
	cout << "\n";

}
