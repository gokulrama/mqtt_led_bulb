#include <ESP8266WiFi.h>
#include <PubSubClient.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
 
const char* ssid = "Dancing Birds";
const char* password =  "vguard@1234";

const char* mqttServer = "vguardbox.com";
const int mqttPort = 8883;
const char* mqttUser = "";
const char* mqttPassword = "";

#define LED_R 12
#define LED_G 15
#define LED_B 13

//int sensorValue;

/*int sensorPin = 11;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
 float temp_sensor_offset=0.4;
 float ADC_VALUE=0.005;
 float temp_voltage=0.0;
 float temp_true_voltage=0.0;
 float temperature=0.0;
  int temp_adc_sampling=0;
   int temp_adc=0;*/
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);

  // prepare GPIO2
 // pinMode(2, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  //digitalWrite(2, HIGH);
  
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  void callback(char* topic, byte* payload, unsigned int length);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client")) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("esp/test");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 char pay[length+1];
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  memset((char *)pay,0,sizeof(pay));
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    pay[i]=(char)payload[i];
  }
  Serial.println("-----------------------");


  if(strcmp((char*)pay,"on")==0){
  //  Serial.println("0,255,0");
    // digitalWrite ( 2, HIGH );
    analogWrite(LED_R,255);analogWrite(LED_G,255);analogWrite(LED_B,255);
  }else if(strcmp((char*)pay,"off")==0){
   // Serial.println("0,0,0");
    // digitalWrite ( 2, LOW );
    analogWrite(LED_R,0);analogWrite(LED_G,0);analogWrite(LED_B,0);
  }else{
    Serial.println((char*)pay);
    char red[3];
    char green[3];
    char blue[3];
    /*memset((char *)red,0,sizeof(red));
    memset((char *)green,0,sizeof(green));
    memset((char *)blue,0,sizeof(blue));
   // 
    red[0]=pay[5];red[1]=pay[6];red[2]=pay[7];
    green[0]=pay[9];green[1]=pay[10];green[2]=pay[11];
    blue[0]=pay[13];blue[1]=pay[14];blue[2]=pay[15];
    Serial.println(atoi(red));
    Serial.println(atoi(green));
    Serial.println(atoi(blue));
    analogWrite(LED_R,atoi(red));analogWrite(LED_G,atoi(green));analogWrite(LED_B,atoi(blue));*/
    char buff[30];
   for(int j=0; pay[j]!=']';j++)
   {
    buff[j]=pay[j+5];
   }

  
    //working code
    red[0]=buff[0];red[1]=buff[1];red[2]=buff[2];
    green[0]=buff[4];green[1]=buff[5];green[2]=buff[6];
    blue[0]=buff[8];blue[1]=buff[9];blue[2]=buff[10];
    analogWrite(LED_R,atoi(red));analogWrite(LED_G,atoi(green));analogWrite(LED_B,atoi(blue));
   /* int flag=0;
   Serial.println(buff);
   int i,j;
   for (i=0,j=0;buff[j]!=']';j++)
   {
    flag=0;
    if(buff[j]==',')
    {
      flag++;
    }else{
      if(flag!=1&&flag!=2&& flag==0)
      {
       Serial.print("RED");
      red[i++]=buff[j];
      Serial.print(red[i]);
      }
      if(flag==1 && i<=3 && buff[i]!=']'){
        Serial.print("GREEN");
      i=0;
      green[i++]=buff[j];
      Serial.print(green[i]);

      }
      if(flag==2 && i<=3 && buff[i]!=']')
      {
        Serial.print("BLUE");
        i=0;
        blue[i++]=buff[j];
        Serial.print(blue[i]);

        flag=0;
      }
    
    }
   }
  Serial.println("s---");
  Serial.println(atoi(red));
  Serial.println(atoi(green));
  Serial.println(atoi(blue));
  Serial.println("e---");
*/
    
  }
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
 /* delay(1000);
  char buf[100];
  sensorValue = digitalRead(2);
  for(int i=0;i<10;++i){
   
     sensorValue=analogRead(sensorPin);
 
     temp_adc_sampling+= sensorValue;
  }
  temp_adc= (temp_adc_sampling / 10);
  temp_adc_sampling=0;
     //Serial.println(temp_adc);
  temp_voltage = (temp_adc*ADC_VALUE);
  temp_true_voltage =(temp_voltage-temp_sensor_offset);
  temperature =(temp_true_voltage/0.020);
  gcvt(sensorValue, 4, buf);
  Serial.println(buf);
  client.publish("esp/test", buf);
  delay(1000);*/
}


