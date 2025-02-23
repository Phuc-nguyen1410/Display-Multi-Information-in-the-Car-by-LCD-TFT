//UNO
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
#include "OneButton.h"
#include <mcp2515.h>

const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define ORANGE  0xFD20
#define DARKORANGE  0xFB60
#define MAROON  0x7800
#define BIENTRO A5
#define BUTTON_PIN1 0
#define CS_PIN 10 // Chân CS của mcp2515
#define INT_PIN 2 // Chân INT của mcp2515

struct can_frame canMsg;
MCP2515 mcp2515(CS_PIN);

float i=0;
int giatri;
int dienap;
int tocdo;
unsigned long int quangduong;
unsigned long int quangduongtrip;
unsigned long int s =0;

const int BUTTON_PIN2 = 1; // Pin của nút nhấn

int temp = 0;
int state = 0;
bool flag = false;
unsigned long buttonPressTime;
int dem;
int status = 0;

void setup(void)
{
  Serial.begin(9600);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  tft.begin();
  tft.setRotation(0);   
  pinMode(BUTTON_PIN1, INPUT_PULLUP);         //PORTRAIT
  tft.fillScreen(BLACK);  // bắt đầu hiển thị với màn hình màu đen 
}

void loop() {
//kẻ line trắng trên
  tft.fillRect(0,50,240,2,WHITE);
//kẻ line trắng trên
  tft.fillRect(0,280,240,2,WHITE); 
if (digitalRead(BUTTON_PIN1) == LOW) {
    dem++;
    delay(10);
    status = dem;
if (status == 0) {
  } else if (status == 1) {
// đèn báo check engine
    tft.drawLine(20,230,40,230,YELLOW); 
    tft.drawLine(30,230,30,234,YELLOW);
    tft.drawLine(14,234,42,234,YELLOW);
    tft.drawLine(14,234,14,250,YELLOW);
    tft.drawLine(14,250,21,250,YELLOW);
    tft.drawLine(21,250,27,255,YELLOW);
    tft.drawLine(27,255,46,255,YELLOW);
    tft.drawLine(46,255,46,250,YELLOW);
    tft.drawLine(46,250,51,250,YELLOW);
    tft.drawLine(51,250,51,255,YELLOW);
    tft.drawLine(51,255,53,255,YELLOW);
    tft.drawLine(53,255,56,253,YELLOW);//
    tft.drawLine(56,253,56,241,YELLOW);
    tft.drawLine(56,241,53,239,YELLOW);//
    tft.drawLine(53,239,51,239,YELLOW);
    tft.drawLine(51,239,51,244,YELLOW);
    tft.drawLine(51,244,48,244,YELLOW);//
    tft.drawLine(48,244,48,239,YELLOW);
    tft.drawLine(48,239,42,234,YELLOW);
    tft.drawLine(14,242,10,242,YELLOW);
    tft.drawLine(10,234,10,250,YELLOW); 
    delay(40);
   } else if (status == 2) {
// đèn báo dầu
    tft.fillRect(8,229,50,30,BLACK);
    tft.drawRect(15,180,22,16,RED);
    tft.fillRect(36,188,2,10,BLACK);
    tft.drawLine(26,180,26,176,RED);
    tft.drawLine(18,176,34,176,RED);
    tft.drawLine(36,187,41,187,RED);
    tft.drawLine(41,187,63,176,RED);
    tft.drawLine(63,176,67,179,RED);
    tft.drawLine(64,177,67,179,RED);
    tft.drawLine(36,195,40,195,RED);
    tft.drawLine(40,195,63,177,RED);
    tft.fillRect(67,182,2,2,RED);
    tft.fillRect(66,184,4,3,RED);
    tft.drawLine(15,180,15,177,RED);
    tft.drawLine(15,177,10,174,RED);
    tft.drawLine(10,174,8,179,RED);
    tft.drawLine(8,179,15,182,RED);
    delay(40);
  } else if (status == 3) {
    // đèn báo bình
    tft.fillRect(7,173,64,23,BLACK);
    tft.drawRect(10,125,40,28,RED);
    tft.fillRect(16,122,8,3,RED);
    tft.fillRect(34,122,8,3,RED);//
    tft.drawLine(16,133,24,133,RED);
    tft.drawLine(34,133,42,133,RED);
    tft.drawLine(38,129,38,137,RED);
    delay(40);
  } else if (status ==4){
    //đèn báo pha
    tft.fillRect(9, 120, 44, 35, BLACK);
    drawHalfCircle(tft.width()/2, tft.height()/2, 15, BLUE);
    delay(40);
  } else if (status ==5){
    dem= 0;
     tft.fillRect(9, 120, 44, 155, BLACK);
     tft.fillRect(95,8,100,32,BLACK);
     delay(40);
  }
}
giatri = analogRead (A5);               //Analog: 0 - 1023
dienap = map(giatri,0,1023,0,5000);     //Điện áp: 0 - 5000mv (0-5v)
tocdo = map(dienap,0,5000,0,33.34); // 120 km/h sang 33.34m/s
  quangduong = quangduong + tocdo*0.3;
  quangduongtrip = quangduongtrip +tocdo*0.3;
  delay(300);
  tft.fillRect(98,283,150,25,BLACK);
  if (temp < 1) {tft.fillRect(1,283,238,30,BLACK);}
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.setCursor(10,288);
  if (temp < 1) {tft.println("ODO");}
  tft.setCursor(100,288);
  if (flag) {
    printText(quangduong);
  } else {
    printText(quangduongtrip);
  }
  delay(10);
  if (digitalRead(BUTTON_PIN2) == LOW) {
    temp++;
    delay(50); // debounce
      buttonPressTime = millis();
      while (digitalRead(BUTTON_PIN2) == LOW) {
        if (millis() - buttonPressTime > 1000) {
          tft.fillRect(1,283,238,30,BLACK);
          quangduongtrip = s;
          tft.setTextSize(3);
          tft.setTextColor(WHITE);
          tft.setCursor(10,288);
          tft.println("TRIP");
          tft.setCursor(100,288);
          flag = false;
          printText(quangduongtrip*0);
          while (digitalRead(BUTTON_PIN2) == LOW); // wait for button release
          return;
        }
      }
      state = !state;
      if (state == 0) {
        flag = true;
        tft.fillRect(1,283,238,30,BLACK);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.setCursor(15,288);
        tft.println("ODO");
        tft.setCursor(100,288);
        printText(quangduong);
      } else {
        flag = false;
        tft.fillRect(1,283,238,30,BLACK);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.setCursor(10,288);
        tft.println("TRIP");
        tft.setCursor(100,288);
        printText(quangduongtrip);
      }
  }
//công tắc xi nhan
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) { // Nếu nhận được tin nhắn từ mcp2515
    Serial.print("Đã nhận tin nhắn: ID = "); // In ra Serial
    Serial.print(canMsg.can_id, HEX); // In ra ID của tin nhắn
    Serial.print(", DLC = "); // In ra DLC của tin nhắn
    Serial.print(canMsg.can_dlc, HEX); // In ra độ dài của tin nhắn
    Serial.print(", DATA = "); // In ra dữ liệu của tin nhắn
    Serial.print(canMsg.data[0]);
    for (int i = 1; i < canMsg.can_dlc; i++) {
      Serial.print(" ");
      Serial.print(canMsg.data[i], HEX); // In ra từng byte dữ liệu
      }
    Serial.println(); // Xuống dòng 
    if (canMsg.can_id == 608 && canMsg.can_dlc == 3) { // Nếu ID của tin nhắn là 260 và độ dài là 3
      if (String(canMsg.data[0], HEX) == "19") { // Nếu byte 1 của tin nhắn là 25
        if (String(canMsg.data[1], HEX) == "3a" && String(canMsg.data[2], HEX) == "80") { // Nếu byte 2 là 3A và byte 3 là 80
          tft.fillRect(14, 57, 52,40 , BLACK);
          tft.fillRect(189, 57, 52, 40, BLACK);
          tft.fillRect(190,65,20,20,GREEN);
          tft.fillTriangle(230,74,210,92,210,58,GREEN); // Vẽ hình chữ nhật màu đỏ
        } else if (String(canMsg.data[1], HEX) == "3" && String(canMsg.data[2], HEX) == "80") { // Nếu byte 2 là 03 và byte 3 là 80
          tft.fillRect(14, 57, 52,40 , BLACK);
          tft.fillRect(189, 57, 52, 40, BLACK);
          tft.fillRect(30,65,20,20,GREEN);
          tft.fillTriangle(30,58,30,92,15,74,GREEN);
          }
      }
      else { // Nếu byte 1 của tin nhắn không phải là 25
        tft.fillRect(14, 57, 52,40 , BLACK);
        tft.fillRect(189, 57, 52, 40, BLACK);
      }
    }
  }
