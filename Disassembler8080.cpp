#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <string.h>


typedef unsigned char byte;

byte spaceInvaders[10] = {0x00, 0x00, 0x00, 0xc3, 0xd4, 0x18, 0x00, 0x00, 0xf5, 0xc5};

void Disassemble(byte* p_codeBuffer, int& p_pc) {

	byte* code = &p_codeBuffer[p_pc];
	int opBytes = 1; //how many bytes the instruction takes, usually one

	std::cout << std::hex << p_pc <<  " ";
	std::cout << static_cast<unsigned>(*code) << " " << std::dec;

	switch (*code) {
		case 0x00:
			std::cout << "NOP " << std::endl;
			break;
		case 0xc3:
			opBytes = 3;
			std::cout << "JMP ";
			code += 2;
			std::cout << std::hex << static_cast<unsigned>(*code);
			code -= 1;
			std::cout << static_cast<unsigned>(*code) << std::dec << std::endl;
			break;
		case 0xc5:
			std::cout << "PUSH B" << std::endl;
			break;
		case 0xd5:
			std::cout << "PUSH D" << std::endl;
			break;
		case 0xe5:
			std::cout << "PUSH H" << std::endl;
			break;
		case 0xf5:
			std::cout << "PUSH PSW" << std::endl;
			break;
		default:
			std::cout << "Op code currently not supported" << std::endl;
	}		

	p_pc += opBytes;	

}

	
using namespace std;

int main(int argc, const char* argv[]) {
	
	ifstream file;
	file.open(argv[1], ios::binary | ios::in);
	
	//get file size
	file.seekg(0, file.end);
	int fileSize = file.tellg();
	file.seekg(0, file.beg);





	
	char* currentByte = new char[fileSize];
	void* byteAddress;
	byte* byteReader;


	for (int i=0; i<fileSize; i++) {
		file.read(&currentByte[i], 1);	
	}

	byteAddress = currentByte;
	byteReader = static_cast<byte*>(byteAddress);
	
	int pc = 0;
	while (pc < fileSize) {
		Disassemble(byteReader, pc);	
	}
		
	return 0;
}
