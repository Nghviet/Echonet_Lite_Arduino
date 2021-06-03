#ifndef __ECHOPROPERTY_H__
#define __ECHOPROPERTY_H__

#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <map>
#include <string>
#include <vector>


#include "Utility.h"
#include "Constant.h"

class EchoProperty {
public:
	byte epc;
	byte pdc;
	byte* edt;

	EchoProperty();

	~EchoProperty();

	EchoProperty(byte epc, byte pdc, byte* edt);

	EchoProperty(byte epc);

	std::string toString();
};

#endif