
#include "SmartPacket.h";
using namespace std;

int main()
{
	SmartPacket* packet = new SmartPacket;

	WORD header = 3;
	string str1("xxxx");
	string str2("ttttttttt");


	packet->push(header)->push(str1)->push(str2)->build()->log();

	typedef struct {
		WORD header;
		STRING str1;
		STRING str2;
	} packetType;
	packetType* parsedPacket = packet->parse<packetType>();
	cout << "\n\n";
	cout << parsedPacket->header;
	cout << "\n\n";
	cout << parsedPacket->str1.read();
	cout << "\n\n";
	cout << parsedPacket->str2.read();
	cout << "\n\n";
	return 0;
}
