int WeldPin= 11; //13. portu LedPin olarak tanımladık.
int button= 2; //2. portu giriş olarak tanımladık
int buton_durum;

char gelen; //Gelen isminde bir karakter tanımlıyoruz.

void setup (){
Serial.begin(9600); 
pinMode(WeldPin, OUTPUT); //LedPini çıkış olarak tanımlıyoruz.
pinMode(button, INPUT);
digitalWrite (button, HIGH);
digitalWrite (WeldPin, LOW);
}
void loop (){
//if(Serial.available()>0)
//gelen=Serial.read(); // Serial port okuma komutunu gelen karakterine atıyoruz.
//if(gelen== ' ') 

buton_durum=digitalRead(button);
if(LOW==buton_durum)
{  
 delay(10);             
 digitalWrite (WeldPin, HIGH);
 delay(50);
 digitalWrite (WeldPin, LOW);
  delay(505);             
 digitalWrite (WeldPin, HIGH);
  delay(100);
 digitalWrite (WeldPin, LOW);
 delay(2000);
// gelen= NULL; 
}
}
