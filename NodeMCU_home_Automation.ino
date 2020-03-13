#include <ESP8266WiFi.h>
 
const char* ssid = "Rahul";
const char* password = "";
 
int relay1 = D1; 
int relay2 = D2;
int relay3 = D3;
int relay4 = D4;

int value1 = LOW;
int value2 = LOW;
int value3 = LOW;
int value4 = LOW;

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, LOW);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay2, LOW);
  pinMode(relay3, OUTPUT);
  digitalWrite(relay3, LOW);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay4, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
  if (request.indexOf("/device1=ON") != -1)  {
    digitalWrite(relay1, HIGH);
    value1 = HIGH;
  }
  if (request.indexOf("/device1=OFF") != -1)  {
    digitalWrite(relay1, LOW);
    value1 = LOW;
  }

  if (request.indexOf("/device2=ON") != -1)  {
    digitalWrite(relay2, HIGH);
    value2 = HIGH;
  }
  if (request.indexOf("/device2=OFF") != -1)  {
    digitalWrite(relay2, LOW);
    value2 = LOW;
  }

  if (request.indexOf("/device3=ON") != -1)  {
    digitalWrite(relay3, HIGH);
    value3 = HIGH;
  }
  if (request.indexOf("/device3=OFF") != -1)  {
    digitalWrite(relay3, LOW);
    value3 = LOW;
  }

  if (request.indexOf("/device4=ON") != -1)  {
    digitalWrite(relay4, HIGH);
    value4 = HIGH;
  }
  if (request.indexOf("/device4=OFF") != -1)  {
    digitalWrite(relay4, LOW);
    value4 = LOW;
  }

 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0">"\"");
  client.println("<center>");
  client.println("<h1>");
  //client.print("<font color=\"Tomato""\">Raspi</font>");
  client.print("<font size=\"20""\" color=\"Tomato""\">Raspi</font>");
  //client.print("<font color=\"SlateBlue""\">Invent</font>");
  client.print("<font size=\"20""\" color=\"SlateBlue""\">Invent</font>");
  client.println("</h1>");
  client.println("<h2>");
  client.println("<br>");
  client.println("<br><br>");
  client.println("<a href=\"/device1=ON\"\"><button style=\"background-color:MediumSeaGreen;height:80px;width:100px\">Device1 ON </button></a>");
  client.println("<a href=\"/device1=OFF\"\"><button style=\"background-color:Tomato;height:80px;width:100px\">Device1 OFF </button></a>");
  client.print("<font color=\"SlateBlue""\">Device Status=</font>");
  if(value1 == HIGH) 
  {
    client.print("<font color=\"MediumSeaGreen""\">ON</font>");
  }
  else 
  {
    client.print("<font color=\"Tomato""\">OFF</font>");
  }
  client.println("<br />");

  client.println("<br>");
  client.println("<a href=\"/device2=ON\"\"><button style=\"background-color:MediumSeaGreen;height:80px;width:100px\">Device2 ON </button></a>");
  client.println("<a href=\"/device2=OFF\"\"><button style=\"background-color:Tomato;height:80px;width:100px\">Device2 OFF </button></a>");
  client.print("<font color=\"SlateBlue""\">Device Status=</font>");
  if(value2 == HIGH) 
  {
    client.print("<font color=\"MediumSeaGreen""\">ON</font>");
  }
  else 
  {
    client.print("<font color=\"Tomato""\">OFF</font>");
  }
  client.println("<br />");

  client.println("<br>");
  client.println("<a href=\"/device3=ON\"\"><button style=\"background-color:MediumSeaGreen;height:80px;width:100px\">Device3 ON </button></a>");
  client.println("<a href=\"/device3=OFF\"\"><button style=\"background-color:Tomato;height:80px;width:100px\">Device3 OFF </button></a>");
  client.print("<font color=\"SlateBlue""\">Device Status=</font>");
  if(value3 == HIGH) 
  {
    client.print("<font color=\"MediumSeaGreen""\">ON</font>");
  }
  else 
  {
   client.print("<font color=\"Tomato""\">OFF</font>");
  }
  client.println("<br />");
  
  client.println("<br>");
  client.println("<a href=\"/device4=ON\"\"><button style=\"background-color:MediumSeaGreen;height:80px;width:100px\">Device4 ON </button></a>");
  client.println("<a href=\"/device4=OFF\"\"><button style=\"background-color:Tomato;height:80px;width:100px\">Device4 OFF </button></a>");
  client.print("<font color=\"SlateBlue""\">Device Status=</font>");
  if(value4 == HIGH) 
  {
    client.print("<font color=\"MediumSeaGreen""\">ON</font>");
  }
  else 
  {
    client.print("<font color=\"Tomato""\">OFF</font>");
  }
  client.println("<br />");
  client.println("</h2>");
  client.println("</center>"); 
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
