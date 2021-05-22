//#include <Streaming.h>
#include <SoftwareSerial.h>
#include "LoRa_E32.h"


unsigned char _nodeId;
SoftwareSerial mySerial(MYLORA_E32_RX_PIN, MYLORA_E32_TX_PIN); // RX, TX
LoRa_E32 e32ttl100(&mySerial, MYLORA_E32_AUX_PIN);
//LoRa_E32 e32ttl100(9,8,7);


bool transportInit(void)
{
	e32ttl100.begin();
	return true;
}

bool transportSend(const uint8_t to, const void* data, const uint8_t len, const bool noACK)
{
	
	(void)noACK;	// not implemented
	ResponseStatus rs = e32ttl100.sendMessage(data, len);
	return rs.code ==1;	
}

void transportSetAddress(const uint8_t address)
{
	_nodeId = address;	
}

uint8_t transportGetAddress(void)
{
	return _nodeId;
}

bool transportDataAvailable(void)
{
	return e32ttl100.available()>1;
}

bool transportSanityCheck(void)
{
	// not implemented yet
	return true;
}

uint8_t transportReceive(void* data)
{
	if (transportDataAvailable()) {
    ResponseContainer rc = e32ttl100.receiveMessageUntil('\r'); //
		if (rc.status.code == 1) {      
		memcpy(data,rc.data.c_str(),rc.data.length());
		return rc.data.length();
		}
	}
	return (0);	
}

void transportPowerDown(void)
{
	// Nothing to shut down here
}

void transportPowerUp(void)
{
	// not implemented
}

void transportSleep(void)
{
	// not implemented
}

void transportStandBy(void)
{
	// not implemented
}

int16_t transportGetSendingRSSI(void)
{
	// not implemented
	return INVALID_RSSI;
}

int16_t transportGetReceivingRSSI(void)
{
	// not implemented
	return INVALID_RSSI;
}

int16_t transportGetSendingSNR(void)
{
	// not implemented
	return INVALID_SNR;
}

int16_t transportGetReceivingSNR(void)
{
	// not implemented
	return INVALID_SNR;
}

int16_t transportGetTxPowerPercent(void)
{
	// not implemented
	return static_cast<int16_t>(100);
}

int16_t transportGetTxPowerLevel(void)
{
	// not implemented
	return static_cast<int16_t>(100);
}

bool transportSetTxPowerPercent(const uint8_t powerPercent)
{
	// not possible
	(void)powerPercent;
	return false;
}
