#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd (0x27,20,4); 
#include <WiFi.h>
#include <WiFiClient.h>
#include "FirebaseESP32.h"
#define WIFI_SSID "Chanh Tran"
#define WIFI_PASSWORD "19091971"
#define FIREBASE_HOST "doan2-38f4f-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "shVMs5GpDSanPw9Qz7PHqDOUcFLMcfxb62QIx0sf"
FirebaseData firebaseData;
FirebaseJson json;
String path = "/"; 
const int RXPin = 16, TXPin = 17; 
SoftwareSerial neo6m(RXPin, TXPin);
TinyGPSPlus gps; 
SoftwareSerial SIM(2, 4);
#define RST_PIN         27
#define SS_PIN          5 
MFRC522 mfrc522(SS_PIN, RST_PIN);
int UID[4], i;
int ID1[4] = {66, 9, 127, 76}; 
int ID2[4] = {243, 93, 249, 149}; 
int ID3[4] = {227, 145, 015, 150}; 
int ID4[4] = {42, 128, 103, 26}; 
int ID5[4] = {121, 43, 219, 59}; 
int solanquet1 = 0; 
int solanquet2 = 0; 
int solanquettaixe = 0; 
int solanquet3 = 0; 
int solanquettaixe2 = 0; 
 int buzzer = 12;
