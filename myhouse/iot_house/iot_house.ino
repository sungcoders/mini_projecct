#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <FS.h>

IPAddress staticIP(192,168,1,98);
IPAddress gateway(192,168,1,1);
IPAddress subnet (255,255,255,0);
const char* ssid = "NGOCTRINH";
const char* password = "NGOCTRINH";

#define DHTPIN 5    
#define DHTTYPE    DHT22    
DHT dht(DHTPIN, DHTTYPE);

float t = 0.0;
float h = 0.0;
String ledState;

AsyncWebServer server(80);
unsigned long previousMillis = 0;    
const long interval = 10000;  

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
    <html lang="vi"></html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=0.5">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <title>SMART HOME MINI</title>
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
     background-color: rgb(236, 236, 236);
    }
    h2 { 
        font-size: 3.0rem; 
        color: blueviolet;

        }
    p { font-size: 3.0rem; 
    }
    .units { font-size: 40px; color:rgb(68, 0, 204);}
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
    .b{width: 180px;height: 60px;font-size: 25px;color: #FFF;background-color:#00fa08;border-radius: 10px;color: rgb(59, 0, 115); font-weight: bold;}
    .t{width: 180px;height: 60px;font-size: 25px;color: #FFF;background-color:red;border-radius: 10px;color: rgb(59, 0, 115); font-weight: bold;}


  </style>
</head>
<body>
  <h2><span style=" padding: 10px; border-style: double; background-color: linen;">★彡SMART HOME彡★ </span></h2>
  <p><span style="border-style: outset; background-color:rgb(182, 180, 240);">
    <i class="fas fa-thermometer-half" style="color:red;"></i> 
    <span class="dht-labels">༺NHIỆT ĐỘ: ༻</span> 
    <span id="temperature" style="color:red;">★ NHIỆT ĐỘ:  </span>
    <sup class="units">&deg;C☀</sup>
  </span></p>
  <p><span style="border-style: outset; background-color: rgb(182, 180, 240);">
    <i class="fas fa-tint" style="color:blue;"></i> 
    <span class="dht-labels">꧁༺ĐỘ ẨM: ༻꧂</span>
    <span id="humidity" style="color: blue;">★ ĐỘ ẨM:  </span>
    <sup class="units">%❅</sup>
  </span></p>
  <div style="width: 700px;height: auto;margin: 0 auto;margin-top: 30px">
  <table align="center">
    <h3 style="color: blue; font-size: 20px; font-family: 'Times New Roman', Times, serif; font-weight: bold;">(►.◄) <i><u> NHẤN CÁC NÚT PHÍA DƯỚI ĐỂ BẬT THIẾT BỊ CỦA BẠN </u></i> (►.◄)</h3>
    <tr>
    <td><a href='/bat1'><button class='b'>✅ BẬT 1</button></a><td>
    <td><a href='/tat1'><button class='t'>TẮT 1 ☠️</button></a><td>
      <tr>
    <tr>
      <td><a href='/bat2'><button class='b'>✅ BẬT 2</button></a><td>
      <td><a href='/tat2'><button class='t'>TẮT 2 ☠️</button></a><td>
    <tr>
  </table>
</div>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 2000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 2000 ) ;
</script>
</html>)rawliteral";


//void bat1() {
//  digitalWrite(2,HIGH);
//      Serial.println("BAT DEN");
//    Serial.println(digitalRead(2));
//    request->send_P(200, "text/html", index_html, processor);
//  }

//----------------------------------CHUONG TRINH------------------------
String processor(const String& var){
   if(var == "STATE"){
    if(digitalRead(2)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;}
 else if(var == "TEMPERATURE"){
    return String(t);
  }
  else if(var == "HUMIDITY"){
    return String(h);
  }
  return String();
}

void setup(){
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin(ssid, password);
  WiFi.config(staticIP,gateway,subnet);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, index_html, String(), false, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(t).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(h).c_str());
  });
   server.on("/bat1", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(2, LOW);
    Serial.println("BAT DEN");
    Serial.println(digitalRead(2));    
    request->send(SPIFFS, index_html, String(), false, processor);
  });
   server.on("/tat1", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(2, HIGH);
    Serial.println("TAT DEN");
    Serial.println(digitalRead(2));     
    request->send(SPIFFS, index_html, String(), false, processor);
  });
// server.on("/bat1",bat1 );
// server.on("/tat1", HTTP_GET, digitalWrite(2,LOW)){
//    
//    Serial.println("TAT DEN");
//    Serial.println(digitalRead(2));
//    request->send_P(200, "text/html", index_html, processor);
//  }
// server.on("/bat2", bat2);
// server.on("/tat2", tat2);

  server.begin();
} // end setup
 
void loop(){  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
//    float newT = dht.readTemperature();
    float newT = 30.0;
    if (isnan(newT)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      t = newT;
      Serial.println(t);
    }
//    float newH = dht.readHumidity();
    float newH = 25.0;
    if (isnan(newH)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      h = newH;
      Serial.println(h);
    }
  }
}
