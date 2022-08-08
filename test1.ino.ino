#include <Wire.h> 
#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0X27,16,2); //SCL A5 SDA A4
String defaultMessage ="Hello World";
String msg ="1.Input Name\n 2.Hien thi ngay thang \n 3.End ";
String choice1 ="Input name";
String choice2 = "";
String choice3="End";
String goodbye ="goodbye";
String myString ="Waoo";
String yourNameis ="YouName is: ";
String quahansudung= "qua han use";
String raining = "raining";
String mayberain = "maybe rain";
int uutien =0;
int timeUsing=0;
int rainCheck = 0;
int rainThresholdValue = 30;

void TaskLoginUser(void * pvParameters);
// void TaskLoginTimeCounter(void * pvParameters);
void TaskRainSensor(void * pvParameters);
void setup()
{
  lcd.init();                    
  lcd.print(myString); 
  Serial.begin(9600);
  xTaskCreate(
    TaskLoginUser
    , "Task Login"
    , 128
    , NULL
    , 1
    , NULL
  );
  xTaskCreate(
    TaskRainSensor
    , "Task Rain"
    , 128
    , NULL
    , 1
    , NULL
  );
  // xTaskCreate(
  //   TaskLoginTimeCounter
  //   , "Task TimeCounter"
  //   , 128
  //   , NULL
  //   , 1
  //   , NULL
  // );
   vTaskStartScheduler();
}

void loop()
{
}
void TaskRainSensor(void * pvParameters) {
  pinMode(A0, INPUT);
  while (1) {
    int sensorValue = analogRead(A0);
    int percentValue = map(sensorValue,0,1023,100,0);
    if(percentValue > 80 &&percentValue <95 ){
      lcd.clear();
      lcd.print(mayberain);
    }
    if(percentValue>95){
      lcd.clear();
      lcd.print(raining);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void TaskLoginUser(void * pvParameters) {
  while(1){
  delay (3000);
  lcd.clear();
  lcd.print(defaultMessage); 
  Serial.print(msg);
  while(Serial.available() ==0){}
  int choice = Serial.parseInt();
  Serial.print(choice);
  if(choice==1){
    lcd.clear();
    Serial.print(yourNameis);
    lcd.print(yourNameis);
    delay(3000);
    String name = Serial.readString();
    name = name.substring(0, name.length() - 1);
    name.remove(0,1);
    uutien=1;
    Serial.println(name);
    lcd.clear();
    lcd.print(name);
    delay(1000);
    timeUsing=1;
  }
  timeUsing+=1;
  if(choice==3){
    lcd.clear();
    lcd.print(timeUsing);
    lcd.setCursor(0 , 1);
    lcd.print(goodbye);
    delay(3000);
  }
  }
}

