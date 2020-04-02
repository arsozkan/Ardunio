#include <SoftwareSerial.h>
int rxPin = 10;                           //ESP8266 Tx kısmı
int txPin = 11;                           //ESP8266 Rx kısmı

String agAdi = "arslan";                 //Ağımızın adını buraya yazıyoruz.    
String agSifresi = "******";             //Ağımızın şifresini buraya yazıyoruz.

String ip = "13.82.214.154";             //Çalıştırmak istediğimiz API nin ip adresi
int sicaklik = 700;                      // Herhangi bir değer

SoftwareSerial esp(rxPin, txPin);

void setup() {

 Serial.begin(9600); 
 Serial.println("Started");
 esp.begin(115200);                                          
  
 esp.println("AT");                                         
 Serial.println("AT Yollandı");
  while(!esp.find("OK")){                                    
    esp.println("AT");
    Serial.println("ESP8266 Bulunamadı.");
  }
 Serial.println("OK Komutu Alındı");
 esp.println("AT+CWMODE=1");                                 
  while(!esp.find("OK")){                                     
    esp.println("AT+CWMODE=1");
    Serial.println("Ayar Yapılıyor....");
  }
  Serial.println("Client olarak ayarlandı");
  Serial.println("Aga Baglaniliyor...");
  esp.println("AT+CWJAP=\""+agAdi+"\",\""+agSifresi+"\"");    
  while(!esp.find("OK"));                                     
  Serial.println("Aga Baglandi.");
  delay(2000);
  
}


void loop() {
  
esp.println("AT+CIPSTART=\"TCP\",\""+ip+"\",80");           //API SSL kısmının kapalı olması gerekiyor
  if(esp.find("Error")){                                     
    Serial.println("AT+CIPSTART Error");
  }
  sicaklik = sicaklik + 1;
  String veri = "GET https://dev.baypmtech.com/Ardunio/rest/Ardunio/Mesafe?";         //API URL si                            
  veri += "&Field1=";                                         //Url Parametresi APInizi göre değiştirebilirsiniz
  veri += String(sicaklik);                                   //Göndereceğimiz herhangi birr değr
  veri += "\r\n\r\n"; 
  esp.print("AT+CIPSEND=");                                   
  esp.println(veri.length()+2);
  delay(2000);
  if(esp.find(">")){                                          
    esp.print(veri);                                       
    Serial.println(veri);
    Serial.println("Veri gonderildi.");
    delay(1000);
  }
  Serial.println("Baglantı Kapatildi.");
  esp.println("AT+CIPCLOSE");                                
  delay(3000);  

}