int dem = 0; 
const int led_hd = 33;
bool nut = false; 
bool firstPress = false;
const int buttonPin = 13; 
const int ledPin = 32; 
String number1 = "0911417094"; 
String number2 = "0987045339"; 
String number3 = "0325146918"; 
String SMS_Warning = "CANH BAO, CO HOC SINH DANG KET TRONG XE";
String SMS_Success1 = "BE TRAN TRUNG TIN DA TOI TRUONG";
String SMS_Success2 = "BE PHAM HOANG VI KHANG DA TOI TRUONG";
String SMS_Success3 = "BE VO PHAN TRI NGUYEN DA TOI TRUONG";
int buttonPressCount = 0;
boolean callAttempted = false;
boolean lastCallAnswered = false;
String timeStr;
String dateStr;
enum CallStatus {
  CALL_NONE, 
  CALL_RINGING,
  CALL_CONNECTED,
  CALL_DISCONNECTED, 
};
CallStatus callStatus = CALL_NONE;
void Tin_check(){
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    solanquet1++;
    if ( (solanquet1%2) == 1){
      dem++;
      lcd.setCursor(6,3);
      lcd.print("CHECK IN");
      lcd.setCursor(0,0); 
      lcd.print("----------*---------"); 
      lcd.setCursor(3,1); 
      lcd.print("TRAN TRUNG TIN");      
      lcd.setCursor(3,2); 
      lcd.print("MSHS:");    
      lcd.setCursor(8,2); 
      lcd.print(" 20161270 "); 
      Firebase.setInt(firebaseData, path + "/Thong tin cua xe/So luong hoc sinh hien tai tren xe",dem);
      Firebase.setString(firebaseData, path + "Danh sach hoc sinh checkin/Ten hoc sinh 1/Ho va ten", "'Trần Trung Tín'");
      Firebase.setString(firebaseData, "/Danh sach hoc sinh checkin/Ten hoc sinh 1/time", timeStr);
      Firebase.setString(firebaseData, "/Danh sach hoc sinh checkin/Ten hoc sinh 1/date", dateStr);
      }
    else{
      lcd.setCursor(0,0); 
      lcd.print("----------*---------"); 
      lcd.setCursor(3,1); 
      lcd.print("TRAN TRUNG TIN");      
      lcd.setCursor(3,2); 
      lcd.print("MSHS:");    
      lcd.setCursor(8,2); 
      lcd.print(" 20161270 "); 
      lcd.setCursor(6,3);
      lcd.print("CHECK OUT");
      Firebase.setString(firebaseData, path + "Danh sach hoc sinh checkout/Ten hoc sinh 1/Ho va ten", "'Trần Trung Tín'");
      Firebase.setString(firebaseData, "/Danh sach hoc sinh checkout/Ten hoc sinh 1/time", timeStr);
      Firebase.setString(firebaseData, "/Danh sach hoc sinh checkout/Ten hoc sinh 1/date", dateStr);     
      delay(2000);
      GUI(number2,SMS_Success1);
      delay(500); 
      } 
    delay(500);
    lcd.clear();
    lcd.setCursor(6,1); 
    lcd.print("HE THONG");
    lcd.setCursor(4,2); 
    lcd.print("DA SAN SANG!");    
}
void Khang_check(){
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    solanquet2++;
    if ( (solanquet2%2) == 1){
      dem++;
      lcd.setCursor(6,3);
      lcd.print("CHECK IN");
      lcd.setCursor(0,0); 
      lcd.print("----------*---------"); 
      lcd.setCursor(1,1); 
      lcd.print("PHAM HOANG VI KHANG");   
      lcd.setCursor(3,2); 
      lcd.print("MSHS:");    
      lcd.setCursor(8,2); 
      lcd.print(" 20161208 ");      
      Firebase.setInt(firebaseData, path + "/Thong tin cua xe/So luong hoc sinh hien tai tren xe",dem);
      Firebase.setString(firebaseData, path + "Danh sach hoc sinh checkin/Ten hoc sinh 2/Ho va ten", "'Phạm Hoàng Vĩ Khang'");
      Firebase.setString(firebaseData, "/Danh sach hoc sinh checkin/Ten hoc sinh 2/time", timeStr);
      Firebase.setString(firebaseData, "/Danh sach hoc sinh checkin/Ten hoc sinh 2/date", dateStr);
      }
    else{
      lcd.setCursor(6,3);
      lcd.print("CHECK OUT");
      lcd.setCursor(0,0); 
      lcd.print("----------*---------"); 
      lcd.setCursor(1,1); 
      lcd.print("PHAM HOANG VI KHANG");   
      lcd.setCursor(3,2); 
      lcd.print("MSHS:");  
      lcd.setCursor(8,2); 
      lcd.print(" 20161208 "); 
      Firebase.setString(firebaseData, path + "Danh sach hoc sinh checkout/Ten hoc sinh 2/Ho va ten", "'Phạm Hoàng Vĩ Khang'");
      Firebase.setString(firebaseData, "/Danh sach hoc sinh checkout/Ten hoc sinh 2/time", timeStr);
      Firebase.setString(firebaseData, "/Danh sach hoc sinh checkout/Ten hoc sinh 2/date", dateStr);
      delay(2000);  
      GUI(number1,SMS_Success2);
      delay(500);   
      }
    delay(500);
    lcd.clear();
    lcd.setCursor(6,1); 
    lcd.print("HE THONG"); 
    lcd.setCursor(4,2); 
    lcd.print("DA SAN SANG!");   
}
void Nguyen_check(){
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    solanquet3++;
    if ( (solanquet3%2) == 1){
      dem++;
      lcd.setCursor(6,3);
      lcd.print("CHECK IN");
      lcd.setCursor(0,0); 
      lcd.print("----------*---------"); 
      lcd.setCursor(1,1); 
      lcd.print("VO PHAN TRI NGUYEN");   
      lcd.setCursor(3,2); 
      lcd.print("MSHS:");   
      lcd.setCursor(8,2); 
      lcd.print(" 20161238 ");           
      Firebase.setInt(firebaseData, path + "/Thong tin cua xe/So luong hoc sinh hien tai tren xe",dem);
      Firebase.setString(firebaseData, path + "Danh sach hoc sinh checkin/Ten hoc sinh 3/Ho va ten", "'Võ Phan Trí Nguyên'");
      Firebase.setString(firebaseData, "/Danh sach hoc sinh checkin/Ten hoc sinh 3/time", timeStr);
      Firebase.setString(firebaseData, "/Danh sach hoc sinh checkin/Ten hoc sinh 3/date", dateStr);
      }
    else{
      lcd.setCursor(6,3);
      lcd.print("CHECK OUT");
      lcd.setCursor(0,0); 
      lcd.print("----------*---------"); 
      lcd.setCursor(1,1); 
      lcd.print("VO PHAN TRI NGUYEN");  
      lcd.setCursor(3,2); 
      lcd.print("MSHS:");  
      lcd.setCursor(8,2); 
      lcd.print(" 20161238 ");       
      Firebase.setString(firebaseData, path + "Danh sach hoc sinh checkout/Ten hoc sinh 3/Ho va ten", "'Võ Phan Trí Nguyên'");  
      Firebase.setString(firebaseData, "/Danh sach hoc sinh checkout/Ten hoc sinh 3/time", timeStr);
      Firebase.setString(firebaseData, "/Danh sach hoc sinh checkout/Ten hoc sinh 3/date", dateStr); 
      delay(2000);
      GUI(number3,SMS_Success3);
      delay(500);   
      } 
    delay(500);
    lcd.clear();
    lcd.setCursor(6,1); 
    lcd.print("HE THONG"); 
    lcd.setCursor(4,2); 
    lcd.print("DA SAN SANG!");   
}
void Tin_khancap(){
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("DANG LIEN LAC VOI");
    lcd.setCursor(4,1);
    lcd.print("PHU HUYNH...");
    lcd.setCursor(3,2); 
    lcd.print("TRAN TRUNG TIN");        
    lcd.setCursor(3,3); 
    lcd.print("MSHS:");  
    lcd.setCursor(8,3); 
    lcd.print(" 20161270 ");  
    GOI(number2);
    delay(3000);
    lcd.clear();
    lcd.setCursor(6,1); 
    lcd.print("HE THONG"); 
    lcd.setCursor(4,2); 
    lcd.print("DA SAN SANG!");
    nut = false;
    buttonPressCount =0;
    digitalWrite(ledPin, LOW);    
}
void Khang_khancap(){
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("DANG LIEN LAC VOI");
    lcd.setCursor(4,1);
    lcd.print("PHU HUYNH...");
    lcd.setCursor(1,2); 
    lcd.print("PHAM HOANG VI KHANG");  
    lcd.setCursor(3,3); 
    lcd.print("MSHS:");   
    lcd.setCursor(8,3); 
    lcd.print(" 20161208 "); 
    GOI(number1);
    delay(3000);
    lcd.clear();
    lcd.setCursor(6,1); 
    lcd.print("HE THONG"); 
    lcd.setCursor(4,2);
    lcd.print("DA SAN SANG!");     
    nut = false; 
    buttonPressCount =0;
    digitalWrite(ledPin, LOW);      
}
void Nguyen_khancap(){
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("DANG LIEN LAC VOI");
    lcd.setCursor(4,1);
    lcd.print("PHU HUYNH...");
    lcd.setCursor(1,2); 
    lcd.print("VO PHAN TRI NGUYEN");  
    lcd.setCursor(3,3); 
    lcd.print("MSHS:");  
    lcd.setCursor(8,3); 
    lcd.print(" 20161238 "); 
    GOI(number3);
    delay(3000);
    lcd.clear();
    lcd.setCursor(6,1); 
    lcd.print("HE THONG"); 
    lcd.setCursor(4,2); 
    lcd.print("DA SAN SANG!");     
    nut = false;
    buttonPressCount =0;
    digitalWrite(ledPin, LOW);       
}
void taixe_checkout_chua_duoc(){
    lcd.clear();
    lcd.setCursor(6,1);
    lcd.print("CANH BAO");
    lcd.setCursor(0,2);
    lcd.print("CON HOC SINH MAC KET");
    lcd.setCursor(5,3);
    lcd.print("TREN XE!!!");
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(1000);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    Firebase.setString(firebaseData, "/Thong tin cua xe/Thoi gian tai xe xuong xe/time", timeStr);
    Firebase.setString(firebaseData, "/Thong tin cua xe/Thoi gian tai xe xuong xe/date", dateStr);
    delay(1000);     
}
void taixe_checkout_duoc(){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("HIEN TAI KHONG CON");
    lcd.setCursor(2,1);
    lcd.print("HOC SINH TREN XE");
    if (UID[i] == ID3[i]){  
    lcd.setCursor(2,2);
    lcd.print("TAI XE CHECK OUT");
    lcd.setCursor(2,3); 
    lcd.print(" MSTX: 20161188"); 
    Firebase.setString(firebaseData, "/Thong tin cua xe/Thoi gian tai xe xuong xe/time", timeStr);
    Firebase.setString(firebaseData, "/Thong tin cua xe/Thoi gian tai xe xuong xe/date", dateStr);
    delay(3000);
    }
    else if (UID[i] == ID5[i]){
    lcd.setCursor(2,2);
    lcd.print("TAI XE CHECK OUT");
    lcd.setCursor(2,3); 
    lcd.print(" MSTX: 20161187"); 
    Firebase.setString(firebaseData, "/Thong tin cua xe/Thoi gian tai xe xuong xe/time", timeStr);
    Firebase.setString(firebaseData, "/Thong tin cua xe/Thoi gian tai xe xuong xe/date", dateStr); 
    delay(3000);      
    }
    lcd.clear();
    lcd.setCursor(6,1); 
    lcd.print("HE THONG"); 
    lcd.setCursor(4,2);
    lcd.print("DA SAN SANG!"); 
}
void taixe_check(){
    if ((solanquet1%2) == 1 || (solanquet2%2) == 1 || (solanquet3%2) == 1){
       taixe_checkout_chua_duoc();     
    }
  else{
      taixe_checkout_duoc();              
    }
}
void taixe(){
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    solanquettaixe++;
    if ( (solanquettaixe%2) == 1)
    {
      lcd.setCursor(2,1);
      lcd.print("TAI XE CHECK IN");
      lcd.setCursor(4,2);
      lcd.print("NGO VAN HANH");      
      lcd.setCursor(2,3); 
      lcd.print(" MSTX: 20161188");  
      delay(1000);
      Firebase.setString(firebaseData, path + "Thong tin cua xe/Ten tai xe", "'Ngô Văn Hạnh'");
      Firebase.setString(firebaseData, path + "Thong tin cua xe/Bien so xe", "'51-T1 063.05'");           
      Firebase.setString(firebaseData, path + "Thong tin cua xe/Loai xe", "TOYOTA");
      Firebase.setString(firebaseData, path + "Thong tin cua xe/So dien thoai tai xe", "'0333617584'");
      Firebase.setString(firebaseData, "/Thong tin cua xe/Thoi gian bat dau/time", timeStr);
      Firebase.setString(firebaseData, "/Thong tin cua xe/Thoi gian bat dau/date", dateStr);             
      lcd.clear();
      lcd.setCursor(6,1); 
      lcd.print("HE THONG"); 
      lcd.setCursor(4,2); 
      lcd.print("DA SAN SANG!");   
      }
    else{
      taixe_check();
    }    
    lcd.clear();
    lcd.setCursor(6,1); 
    lcd.print("HE THONG"); 
    lcd.setCursor(4,2); 
    lcd.print("DA SAN SANG!"); 
}
void taixe2(){
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    solanquettaixe2++;
    if ( (solanquettaixe2%2) == 1)
    {
      lcd.setCursor(2,1);
      lcd.print("TAI XE CHECK IN");
      lcd.setCursor(4,2);
      lcd.print("VU DINH HAI"); 
      lcd.setCursor(2,3); 
      lcd.print(" MSTX: 20161187"); 
      delay(1000);
      Firebase.setString(firebaseData, path + "Thong tin cua xe/Ten tai xe", "'Vũ Đình Hải'");
      Firebase.setString(firebaseData, path + "Thong tin cua xe/Bien so xe", "'15-C1 010.82'");           
      Firebase.setString(firebaseData, path + "Thong tin cua xe/Loai xe", "HYUNDAI");
      Firebase.setString(firebaseData, path + "Thong tin cua xe/So dien thoai tai xe", "'0368403868'"); 
      Firebase.setString(firebaseData, "/Thong tin cua xe/Thoi gian bat dau/time", timeStr);
      Firebase.setString(firebaseData, "/Thong tin cua xe/Thoi gian bat dau/date", dateStr);            
      lcd.clear();
      lcd.setCursor(6,1); 
      lcd.print("HE THONG"); 
      lcd.setCursor(4,2); 
      lcd.print("DA SAN SANG!"); 
      }
    else{
      taixe_check();
    }    
      lcd.clear();
      lcd.setCursor(6,1); 
      lcd.print("HE THONG"); 
      lcd.setCursor(4,2); 
      lcd.print("DA SAN SANG!");      
}
void setup() {
  Serial.begin(9600);  
  neo6m.begin(9600);  
  SIM.begin(9600);  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(ledPin, LOW);  
  pinMode(led_hd, OUTPUT);  
  SPI.begin();   
  mfrc522.PCD_Init(); 
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);  
  lcd.init(); 
  lcd.backlight(); 
  lcd.setCursor(6,0); 
  lcd.print("HE THONG"); 
  lcd.setCursor(1,1);
  lcd.print("GIAM SAT HOC SINH"); 
  lcd.setCursor(0,2); 
  lcd.print("KHI THAM GIA DICH VU");
  lcd.setCursor(0,3);
  lcd.print("DUA RUOC CUA TRUONG!"); 
  delay(1000);
  lcd.clear();
  lcd.setCursor(3,0); 
  lcd.print("TRAN TRUNG TIN"); 
  lcd.setCursor(6,1);
  lcd.print("20161270"); 
  lcd.setCursor(1,2); 
  lcd.print("PHAM HOANG VI KHANG");
  lcd.setCursor(6,3);
  lcd.print("20161208"); 
  delay(1000);
  lcd.clear();
  lcd.setCursor(6,1); 
  lcd.print("HE THONG"); 
  lcd.setCursor(4,2); 
  lcd.print("DA SAN SANG!");          
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  while (WiFi.status() != WL_CONNECTED) { 
  delay(500);
  Serial.print(".");  
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true); 
  if (!Firebase.beginStream(firebaseData, path)) 
  {
     Serial.println("REASON: " + firebaseData.errorReason()); 
     Serial.println();
  }
  Serial.print("Connected with IP: "); 
  Serial.println(WiFi.localIP());
  Serial.println();   
  Serial.println("Firebase OK."); 
}
void loop() {
  read_check_real_time();
  btn_khan_cap();
  smartdelay_gps(1000);
  get_location();        
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  { 
    return; 
  }  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {  
    return;
  }      
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  { 
    UID[i] = mfrc522.uid.uidByte[i]; 
  }
  if(nut){
    if (UID[i] == ID1[i]){
    Tin_khancap(); 
    }
    else if (UID[i] == ID2[i]){
    Khang_khancap();  
    }
    else if (UID[i] == ID4[i]){
    Nguyen_khancap(); 
    }
    else{
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("HIEN TAI");
    lcd.setCursor(3,1);
    lcd.print("MA SO HOC SINH");
    lcd.setCursor(1,2);
    lcd.print("CHUA DUOC DANG KY");
    lcd.setCursor(2,3);
    lcd.print("CHO DICH VU NAY!");
    delay(2000);
    lcd.clear();
    lcd.setCursor(6,1); 
    lcd.print("HE THONG"); 
    lcd.setCursor(4,2); 
    lcd.print("DA SAN SANG!");      
    nut = false; 
    buttonPressCount =0;
    digitalWrite(ledPin, LOW);    
    }
  }
  else{
  if (UID[i] == ID1[i])
  {
    Tin_check();   
  }  
  else if (UID[i] == ID2[i])
  {
    Khang_check();
  }
  else if (UID[i] == ID3[i])
  {
    taixe(); 
  }
  else if (UID[i] == ID4[i])
  {
    Nguyen_check();
  }
  else if (UID[i] == ID5[i])
  {
    taixe2(); 
  }  
  else
  {
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("HIEN TAI");
    lcd.setCursor(7,1);
    lcd.print("MA SO");
    lcd.setCursor(1,2);
    lcd.print("CHUA DUOC DANG KY");
    lcd.setCursor(2,3);
    lcd.print("CHO DICH VU NAY!");
    delay(2000);
    lcd.clear();
    lcd.setCursor(6,1); 
    lcd.print("HE THONG"); 
    lcd.setCursor(4,2); 
    lcd.print("DA SAN SANG!"); 
  }}  
  mfrc522.PICC_HaltA(); 
  mfrc522.PCD_StopCrypto1(); }
