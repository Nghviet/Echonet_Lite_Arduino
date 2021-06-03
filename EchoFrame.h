#ifndef __ECHOFRAME_H__
#define __ECHOFRAME_H__

#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <map>
#include <string>
#include <vector>


#include "Utility.h"
#include "Constant.h"
#include "EchoProperty.h"

class EchoFrame {
protected:
	short mTID;
	byte mESV;

	
	short mSrcEchoClassCode;
	byte mSrcEchoInstanceCode;
	short mDstEchoClassCode;
	byte mDstEchoInstanceCode;

	std::vector<EchoProperty> mPropertyList;
public:

	EchoFrame();

	EchoFrame(short srcEchoClassCode, byte srcEchoInstanceCode, short dstEchoClassCode, byte dstEchoInstanceCode, byte esv, short mTID);

	EchoFrame(byte* buffer);

	~EchoFrame();

	std::vector<EchoProperty> getProperties();

	byte getESV();

	byte* toArray();

	void toArray(byte* buffer);

	void addProperty(byte epc, byte edt[]);

	void addProperty(byte epc, byte pdc, byte* edt);

	short getSrcClassCode();

	byte getSrcInstanceCode();

	short getDstClassCode();

	byte getDstInstanceCode();

	std::string toString();

	short getTID();
};

#endif