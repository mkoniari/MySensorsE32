
// Enable debug prints to serial monitor
#define MY_DEBUG
//#define MY_BAUD_RATE 9600

#define MY_RADIO_E32
#define MYLORA_E32_RX_PIN (9)
#define MYLORA_E32_TX_PIN (8)
#define MYLORA_32_AUX_PIN (7)
#define MY_GATEWAY_SERIAL
//#define MY_NODE_ID 0


#include <MySensors.h>

void setup()
{
	// Setup locally attached sensors
}

void presentation()
{
	// Present locally attached sensors
}

void loop()
{
	// Send locally attached sensor data here
}

/*void receive(const MyMessage & message)
{
  Serial.print("receive MyMessage: ");
  Serial.println(protocolMyMessage2Serial(message));
}*/
