#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <string.h>



typedef unsigned char byte;

byte spaceInvaders[10] = {0x00, 0x00, 0x00, 0xc3, 0xd4, 0x18, 0x00, 0x00, 0xf5, 0xc5};

void Disassemble(byte* p_codeBuffer, int& p_pc, std::ofstream& p_file) {

	byte* code = &p_codeBuffer[p_pc];
	int opBytes = 1; //how many bytes the instruction takes, usually one
	


	
	p_file << std::hex << p_pc <<  " ";
	p_file << static_cast<unsigned>(*code) << " " << std::dec;

	switch (*code) {
		case 0x00:
			p_file << "NOP " << std::endl;
			break;
		case 0x01:
			opBytes = 3;
			p_file << "LXI ";
			code += 2;
			p_file << std::hex << static_cast<unsigned>(*code) << std::endl;	
			break;
		case 0x02:
			p_file << "STAX B" << std::endl;
			break;
		case 0x03:
			p_file << "INX B" << std::endl;
			break;
		case 0x04:
			p_file << "INR B" << std::endl;
			break;
		case 0x05:
			p_file << "DCR B" << std::endl;
			break;
		case 0x06:
			opBytes = 2;
			code++;
			p_file << "MVI " << std::hex << static_cast<unsigned>(*code) << ", D8" << std::endl;
			break;
		case 0x07:
			p_file << "RLC" << std::endl;
			break;
		case 0x08:
			p_file << "-" << std::endl;
			break;
		case 0x09:
			p_file << "DAD B" << std::endl;
			break;
		case 0x0a:
			p_file << "LDAX B" << std::endl;
			break;
		case 0x0b:
			p_file << "DCX B" << std::endl;
			break;
		case 0x0c:
			p_file << "INR C" << std::endl;
			break;
		case 0x0d:
			p_file << "DCR C" << std::endl;
			break;
		case 0x0e:
			opBytes = 2;
			code++;
			p_file << "MVI " << std::hex << static_cast<unsigned>(*code) << ",d8" << std::dec << std::endl;
			break;	
		case 0x0f:
			p_file << "RRC" << std::endl;
			break;
		case 0x10:
			p_file << "-" << std::endl;
			break;
		case 0x11:
			opBytes = 3;
			code += 2;
			p_file << "LXI " << std::hex << static_cast<unsigned>(*code) << ",D16" << std::dec << std::endl;
			break;
		case 0x12:
			p_file << "STAX D" << std::endl;
			break;
		case 0x13:
			p_file << "INX D" << std::endl;
			break;
		case 0x14:
			p_file << "INR D" << std::endl;
			break;
		case 0x15:
			p_file << "DECR D" << std::endl;
			break;
		case 0x16:
			opBytes = 2;
			code++;
			p_file << "MVI " << std::hex << static_cast<unsigned>(*code) << ", D8" << std::dec << std::endl;
			break;
		case 0x17:
			p_file << "RAL" << std::endl;
			break;
		case 0x18:
			p_file << "-" << std::endl;
			break;
		case 0x19:
			p_file << "DAD D" << std::endl;
			break;
		case 0x1a:
			p_file << "LDAX D" << std::endl;
			break;
		case 0x1b:
			p_file << "DCX D" << std::endl;
			break;
		case 0x1c:
			p_file << "INR E" << std::endl;
			break;
		case 0x1d:
			p_file << "DCR E" << std::endl;
			break;
		case 0x1e:
			opBytes = 2;
			code++;
			p_file << "MVI " << std::hex << static_cast<unsigned>(*code) << ",D8" << std::dec << std::endl;
			break;
		case 0x1f:
			p_file << "RAR" << std::endl;
			break;
		case 0x20:
			p_file << "-" << std::endl;
			break;
		case 0x21:
			opBytes = 3;
			code += 2;
			p_file << "LXI " << std::hex << static_cast<unsigned>(*code) << ",D16" << std::dec << std::endl;
			break;
		case 0x22:
			opBytes = 3;
			p_file << "SHLD" << std::endl;
			break;
		case 0x23:
			p_file << "INX H" << std::endl;
			break;
		case 0x24:
			p_file << "INR H" << std::endl;
			break;
		case 0x25:
			p_file << "DCR H" << std::endl;
			break;
		case 0x26:
			opBytes = 2;
			code++;
			p_file << "MVI " << std::hex << static_cast<unsigned>(*code) << ",D8" << std::dec << std::endl;
			break;
		case 0x27:
			p_file << "DAA" << std::endl;
			break;
		case 0xc3:
			opBytes = 3;
			p_file << "JMP ";
			code += 2;
			p_file << std::hex << static_cast<unsigned>(*code);
			code -= 1;
			p_file << static_cast<unsigned>(*code) << std::dec << std::endl;
			break;
		case 0xc5:
			p_file << "PUSH B" << std::endl;
			break;
		case 0xd5:
			p_file << "PUSH D" << std::endl;
			break;
		case 0xe5:
			p_file << "PUSH H" << std::endl;
			break;
		case 0xf5:
			p_file << "PUSH PSW" << std::endl;
			break;
		default:
			p_file << "Op code currently not supported" << std::endl;
	}		

	p_pc += opBytes;	



}

	
using namespace std;

int main(int argc, const char* argv[]) {
	
	ifstream ifile;
	ifile.open(argv[1], ios::binary | ios::in);
	
	//get file size
	ifile.seekg(0, ifile.end);
	int fileSize = ifile.tellg();
	ifile.seekg(0, ifile.beg);





	
	char* currentByte = new char[fileSize];
	void* byteAddress;
	byte* byteReader;


	for (int i=0; i<fileSize; i++) {
		ifile.read(&currentByte[i], 1);	
	}

	byteAddress = currentByte;
	byteReader = static_cast<byte*>(byteAddress);

	ofstream ofile;
	ofile.open(argv[2]);	
	int pc = 0;
	while (pc < fileSize) {
		Disassemble(byteReader, pc, ofile);	
	}
		
	ofile.close();
	
	return 0;
}
