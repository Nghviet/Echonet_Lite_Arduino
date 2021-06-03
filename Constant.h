#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#pragma once

#define UDP_MAX_PACKET_SIZE 1000

//EchoFrame
#define MIN_FRAME_SIZE 	12

#define EHD1 			0x10
#define EHD2 			(byte)0x81

#define ESV_SETI 		0x60
#define ESV_SETC 		0x61
#define ESV_GET  		0x62
#define ESV_INF_REQ		0x63

#define ESV_SET_RES 	0x71
#define ESV_GET_RES 	0x72
#define ESV_INF 		0x73

#define ESV_INFC 		0x74
#define ESV_INFC_RES	0x7A

#define ESV_SETI_SNA	0x50
#define ESV_SETC_SNA	0x51
#define ESV_GET_SNA		0x52
#define ESV_INF_SNA		0x53

#define ESV_SET_NO_RES	0x70

#define ESV_SET_GET		0x6E
#define ESV_SET_GET_RES	0x7E
#define ESV_SET_GET_SNA	0x5E

#define ESV_UNKNOWN 0x00

#define PORT 3610

//Profile Object
#define EPC_FAULT_STATUS 							(byte)0x88
#define EPC_MANUFACTURER_CODE 						(byte)0x8A
#define EPC_PLACE_OF_BUSINESS_CODE 					(byte)0x8B
#define EPC_PRODUCT_CODE 							(byte)0x8C
#define EPC_SERIAL_NUMBER 							(byte)0x8D
#define EPC_DATE_OF_MANUFACTURE 					(byte)0x8E
#define EPC_STATUS_CHANGE_ANNOUNCEMENT_PROPERTY_MAP (byte)0x9D
#define EPC_SET_PROPERTY_MAP 						(byte)0x9E
#define EPC_GET_PROPERTY_MAP 						(byte)0x9F

#define EPC_INSTANCE_LIST_NOTIFICATION				(byte)0xD5

typedef void (*fptr)(byte, byte*);

#endif