void get_location()
{
    if(gps.location.isValid())  
  {
    float latitude = gps.location.lat(); 
    float longitude = gps.location.lng(); 
    digitalWrite(led_hd, HIGH);     
    if(Firebase.setFloat(firebaseData, "/GPS/VIDOCUAXE", latitude))
      {} 
    else
      {}
    if(Firebase.setFloat(firebaseData, "/GPS/KINHDOCUAXE", longitude))
      {}
    else
      {}
  }
  else {
    Firebase.setString(firebaseData, path + "/GPS/KINHDOCUAXE","'KHÔNG THẤY'"); 
    Firebase.setString(firebaseData, path + "/GPS/VIDOCUAXE","'KHÔNG THẤY'"); 
  }
}
static void smartdelay_gps(unsigned long ms)
{
  unsigned long start = millis(); 
  do 
  {
    while (neo6m.available()) 
      gps.encode(neo6m.read()); 
  } while (millis() - start < ms); 
}
void print_ok()
{
    Serial.println("------------------------------------");
    Serial.println("OK");
    Serial.println("PATH: " + firebaseData.dataPath()); 
    Serial.println("TYPE: " + firebaseData.dataType()); 
    Serial.println("ETag: " + firebaseData.ETag()); 
    Serial.println("------------------------------------");
    Serial.println();
}
void print_fail()
{
    Serial.println("------------------------------------");
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
}
void xoa_lcd(){
  lcd.setCursor(0, 0);
  lcd.print("                             ");
  lcd.setCursor(0, 1);
  lcd.print("                             ");
}
void GUI(String number,String SMS)
  {
    Serial.println ("Sending Message");
    SIM.println("AT+CMGF=1");
    delay(500);
    Serial.println ("Set SMS Number");
    SIM.println(("AT+CMGS=\"" + number + "\"\r"));
    delay(500);
    SIM. println(SMS);
    delay(500);
    SIM.println((char)26);
    delay(500);
    Serial.println ("Sent");
  }
