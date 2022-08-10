#include <LiquidCrystal.h>
#include <dht11.h> 
#define DHT11PIN 8
dht11 DHT11; 
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, DB4,DB5,DB6,DB7)
float temperature; 
int reading; 
int lm35Pin = A7;
int relay = 13;
int i;
int j;
int onoff=1; //카운트 많이 올라가는거 방지용, 경계온도에서 여러번 잡힐 수 있으니까
int
count=0;
float T;
float reading2;

void setup() 
{
lcd.begin(16, 2);
analogReference(INTERNAL);
Serial.begin(9600);
pinMode(relay, OUTPUT);
}
double Fahrenheit(double celsius) // Fahrenheit라는 함수를 만듭니다. 함수의 입력값은 celsius에 저장됩니다.
{
return 1.8 * celsius + 32; // 입력된 celsius값을 1.8를 곱하고 32를 더하여 출력합니다.
}

void loop() 
{ 
reading = analogRead(lm35Pin);
delay(100);
for(i=1;i<=6;i++)
{
reading = reading+analogRead(lm35Pin);
delay(100);
}
temperature=temperature*30;
reading=reading+temperature;
reading = reading/10; 
temperature = (reading / 10.0);
reading2=(float)DHT11.temperature;
delay(100);
reading2=(reading2+T)/2;
T=reading2;
//온도 조절 이게 lm35
if(temperature>38.5&&onoff==0)
{
digitalWrite(relay, LOW); 
onoff=1;
count=count+1;
}
else if(temperature<36.9&&onoff==1)
{
digitalWrite(relay, HIGH); 
onoff=0;
count=count+1;
}
/*
if(T>24&&onoff==0)
{
digitalWrite(relay, LOW); 
onoff=1;
count=count+1;
}
else if(T<21&&onoff==1)
{
digitalWrite(relay, HIGH); 
onoff=0;
count=count+1;
}
*/
//lcd 패널 출력
lcd.setCursor(0,0);
lcd.print("T:");
lcd.setCursor(3,0);
lcd.print(temperature);
lcd.print((char)223);
lcd.print("C");
lcd.setCursor(12,0);
lcd.print(count);
float chk = DHT11.read(DHT11PIN);
lcd.setCursor(0,1);
lcd.print("T:");
lcd.setCursor(3,1);
lcd.print((float)DHT11.temperature,0);
lcd.print((char)223);
lcd.print("C");
lcd.setCursor(8,1);
lcd.print("H:");
lcd.print((float)DHT11.humidity,0);
lcd.print("%");
Serial.println(analogRead(lm35Pin)/10);
Serial.println(temperature);
Serial.println((float)DHT11.temperature); 
Serial.println((float)DHT11.humidity); 
delay(600);
}