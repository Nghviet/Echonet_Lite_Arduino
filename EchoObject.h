#ifndef __ECHOOBJECT_H__
#define __ECHOOBJECT_H__

#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <map>
#include <string>
#include <vector>


#include "Utility.h"
#include "Constant.h"

class EchoObject {
protected:
	short classCode;
	byte instanceCode;

	std::map<byte, byte> length;
	std::map<byte, byte*> storage;
	std::map<byte, fptr> functions;
public:

	EchoObject();

	EchoObject(short _classCode, byte _instanceCode);

	~EchoObject();

	short getClassCode();

	byte getInstanceCode();

	void addProperty(byte epc, int length, byte initValue[], fptr function);

	bool setProperty(byte epc, byte length, byte* data);

	byte* getPropertyStore(byte epc);

	byte getPropertyLength(byte epc);

	fptr getFunction(byte epc);

	std::string toString();
};

#endif