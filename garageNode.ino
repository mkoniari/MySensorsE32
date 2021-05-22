//#include <Streaming.h>
#define MY_DEBUG

// Use a bit lower baudrate for serial prints on ESP8266 than default in MyConfig.h
#define MY_BAUD_RATE 9600
#define MY_NODE_ID 1
#define MY_RADIO_E32

#define MYLORA_E32_RX_PIN (9)
#define MYLORA_E32_TX_PIN (8)
#define MYLORA_32_AUX_PIN (7)

// Wait times
#define LONG_WAIT 2000
#define SHORT_WAIT 1000

#define SKETCH_NAME "GarageNodeScetch"
#define SKETCH_VERSION "v0.1"


#include <MySensors.h>

#define OPEN 1
#define CLOSE 0
#define ID_S_DOOR1            10
#define ID_S_DOOR2            11
#define ID_S_DOOR3            12
#define ID_S_CUSTOM           99

MyMessage msgDOOR1(ID_S_DOOR1, V_TRIPPED);
MyMessage msgDOOR2(ID_S_DOOR2, V_TRIPPED);
MyMessage msgDOOR3(ID_S_DOOR3, V_TRIPPED);
MyMessage msg_S_CUSTOM_1(ID_S_CUSTOM,V_VAR1);
MyMessage msg_S_CUSTOM_2(ID_S_CUSTOM,V_VAR2);
MyMessage msg_S_CUSTOM_3(ID_S_CUSTOM,V_VAR3);
MyMessage msg_S_CUSTOM_4(ID_S_CUSTOM,V_VAR4);
MyMessage msg_S_CUSTOM_5(ID_S_CUSTOM,V_VAR5);

bool metric = true;

uint8_t value = OPEN;


void presentation()
{
  //Send Sketch Info
  Serial.print("Send Sketch Info: ");
  sendSketchInfo(SKETCH_NAME, SKETCH_VERSION);
  Serial.print(SKETCH_NAME);
  Serial.println(SKETCH_VERSION);
  sleep(SHORT_WAIT);
  // Get controller configuration
  Serial.print("Get Config: ");
  metric = getControllerConfig().isMetric;
  Serial.println(metric ? "Metric":"Imperial");
  sleep(SHORT_WAIT);
  // Register all sensors to gw (they will be created as child devices)
  Serial.println("Presenting Nodes");
  Serial.println("________________");
  Serial.println("  ID_S_DOOR1");
  present(ID_S_DOOR1, S_DOOR, "Inside Door");
  sleep(SHORT_WAIT);
  Serial.println("  ID_S_DOOR2");
  present(ID_S_DOOR2, S_DOOR, "Outside Door");
  sleep(SHORT_WAIT);
  Serial.println("  ID_S_DOOR3");
  present(ID_S_DOOR3, S_DOOR, "Outside Door 2");
  sleep(SHORT_WAIT);
  Serial.println("  S_CUSTOM");
  present(ID_S_CUSTOM,S_CUSTOM,"Other Stuff");
  sleep(SHORT_WAIT);
  Serial.println("________________");
 
}

void loop()
{
  value = random(2);
  value = value == OPEN ? CLOSE : OPEN;
  send(msgDOOR1.set(value));
  sleep(LONG_WAIT);
  send(msgDOOR2.set(value));
  sleep(LONG_WAIT);
  requestTime(); 
  sleep(LONG_WAIT);
  send(msgDOOR3.set(!value));
  sleep(LONG_WAIT);
  custom();
  //rest for a while
  sleep(LONG_WAIT*5);
}

void custom()
{
  int randNumber = random(0,101);
  Serial.print("Custom value is: " );
  Serial.println(randNumber);

  send(msg_S_CUSTOM_1.set(randNumber));
  sleep(LONG_WAIT);
  send(msg_S_CUSTOM_2.set(randNumber/2));
  sleep(LONG_WAIT);
  send(msg_S_CUSTOM_3.set(randNumber+randNumber));
  sleep(LONG_WAIT);
  send(msg_S_CUSTOM_4.set(randNumber*randNumber));
  sleep(LONG_WAIT);
  send(msg_S_CUSTOM_5.set(randNumber));
  sleep(LONG_WAIT);
}
