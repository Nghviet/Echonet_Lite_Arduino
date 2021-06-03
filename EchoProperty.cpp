#include "EchoProperty.h"

EchoProperty::EchoProperty() {
	epc = 0;
	pdc = 0;
}

EchoProperty::EchoProperty(byte _epc, byte _pdc, byte* _edt) {
	epc = _epc;
	pdc = _pdc;
	edt = (byte*) malloc(pdc);
	for(int i=0;i<(unsigned byte)pdc; i++) edt[i] = _edt[i];
}

EchoProperty::~EchoProperty() {

}

EchoProperty::EchoProperty(byte _epc) {
	epc = _epc;
	pdc = 0;
}

std::string EchoProperty::toString() {
	std::string value = "	EchoProperty : {\n";
	value += "		epc : " + byteToHex(epc) + "\n";
	value += "		pdc : " + byteToHex(pdc) + "\n";
	if(pdc != 0) {
		value += "		edt : ";
		for(int i=0;i<(unsigned byte)pdc;i++) value += byteToHex(edt[i]);
		value += "\n";
	}
	value += "	}";
	return value;
}