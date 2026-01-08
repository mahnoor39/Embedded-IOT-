#include <WiFi.h>

// Network configuration
IPAddress staticIP(192, 168, 1, 103);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
WiFi.config(staticIP, gateway, subnet);
WiFi.begin("Merab", "31052008");

while (WiFi.status() != WL_CONNECTED) {
delay(500);
}
}