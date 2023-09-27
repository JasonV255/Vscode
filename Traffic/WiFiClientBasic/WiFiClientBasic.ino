#include <ESP8266WiFi.h>
int port=8080;
WiFiServer server(port);

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin("Gaugaugau", "abc123!!!");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.print("\nOn port:");
  Serial.print(port);
     
}

void loop() {
  WiFiClient client = server.available();
  if(client) 
  {
    if(client.connected())
    {
      Serial.println("\nClient Connected");
    }
    while(client.connected())
    {
      while(client.available()>0)
      {
        Serial.write(client.read());
      }
    client.stop();
    Serial.println("Disconnected");
    }
  }
}