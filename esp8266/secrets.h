
#include <pgmspace.h>
 
#define SECRETS
 
const char WIFI_SSID[] = "*************";    //add ur wifi name               
const char WIFI_PASSWORD[] = "************"; // add ur wifi password           
 
#define THINGNAME "***********"//add ur thing name 
 
float TIME_ZONE = 5.5; //NYC(USA): -5 UTC
 
const char MQTT_HOST[] = "************";//add ur endpoint
 
 
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";
 
 
// Copy contents from XXXXXXXX-certificate.pem.crt here ▼
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)KEY";
 
 
// Copy contents from  XXXXXXXX-private.pem.key here ▼
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----

-----END RSA PRIVATE KEY-----
)KEY";