// nút nhấn đóng mở cửa
if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) { // Nếu nhận được tin nhắn từ mcp2515
    Serial.print("Đã nhận tin nhắn: ID = "); // In ra Serial
    Serial.print(canMsg.can_id, HEX); // In ra ID của tin nhắn
    Serial.print(", DLC = "); // In ra DLC của tin nhắn
    Serial.print(canMsg.can_dlc, HEX); // In ra độ dài của tin nhắn
    Serial.print(", DATA = "); // In ra dữ liệu của tin nhắn
      for (int j = 0; j < canMsg.can_dlc; j++) {
        Serial.print(" ");
        Serial.print(canMsg.data[j], HEX); // In ra từng byte dữ liệu
    }
    Serial.println(); // Xuống dòng
    if (canMsg.can_id == 1029 && canMsg.can_dlc == 6 && String(canMsg.data[3], HEX) == "20") { // Nếu ID của tin nhắn là 405 và độ dài là 6        
      tft.fillRect(75,85,110,150,BLACK);
      drawCar1(95, 100, 90, 140, WHITE);        
    }
    else if (String(canMsg.data[3], HEX) == "0") { // Nếu byte 4 của tin nhắn không phải là 20
         tft.fillRect(75,80,110,150,BLACK);
         drawCar(95, 100, 90, 140, WHITE);
    } 
  }
}

