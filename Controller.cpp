#include "Controller.h"

Controller::Controller() {

}

Controller::Controller(WiFiUDP *_udp) {
	Controller();
	udp = _udp;
	WiFi.macAddress(macAddress);
}

Controller::~Controller() {

}

void Controller::addObject(EchoObject* object) {
	object->addProperty((byte)0xD8, 6, macAddress, NULL);
	objects[convert(object->getClassCode(), object->getInstanceCode())] = object;
}

void Controller::read() {
	int length = udp->parsePacket();
	if(length) {
		int len = udp->read(buffer,UDP_MAX_PACKET_SIZE);
		EchoFrame frame(buffer);
		//Serial.println(shortToHex(frame.getDstClassCode()).c_str());
		//Serial.println(byteToHex(frame.getDstInstanceCode()).c_str());
		EchoObject *object = objects[convert(frame.getDstClassCode(), frame.getDstInstanceCode())];
		
		if(object == NULL) return;
		
		byte resESV;
		switch(frame.getESV()) {
			case ESV_SETI: 
				resESV = ESV_SET_NO_RES;
				break;
			case ESV_SETC: 
				resESV = ESV_SET_RES;
				break;
			case ESV_GET:
				resESV = ESV_GET_RES;
				break;
			case ESV_INF_REQ:
				resESV = ESV_INF;
				break;
			case ESV_INFC:
				resESV = ESV_INFC_RES;
				break;
			case ESV_SET_GET:
				resESV = ESV_SET_GET_RES;
				break;
			default:
				resESV = ESV_UNKNOWN;
				break;
		}

		if(resESV == ESV_UNKNOWN) return;

		EchoFrame response(frame.getDstClassCode(), frame.getDstInstanceCode(), 
						   frame.getSrcClassCode(), frame.getSrcInstanceCode(), 
						   resESV, frame.getTID());

		std::vector<EchoProperty> propeties = frame.getProperties();


		for(int i = 0; i < propeties.size() ; i ++) {
			byte epc = propeties[i].epc;
			byte pdc = propeties[i].pdc;
			byte* edt = propeties[i].edt;

			fptr function = object->getFunction(epc);
			switch(frame.getESV()) {
				case ESV_SETI: case ESV_SETC:
					if( object -> setProperty(epc, pdc, edt) && function != NULL) {
						response.addProperty(epc, 0, NULL);
						function(pdc, edt);
					}
					else response.addProperty(epc, pdc, edt);
					break;
				case ESV_GET: case ESV_INF_REQ:
					response.addProperty(epc, 
										 object -> getPropertyLength(epc), 
										 object -> getPropertyStore(epc));
					break;

				case ESV_INFC:
					//Later
					break;
			}
		}
		if(udp->destinationIP().toString() == "224.0.23.0") {
			if(!udp->beginPacketMulticast(udp->destinationIP(), PORT, WiFi.localIP(), 10)) {
				return;
			}
		}
		else 
		if(!udp->beginPacket(udp->remoteIP(), udp->remotePort())) {
			return;
		} 
		response.toArray(buffer);
		//for(int i=0;i<25;i++) Serial.print(byteToHex(buffer[i]).c_str());
		//Serial.println();
		udp->write(buffer, UDP_MAX_PACKET_SIZE);
		udp->endPacket();
	}
}

void Controller::start() {
	EchoObject* nodeProfile = new EchoObject((short) 0x0EF0, 1);

	int length = objects.size();
	byte objectCode[3 * length + 1];
	objectCode[0] = (byte) length;
	int counter = 1;
	for(std::map<int, EchoObject*>::const_iterator it = objects.begin(); it != objects.end(); it++) {
		short classCode = it->second->getClassCode();
		byte instanceCode = it->second->getInstanceCode();

		
		objectCode[counter] = (byte) (classCode >> 8);
		objectCode[counter + 1] = (byte) (classCode & 0xFF);
		objectCode[counter + 2] = instanceCode;

/*
		Serial.println("-------");
		Serial.println(shortToHex(classCode).c_str());
		Serial.println(byteToHex(instanceCode).c_str());
		Serial.println(byteToHex(objectCode[counter]).c_str());
		Serial.println(byteToHex(objectCode[counter + 1]).c_str());
		Serial.println(byteToHex(objectCode[counter + 2]).c_str());
*/
		counter += 3;
	}

	nodeProfile->addProperty(EPC_INSTANCE_LIST_NOTIFICATION, length * 3 + 1, objectCode, NULL);
	addObject(nodeProfile);
}
