#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <map>
#include <string>
#include <vector>

#include "Utility.h"
#include "EchoObject.h"
#include "EchoFrame.h"
#include "Constant.h"

class Controller {
protected:
	WiFiUDP *udp;

	//IPAddress gateway;
	//short dstClassCode; // 0x0EF0 <- send only to gateway
	//byte dstInstanceCode; // if we seperate each thread to have different instance code <- recheck

	byte buffer[UDP_MAX_PACKET_SIZE];

	std::map<int, EchoObject*> objects;
	byte macAddress[6];
	bool started;
public:

	Controller();

	Controller(WiFiUDP *_udp);

	~Controller();

	void addObject(EchoObject *object);

	void read();

	void send(EchoFrame* frame);

	std::string toString();

	void start();

	bool setProperty(short classCode, byte instanceCode, byte _epc, byte _length, byte* _data);
};

#endif