void printText(unsigned long int thamso){
  unsigned char tramngan, chucngan, ngan, tram, chuc, donvi;
        tramngan = thamso/100000%10;
        chucngan = thamso/10000%10;
        ngan = thamso/1000%10;
        tram = thamso/100%10;
        chuc = thamso/10%10;
        donvi = thamso%10;
        tft.print(tramngan);
        tft.print(chucngan);
        tft.print(ngan);
        tft.print(tram);
        tft.print(chuc);
        tft.print(donvi);
}

void drawCar(int x, int y, int w, int h, uint16_t color) {
//vẽ thân xe
  tft.fillRect(x, y , w, h, color);
  tft.fillRect(x+6, y-4 , w-12 , 4, color);
  tft.fillRect(x+16, y-8 , w-32, 4, color);
  tft.fillRect(x+26, y-12 , w-52, 4, color);
  tft.fillRect(x+5, y+h , w-10, 8, color);
  tft.fillRect(x+10, y+h+8 , w-20, 4, color);
  tft.fillRect(x+15, y+h+12 , w-30, 4, color);
//vẽ các cửa sổ 
  // trước
    tft.fillRect(x+26, y+25 , w-52, 5, BLACK);    
    tft.fillRect(x+16, y+30 , w-32, 10, BLACK);
    tft.fillRect(x+11, y+40 , w-22, 3, BLACK);
    tft.fillRect(x+16, y+43 , w-32, 5, BLACK);
    tft.fillRect(x+21, y+48 , 10, 5, BLACK);
    tft.fillRect(x+w-31, y+48 , 10, 5, BLACK);
  // sau
    tft.fillRect(x+20, y+h-8 , w-40, 10, BLACK);  
    tft.fillRect(x+40, y+h+2 , w-80, 5, BLACK);
  // cửa sổ 2 bên
    tft.fillRect(x+11, y+53 , 4, h-60, BLACK);
    tft.fillRect(x+w-16, y+53 , 4, h-60, BLACK);
    tft.fillRect(x, y+86 , w, 7, color);
    tft.fillRect(x, y+121 , w, 5, color);
}

