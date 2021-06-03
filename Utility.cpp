#include "Utility.h"

std::string lookup[] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};

std::string shortToHex(short value) {
	return byteToHex((byte)(value >> 8)) + byteToHex((byte)(value & 0xFF));
}

std::string shortToString(short value) {
	return "";
}

std::string byteToHex(byte value) {
	std::string first = lookup[(int)(value >> 4)];
	std::string second = lookup[value & 0xF];
	return first + second;
}

std::string byteToString(byte value) {
	return "";
}

unsigned short fromBytes(byte byte1, byte byte2) {
	return (byte1 << 8) | byte2;
}

int convert(short classCode, byte instanceCode) {
	return(int) ((classCode<<8) | instanceCode);
}