void GOI(String number)
  {
    Serial.println ("Calling");
    SIM.println("AT");
    delay(300);
    SIM.print("ATD");
    SIM.print(number);
    SIM.println(";");
    delay (15000);
  }
boolean checkCallStatus() 
  {
    SIM.println("AT+CLCC"); 
    delay(2000); 
    while (SIM.available()) 
     {
      String response = SIM.readStringUntil('\n');
      Serial.println("Phản hồi từ SIM: " + response);
        if (response.indexOf("+CLCC:") != -1) {}
        else if (response.indexOf("ACTIVE") != -1) 
        {
           return true; // Cuộc gọi đã được nhấc máy.
        } 
        else if (response.indexOf("NO ANSWER") != -1 || response.indexOf("BUSY") != -1) 
        {
           return false; 
        }
      } return false;
  }
void btn_khan_cap()
  {
    if (digitalRead(buttonPin) == LOW)
    { 
        delay(10);
    if (digitalRead(buttonPin) == LOW )
    {
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);      
      buttonPressCount++;
      if (buttonPressCount == 1) 
        {
          lcd.setCursor(6, 1);
          lcd.print("HIEN TAI");
          lcd.setCursor(3, 2);
          lcd.print("DANG LIEN LAC");
          lcd.setCursor(2, 3);
          lcd.print("VOI TAI XE LAN 1");          
          callAttempted = false;
          callStatus = CALL_RINGING;
          GOI(number1);
          delay(2000);
          lcd.clear();
          lcd.setCursor(6, 1);
          lcd.print("VUI LONG");
          lcd.setCursor(2, 2);
          lcd.print("NHAN NUT LAN 2 DE");
          lcd.setCursor(0, 3);
          lcd.print("GOI TAI XE LAN NUA!!");   
        } 
      else if (buttonPressCount == 2 && !lastCallAnswered && !nut) 
        {
          lcd.clear();
          lcd.setCursor(6, 1);
          lcd.print("HIEN TAI");
          lcd.setCursor(3, 2);
          lcd.print("DANG LIEN LAC");
          lcd.setCursor(2, 3);
          lcd.print("VOI TAI XE LAN 2");
          callAttempted = false;
          callStatus = CALL_RINGING;
          GOI(number1);
          delay(2000);
          nut = !nut;             
          digitalWrite(ledPin, HIGH);   
          lcd.clear();
          lcd.setCursor(2, 1);
          lcd.print("MOI BAN QUET THE");
          lcd.setCursor(1, 2);
          lcd.print("DE CO THE LIEN LAC");
          lcd.setCursor(2, 3);
          lcd.print("VOI PHU HUYNH!!!");          
        } 
        }} 
    if (callStatus == CALL_RINGING) 
      {
        if (checkCallStatus()) 
          {
            callStatus = CALL_CONNECTED;
            lcd.clear();
            lcd.setCursor(3,1);
            lcd.print("GOI THANH CONG");
            lcd.setCursor(4,2);
            lcd.print("HAY CHO DOI!");
            lastCallAnswered = true;
          } 
        else
          {
            callStatus = CALL_DISCONNECTED; 
            
            lcd.setCursor(4, 0);
            lcd.print("GOI THAT BAI");
            GUI(number1,SMS_Warning);
            delay(4000);
            lastCallAnswered = false;
          }     
      }
  }
void read_check_real_time()
  {
    while (neo6m.available() > 0) 
    {
      if (gps.encode(neo6m.read())) 
      {
        if (gps.time.isValid() && gps.date.isValid()) 
        { int adjustedHour = (gps.time.hour() + 7) % 24;
          timeStr = "'" + formatToTwoDigits(adjustedHour) + ":" + formatToTwoDigits(gps.time.minute()) + ":" + formatToTwoDigits(gps.time.second()) + "'";
          dateStr = "'" + String(gps.date.day()) + "/" + String(gps.date.month()) + "/" + String(gps.date.year()) + "'";
          delay(1000);  
        }
      }
    }
  }
void sendTimeToFirebase() {
  if (Firebase.setString(firebaseData, "/timestamp/time", timeStr) && Firebase.setString(firebaseData, "/timestamp/date", dateStr)) 
  {
  } else {
  }
}
String formatToTwoDigits(int value) {
  if (value < 10) {
    return "0" + String(value);
  } else {
    return String(value);
  }
}