void drawCar1(int x, int y, int w, int h, uint16_t color) {
// vẽ thân xe
  tft.fillRect(x, y , w, h, color);
  tft.fillRect(x+6, y-4 , w-12 , 4, color);
  tft.fillRect(x+16, y-8 , w-32, 4, color);
  tft.fillRect(x+26, y-12 , w-52, 4, color);
  tft.fillRect(x+5, y+h , w-10, 8, color);
  tft.fillRect(x+10, y+h+8 , w-20, 4, color);
  tft.fillRect(x+15, y+h+12 , w-30, 4, color);
//vẽ cửa sổ xe
  // trước
    tft.fillRect(x+26, y+25 , w-52, 5, BLACK);  
    tft.fillRect(x+16, y+30 , w-32, 10, BLACK);
    tft.fillRect(x+11, y+40 , w-22, 3, BLACK);
    tft.fillRect(x+16, y+43 , w-32, 5, BLACK);
    tft.fillRect(x+21, y+48 , 10, 5, BLACK);
    tft.fillRect(x+w-31, y+48 , 10, 5, BLACK);
  // sau  
    tft.fillRect(x+20, y+h-8 , w-40, 10, BLACK);  
    tft.fillRect(x+40, y+h+2 , w-80, 5, BLACK);
  // cửa sổ 2 bên
    tft.fillRect(x+11, y+53 , 4, h-60, BLACK);
    tft.fillRect(x+w-16, y+53 , 4, h-60, BLACK);
    tft.fillRect(x, y+86 , w, 7, color);
    tft.fillRect(x, y+121 , w, 5, color);
    tft.fillRect(x, y+53 , 5, 37, BLACK);  
  // mở cửa
    tft.fillTriangle(x, y+53, x+3, y+58, x-15, y+90, RED);
    tft.fillTriangle(x, y+53, x-15, y+90, x-18, y+85, RED);
      delay(500);
  // đóng cửa
    tft.fillTriangle(x, y+53, x+3, y+58, x-15, y+90, color);
    tft.fillTriangle(x, y+53, x-15, y+90, x-18, y+85, color);
      delay(500); 
}
void drawHalfCircle(int x, int y, int r, uint16_t color) {
  // Tính góc bắt đầu và kết thúc
  int startAngle = 270;
  int endAngle = 360;
  // Vẽ các điểm trên nửa hình tròn
  for (int angle = startAngle; angle < endAngle; angle++) {
    // Tính tọa độ x và y của điểm
    int px = 120 + 15 * cos(angle * PI / 180);
    int py = 25 + 15 * sin(angle * PI / 180);
    // Vẽ điểm màu xanh
    tft.drawPixel(px, py, color);}

  int stAngle = 0;
  int eAngle = 90;
    // Vẽ các điểm trên nửa hình tròn
    for (int angle = stAngle; angle < eAngle; angle++) {
      // Tính tọa độ x và y của điểm
      int x = 120 + 15 * cos(angle * PI / 180);
      int y = 25 + 15 * sin(angle * PI / 180);
      // Vẽ điểm màu xanh
      tft.drawPixel(x, y, color);  }
    // vẽ các đường thẳng màu xanh trên đèn báo pha
      tft.fillRect(118,10,3,30,BLUE);
      tft.fillRect(97,10,18,2,BLUE);
      tft.fillRect(97,38,18,2,BLUE);
      tft.fillRect(98,19,16,2,BLUE);
      tft.fillRect(98,29,16,2,BLUE);
}
