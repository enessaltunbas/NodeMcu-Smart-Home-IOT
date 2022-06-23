#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>

const char* isim = "SSID";
const char* sifre = "PASS";

ESP8266WebServer server(80);


uint8_t role1pin = D3;
bool role1durum = false;

uint8_t role2pin = D5;
bool role2durum = false;

uint8_t role3pin = D2;
bool role3durum = false;

uint8_t role4pin = D1;
bool role4durum = false;


const int redLED = 12;   //D3
const int greenLED = 13; //D2
const int blueLED = 15;  //D1


void setup() {

  Serial.begin(115200);
  delay(100);
  pinMode(role1pin, OUTPUT);
  pinMode(role2pin, OUTPUT);
  pinMode(role3pin, OUTPUT);
  pinMode(role4pin, OUTPUT);


  pinMode(redLED, OUTPUT);
pinMode(greenLED, OUTPUT);
pinMode(blueLED, OUTPUT);

analogWrite(redLED, 0);
analogWrite(greenLED, 0);
analogWrite(blueLED, 0);


  WiFi.begin(isim, sifre);
  
  //////////////////////////////////////////////////////////////////////////////////
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  //////////////////////////////////////////////////////////////////////////////////
  
  role1durum = false;
  role2durum = false;
  role3durum = false;
  role4durum = false;

  server.on("/", baglandi);
  server.on("/role1ac", role1ac);
  server.on("/role1kapat", role1kapat);
  server.on("/role2ac", role2ac);
  server.on("/role2kapat", role2kapat);
  server.on("/role3ac", role3ac);
  server.on("/role3kapat", role3kapat);
  server.on("/role4ac", role4ac);
  server.on("/role4kapat", role4kapat);
  server.onNotFound(komutyok);

  server.begin();

}
void loop() {
  
  //////////////////////////////////////////////////////////////////////////////////
  ArduinoOTA.handle();
  //////////////////////////////////////////////////////////////////////////////////
  
  server.handleClient();
  if(role1durum)
  {digitalWrite(role1pin, LOW);}
  else
  {digitalWrite(role1pin, HIGH);}
  
  if(role2durum)
  {digitalWrite(role2pin, LOW);}
  else
  {digitalWrite(role2pin, HIGH);}

  if(role3durum)
  {digitalWrite(role3pin, LOW);}
  else
  {digitalWrite(role3pin, HIGH);}

  if(role4durum)
  {digitalWrite(role4pin, LOW);}
  else
  {digitalWrite(role4pin, HIGH);}
}

void baglandi() {
  String red = server.arg(0);
String green = server.arg(1);
String blue = server.arg(2);

if((red != "") && (green != "") && (blue != ""))
{
  analogWrite(redLED, 1023 - red.toInt());
  analogWrite(greenLED, 1023 - green.toInt());
  analogWrite(blueLED, 1023 - blue.toInt());
}
  server.send(200, "text/html", SendHTML(role1durum,role2durum,role3durum,role4durum)); 
}

void role1ac() {
  role1durum = true;
  server.send(200, "text/html", SendHTML(true,role2durum,role3durum,role4durum)); 
}

void role1kapat() {
  role1durum = false;
  server.send(200, "text/html", SendHTML(false,role2durum,role3durum,role4durum)); 
}

void role2ac() {
  role2durum = true;
  server.send(200, "text/html", SendHTML(role1durum,true,role3durum,role4durum)); 
}

void role2kapat() {
  role2durum = false;
  server.send(200, "text/html", SendHTML(role1durum,false,role3durum,role4durum)); 
}

void role3ac() {
  role3durum = true;
  server.send(200, "text/html", SendHTML(role1durum,role2durum,true,role4durum)); 
}

void role3kapat() {
  role3durum = false;
  server.send(200, "text/html", SendHTML(role1durum,role2durum,false,role4durum)); 
}

void role4ac() {
  role4durum = true;
  server.send(200, "text/html", SendHTML(role1durum,role2durum,role3durum,true)); 
}

void role4kapat() {
  role4durum = false;
  server.send(200, "text/html", SendHTML(role1durum,role2durum,role3durum,false)); 
}

