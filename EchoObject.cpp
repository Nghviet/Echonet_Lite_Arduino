#include "EchoObject.h"

EchoObject::EchoObject() {
	
}

EchoObject::EchoObject(short _classCode, byte _instanceCode) {
	classCode = _classCode;
	instanceCode = _instanceCode;
}

EchoObject::~EchoObject() {

}

void EchoObject::addProperty(byte _epc, int _length, byte _initValue[], fptr function) {
	byte* mem = (byte*)malloc(_length);
	if (_initValue != NULL) for(int i = 0 ; i < _length ; i++) mem[i] = _initValue[i];
	length[_epc] = _length;
	storage[_epc] = mem;
	functions[_epc] = function;
}

bool EchoObject::setProperty(byte _epc, byte _length, byte* _data) {
	if(length[_epc] != _length || _length == 0) return false;
	for( int i = 0 ; i < _length ; i++ ) storage[_epc][i] = _data[i];
	return true;
}

byte* EchoObject::getPropertyStore(byte epc) { return storage[epc]; }

byte EchoObject::getPropertyLength(byte epc) { return length[epc]; }

short EchoObject::getClassCode() { return classCode; }

byte EchoObject::getInstanceCode() { return instanceCode; }

fptr EchoObject::getFunction(byte epc) { return functions[epc]; }

std::string EchoObject::toString() {
	std::string value = "EchoObject {\n";
	value += "	Class Code :" + shortToHex(classCode) + "\n";
	value += "	Instance Code :" + byteToHex(instanceCode) + "\n";
	value += "}";

	return value;
}
