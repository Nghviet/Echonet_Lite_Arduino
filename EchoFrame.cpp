#include "EchoFrame.h"

EchoFrame::EchoFrame() {
	mTID = 0;
	mESV = 0;
	mSrcEchoClassCode = 0;
	mSrcEchoInstanceCode = 0;
	mDstEchoClassCode = 0;
	mDstEchoInstanceCode = 0;
}

EchoFrame::EchoFrame(short _srcEchoClassCode, 
					 byte _srcEchoInstanceCode, 
					 short _dstEchoClassCode, 
					 byte _dstEchoInstanceCode, 
					 byte _esv,
					 short _mTID) {

	mTID = _mTID;
	mESV = _esv;
	mSrcEchoClassCode = _srcEchoClassCode;
	mSrcEchoInstanceCode = _srcEchoInstanceCode;
	mDstEchoClassCode = _dstEchoClassCode;
	mDstEchoInstanceCode = _dstEchoInstanceCode;
}

EchoFrame::EchoFrame(byte* buffer) {
	if(buffer[0] != EHD1 && buffer[1] != EHD2) return;
	
	mTID = fromBytes(buffer[2], buffer[3]);
	
	mSrcEchoClassCode = fromBytes(buffer[4], buffer[5]);
	mSrcEchoInstanceCode = buffer[6];
	
	mDstEchoClassCode = fromBytes(buffer[7], buffer[8]);
	mDstEchoInstanceCode = buffer[9];
	
	mESV = buffer[10];

	int opc = (int) (buffer[11] & 0xFF);

	int pointer = 12;

	for(int i = 0 ; i < opc ; i++) {
		byte epc = buffer[pointer];
		int pdc = (int) (buffer[pointer + 1] & 0xFF);
		pointer += 2;
		byte* edt = (byte*) malloc(pdc);
		for(int j = 0 ; j < pdc ; j++) edt[j] = buffer[pointer + j];
		mPropertyList.push_back(EchoProperty(epc,pdc,edt));
		pointer +=  pdc;
	}
}

EchoFrame::~EchoFrame() {

}

std::vector<EchoProperty> EchoFrame::getProperties() {
	return mPropertyList;
}

byte EchoFrame::getESV() { return mESV; }

void EchoFrame::toArray(byte* buffer) {
	buffer[0] = EHD1;
	buffer[1] = EHD2;

	buffer[2] = (byte) (mTID >> 8);
	buffer[3] = (byte) (mTID & 0xFF);

	buffer[4] = (byte) (mSrcEchoClassCode >> 8);
	buffer[5] = (byte) (mSrcEchoClassCode & 0xFF);
	buffer[6] = mSrcEchoInstanceCode;

	buffer[7] = (byte) (mDstEchoClassCode >> 8);
	buffer[8] = (byte) (mDstEchoClassCode & 0xFF);
	buffer[9] = mDstEchoInstanceCode;

	buffer[10] = mESV;

	buffer[11] = (byte) mPropertyList.size();

	int pointer = 12;

	for(int i = 0 ; i < mPropertyList.size() ; i ++) {
		EchoProperty property = mPropertyList[i];
		buffer[pointer] = property.epc;
		int size = (int) (property.pdc & 0xFF);
		buffer[pointer + 1] = (byte) size;
		for(int j = 0 ; j < size ; j++ ) {
			buffer[pointer + 2 + j] = property.edt[j];
		}
		pointer += 2 + size;
	}

	Serial.println();
}

void EchoFrame::addProperty(byte _epc, byte _edt[]) {
	byte pdc = 0;
	if(_edt != NULL) pdc = (byte)sizeof(_edt);
	mPropertyList.push_back(EchoProperty(_epc, pdc, _edt));
	switch(mESV) {
		case ESV_SET_NO_RES: case ESV_SETI_SNA:
			if(pdc != 0) {
				mESV = ESV_SETI_SNA;
			}
			break;
		case ESV_SET_RES: case ESV_SETC_SNA:
			if(pdc != 0) {
				mESV = ESV_SETC_SNA;
			}
			break;
		case ESV_GET_RES: case ESV_GET_SNA:
			if(pdc == 0) {
				mESV = ESV_GET_SNA;
			}
			break;
		case ESV_INF: case ESV_INF_SNA:
			if(pdc == 0) {
				mESV = ESV_INF_SNA;
			}
			break;
	}
}

void EchoFrame::addProperty(byte _epc, byte _pdc, byte* _edt) {
	byte pdc = 0;
	if(_edt != NULL) pdc = _pdc;
	mPropertyList.push_back(EchoProperty(_epc, pdc, _edt));
	switch(mESV) {
		case ESV_SET_NO_RES: case ESV_SETI_SNA:
			if(pdc != 0) {
				mESV = ESV_SETI_SNA;
			}
			break;
		case ESV_SET_RES: case ESV_SETC_SNA:
			if(pdc != 0) {
				mESV = ESV_SETC_SNA;
			}
			break;
		case ESV_GET_RES: case ESV_GET_SNA:
			if(pdc == 0) {
				mESV = ESV_GET_SNA;
			}
			break;
		case ESV_INF: case ESV_INF_SNA:
			if(pdc == 0) {
				mESV = ESV_INF_SNA;
			}
			break;
	}
}

std::string EchoFrame::toString() {
	std::string value = "EchoFrame : {\n";
	value += "	src : " + shortToHex(mSrcEchoClassCode) + byteToHex(mSrcEchoInstanceCode) + 
		   " -> dst : " + shortToHex(mDstEchoClassCode) + byteToHex(mDstEchoInstanceCode);
	value += "\n 	esv : " + byteToHex(mESV);
	value += "\n	tid : " + shortToHex(mTID);
	value += "\n	prop: [";

	for(EchoProperty property : mPropertyList) value += "\n" + property.toString();

	value += "]\n}";

	return value;
}

short EchoFrame::getSrcClassCode() { return mSrcEchoClassCode; }

byte EchoFrame::getSrcInstanceCode() { return mSrcEchoInstanceCode; }

short EchoFrame::getDstClassCode() { return mDstEchoClassCode; }

byte EchoFrame::getDstInstanceCode() { return mDstEchoInstanceCode; }

short EchoFrame::getTID() { return mTID; }
