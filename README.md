# MySensorsE32
Custom MySensors [https://github.com/mysensors/MySensors] modifications for the ΕΒΥΤΕ E22-400T30D [https://www.ebyte.com/en/product-view-news.html?id=939] module (LoRa SX1278 SX1276 433MHz rf Module)

Tested with MySensors v.2.3.2 and LoRa_E32_Series_Library [https://github.com/xreef/LoRa_E32_Series_Library] v1.5.0

## Insctruction on how to use ebyte e32 with my sensors
1. LoRa_E32_Series_Library
    * Download  LoRa_E32_Series_Library from [https://github.com/xreef/LoRa_E32_Series_Library]
    * Place LoRa_E32.cpp, LoRa_E32.h and includes directory (statesNaming.h) in folder \MySensors\hal\transport\E32\driver
    (create dir if needed)
2. E32 Transport for MySensors
    * Place file MyTransportE32.cpp in folder \MySensors\hal\transport\E32\
3. MySensors config files modifications. 
Since we define a new transport called 'MY_RADIO_E32' we have to modify the following files
    1. MyConfig.h
    Add the following definitions
    ```c
    #define MYLORA_DEFAULT_E32_RX_PIN (9)
    #define MYLORA_DEFAULT_E32_TX_PIN (8)
    #define MYLORA_DEFAULT_E32_AUX_PIN (7)
    #define MYLORA_DEFAULT_E32_AUX_PIN (10)
    #define MYLORA_DEFAULT_E32_AUX_PIN (11)
    #ifndef MYLORA_E32_RX_PIN 
    #define MYLORA_E32_RX_PIN  MYLORA_DEFAULT_E32_RX_PIN
    #endif
    #ifndef MYLORA_E32_TX_PIN  
    #define MYLORA_E32_TX_PIN  MYLORA_DEFAULT_E32_TX_PIN
    #endif
    #ifndef MYLORA_32_AUX_PIN  
    #define MYLORA_32_AUX_PIN MYLORA_DEFAULT_E32_AUX_PIN
    #endif
    #ifndef MYLORA_E32_M0_PIN  
    #define MYLORA_E32_M0_PIN MYLORA_DEFAULT_E32_M0_PIN
    #endif
    #ifndef MYLORA_E32_M1_PIN  
    #define MYLORA_E32_M1_PIN MYLORA_DEFAULT_E32_M1_PIN
    #endif
    ```
    These are the module RX,TX and AUX pin connections.
    2. MyConfig.h
    
    Change line
    ```c
    // TRANSPORT INCLUDES
    #if defined(MY_RADIO_RF24) || defined(MY_RADIO_NRF5_ESB) || defined(MY_RADIO_RFM69) || defined(MY_RADIO_RFM95) || defined(MY_RS485)
    ```
    to 
     ```c
    // TRANSPORT INCLUDES
    #if defined(MY_RADIO_RF24) || defined(MY_RADIO_NRF5_ESB) || defined(MY_RADIO_RFM69) || defined(MY_RADIO_RFM95) || defined(MY_RS485) || defined(MY_RADIO_E32) || defined(MY_RADIO_ETH)
    ```
    Also at the section // Transport drivers include the MyTransportE32.cpp driver
    For example change from
     ```c
   // Transport drivers
    #if defined(MY_RADIO_RF24)
    #include "hal/transport/RF24/driver/RF24.cpp"
    #include "hal/transport/RF24/MyTransportRF24.cpp"
    ```
    to 
     ```c
    // Transport drivers
    #if defined(MY_RADIO_RF24)
    #include "hal/transport/RF24/driver/RF24.cpp"
    #include "hal/transport/RF24/MyTransportRF24.cpp"
    #elif defined(MY_RADIO_E32)
    #include "hal/transport/E32/MyTransportE32.cpp"
    ```
    
    3. MyCapabilities.h
    Optional step in // Transport section
    
    Change line
    ```c
    #if defined(MY_RADIO_RF24) || defined(MY_RADIO_NRF5_ESB)
    #define MY_CAP_RADIO "N"
    ```
    to 
     ```c
    #if defined(MY_RADIO_RF24) || defined(MY_RADIO_NRF5_ESB)
    #define MY_CAP_RADIO "N"
    #elif defined(MY_RADIO_E32)
    #define MY_CAP_RADIO "E"
    ```
    4. MySensorsCore.cpp
    
    Optional step add a 500ms delay in function sendSketchInfo
    
    Change 
    ```c
     bool sendSketchInfo(const char *name, const char *version, const bool requestEcho)
    {
	    bool result = true;
    	if (name) {
		    result &= _sendRoute(build(_msgTmp, GATEWAY_ADDRESS, NODE_SENSOR_ID, C_INTERNAL, I_SKETCH_NAME,
		                           requestEcho).set(name));
	    }
	    if (version) {
		    result &= _sendRoute(build(_msgTmp, GATEWAY_ADDRESS, NODE_SENSOR_ID, C_INTERNAL, I_SKETCH_VERSION,
		                           requestEcho).set(version));
	    }
	    return result;
    }
    ```
    to
    ```c
     bool sendSketchInfo(const char *name, const char *version, const bool requestEcho)
    {
	    bool result = true;
    	if (name) {
		    result &= _sendRoute(build(_msgTmp, GATEWAY_ADDRESS, NODE_SENSOR_ID, C_INTERNAL, I_SKETCH_NAME,
		                           requestEcho).set(name));
	    }
	    if (version) {
		    wait(500);
		    result &= _sendRoute(build(_msgTmp, GATEWAY_ADDRESS, NODE_SENSOR_ID, C_INTERNAL, I_SKETCH_VERSION,
		                           requestEcho).set(version));
	    }
	    return result;
    }
    ```
    
    5. Make sure to include the new transport (E32) to your nodes/ gateway scketches
    ```c
    #define MY_RADIO_E32
    ```

## Example
Sample files garageNode.ino and E32Gateway.ino

## Tips ##
Make sure to include  a short delay betwwen communication attemps within your node
e.g.
```c
#define SHORT_WAIT 1000
send(msg);
sleep(SHORT_WAIT);
send(msg);
```