void komutyok(){
  server.send(404, "text/plain", "Sayfa Bulunamadi");
}

  String SendHTML(bool role1drm,bool role2drm,bool role3drm,bool role4drm){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<meta http-equiv=\"Content-Type\" content=\"text/html;charset=UTF-8\">";
  ptr +="<title>Vital Yazılım</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px; margin-left: 0px; margin-bottom: 0px; margin-right: 0px; padding: 0px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>VTL Akıllı Ev Sistemi</h1>\n";
  ptr +="<br><br>\n";
  ptr +="<h2>Röle Kontrolleri</h2>\n";
  
   if(role1drm)
  {ptr +="<p id='role1'>Röle 1 Durum: AÇIK</p><a class=\"button button-off\" href=\"/role1kapat\">KAPAT</a>\n";}
  else
  {ptr +="<p id='role1'>Röle 1 Durum: KAPALI</p><a class=\"button button-on\" href=\"/role1ac\">AÇ</a>\n";}

  if(role2drm)
  {ptr +="<p id='role2'>Röle 2 Durum: AÇIK</p><a class=\"button button-off\" href=\"/role2kapat\">KAPAT</a>\n";}
  else
  {ptr +="<p id='role2'>Röle 2 Durum: KAPALI</p><a class=\"button button-on\" href=\"/role2ac\">AÇ</a>\n";}

  if(role3drm)
  {ptr +="<p id='role3'>Röle 3 Durum: AÇIK</p><a class=\"button button-off\" href=\"/role3kapat\">KAPAT</a>\n";}
  else
  {ptr +="<p id='role3'>Röle 3 Durum: KAPALI</p><a class=\"button button-on\" href=\"/role3ac\">AÇ</a>\n";}

  if(role4drm)
  {ptr +="<p id='role4'>Röle 4 Durum: AÇIK</p><a class=\"button button-off\" href=\"/role4kapat\">KAPAT</a>\n";}
  else
  {ptr +="<p id='role4'>Röle 4 Durum: KAPALI</p><a class=\"button button-on\" href=\"/role4ac\">AÇ</a>\n";}
    ptr +="<br><br>\n";
ptr +="<h2>RGB Led Kontolü</h2>\n";
ptr +="<center><div><canvas id='colorspace' style=\"width: 100%; height: 300px;\"></canvas></div></center>\n";

  ptr +="</body>\n";

ptr +="<script type='text/javascript'>\n";
ptr +="(function () {\n";
ptr +=" var canvas = document.getElementById('colorspace');\n";
ptr +=" var ctx = canvas.getContext('2d');\n";
ptr +=" function drawCanvas() {\n";
ptr +=" var colours = ctx.createLinearGradient(0, 0, window.innerWidth, 0);\n";
ptr +=" for(var i=0; i <= 360; i+=10) {\n";
ptr +=" colours.addColorStop(i/360, 'hsl(' + i + ', 100%, 50%)');\n";
ptr +=" }\n";
ptr +=" ctx.fillStyle = colours;\n";
ptr +=" ctx.fillRect(0, 0, window.innerWidth, window.innerHeight);\n";
ptr +=" var luminance = ctx.createLinearGradient(0, 0, 0, ctx.canvas.height);\n";
ptr +=" luminance.addColorStop(0, '#ffffff');\n";
ptr +=" luminance.addColorStop(0.05, '#ffffff');\n";
ptr +=" luminance.addColorStop(0.5, 'rgba(0,0,0,0)');\n";
ptr +=" luminance.addColorStop(0.95, '#000000');\n";
ptr +=" luminance.addColorStop(1, '#000000');\n";
ptr +=" ctx.fillStyle = luminance;\n";
ptr +=" ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);\n";
ptr +=" }\n";
ptr +=" var eventLocked = false;\n";
ptr +=" function handleEvent(clientX, clientY) {\n";
ptr +=" if(eventLocked) {\n";
ptr +=" return;\n";
ptr +=" }\n";
ptr +=" function colourCorrect(v) {\n";
ptr +=" return Math.round(1023-(v*v)/64);\n";
ptr +=" }\n";
ptr +=" var data = ctx.getImageData(clientX, clientY, 1, 1).data;\n";
ptr +=" var params = [\n";
ptr +=" 'r=' + colourCorrect(data[0]),\n";
ptr +=" 'g=' + colourCorrect(data[1]),\n";
ptr +=" 'b=' + colourCorrect(data[2])\n";
ptr +=" ].join('&');\n";
ptr +=" var req = new XMLHttpRequest();\n";
ptr +=" req.open('POST', '?' + params, true);\n";
ptr +=" req.send();\n";
ptr +=" eventLocked = true;\n";
ptr +=" req.onreadystatechange = function() {\n";
ptr +=" if(req.readyState == 4) {\n";
ptr +=" eventLocked = false;\n";
ptr +=" }\n";
ptr +=" }\n";
ptr +=" }\n";
ptr +=" canvas.addEventListener('click', function(event) {\n";
ptr +=" handleEvent(event.clientX, event.clientY, true);\n";
ptr +=" }, false);\n";
ptr +=" canvas.addEventListener('touchmove', function(event){\n";
ptr +=" handleEvent(event.touches[0].clientX, event.touches[0].clientY);\n";
ptr +="}, false);\n";
ptr +=" function resizeCanvas() {\n";
ptr +=" canvas.width = window.innerWidth;\n";
ptr +=" canvas.height = window.innerHeight;\n";
ptr +=" drawCanvas();\n";
ptr +=" }\n";
ptr +=" window.addEventListener('resize', resizeCanvas, false);\n";
ptr +=" resizeCanvas();\n";
ptr +=" drawCanvas();\n";
ptr +=" document.ontouchmove = function(e) {e.preventDefault()};\n";
ptr +=" })();\n";
ptr +="</script>\n";
  
  ptr +="</html>\n";
  return ptr;
}
