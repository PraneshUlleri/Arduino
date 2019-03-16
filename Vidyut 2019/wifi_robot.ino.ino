#include <ESP8266WiFi.h>
 
const char* ssid = "RAVA";//Chane here your hostspot id
const char* password = "athirarudhra2114";//change here your hotspot password
 
int ledPin1 = 16; 
int ledPin2 = 5; 
int ledPin3 = 4; 
int ledPin4 = 0; 

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin1, OUTPUT);
  
  pinMode(ledPin2, OUTPUT);
  
  pinMode(ledPin3, OUTPUT);
  
  pinMode(ledPin4, OUTPUT);
  digitalWrite(ledPin2,LOW);
    digitalWrite(ledPin4,LOW);
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin3,LOW);
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
 
  
  if (request.indexOf("/cmd=front") != -1)  {
    digitalWrite(ledPin1,HIGH);
    digitalWrite(ledPin3,HIGH);
    digitalWrite(ledPin2,LOW);
    digitalWrite(ledPin4,LOW);
  }
  if (request.indexOf("/cmd=right") != -1)  {
    digitalWrite(ledPin1,HIGH);
    digitalWrite(ledPin3,LOW);
    digitalWrite(ledPin2,LOW);
    digitalWrite(ledPin4,LOW);
  }
  if (request.indexOf("/cmd=left") != -1)  {
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin3,HIGH);
    digitalWrite(ledPin2,LOW);
    digitalWrite(ledPin4,LOW);
  }
  if (request.indexOf("/cmd=back") != -1)  {
    digitalWrite(ledPin2,HIGH);
    digitalWrite(ledPin4,HIGH);
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin3,LOW);
  }
  if (request.indexOf("/cmd=stop") != -1)  {
    digitalWrite(ledPin2,LOW);
    digitalWrite(ledPin4,LOW);
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin3,LOW);
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css' integrity='sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u' crossorigin='anonymous'>");
  client.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css' integrity='sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp' crossorigin='anonymous'>");
  client.println("<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js' integrity='sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa' crossorigin='anonymous'></script>");
  client.println("</head>");
  client.println("<body>");
  client.println("<div class='container'>");
  client.println("<div class='row'>");
  client.println("<div class='md-col-2'></div>");
  client.println("<div class='md-col-8'>");
  client.println("<center><h2>www.beginnertopro.in</h2></center>");
  client.println("<center><h3>WiFi controlled Rc Car</h3></center>");
  client.print("<center><h4 style='color:red;'>Led pin is now: ");
 
  
  client.println("<br><br><center>");
  client.println("<a href=\"/cmd=front\"\"><button class='btn btn-primary'>FRONT</button></a>");
  client.println("<hr/>");
  client.println("<a href=\"/cmd=left\"\"><button class='btn btn-primary'>LEFT</button></a>'-------<a href=\"/cmd=stop\"\"><button class='btn btn-primary'>Stop</button></a>'------'<a href=\"/cmd=right\"\"><button class='btn btn-primary'>RIGHT</button></a>");
  client.println("<hr/>");
  client.println("<a href=\"/cmd=back\"\"><button class='btn btn-primary'>BACK</button></a><br />");
  client.println("</center></div>");
  client.println("<div class='md-col-2'></div>");
  client.println("</div>");
  client.println("</div>");

  client.println("</body>");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
