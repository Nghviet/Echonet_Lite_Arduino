#ifndef __UTILITY_H__
#define __UTILITY_H__
#pragma once

#include <Arduino.h>
#include <string>

std::string shortToString(short value);

std::string shortToHex(short value);

std::string byteToHex(byte value);

std::string byteToString(byte value);

unsigned short fromBytes(byte byte1, byte byte2);

int convert(short classCode, byte instanceCode);
#endif