// Code cho arduino nano, làm nút truyền
#include <mcp2515.h> // Thư viện mcp2515
#define CS_PIN 10 // Chân CS của mcp2515
#define INT_PIN 2 // Chân INT của mcp2515
#define SWITCH_PIN 3 // Chân nối với chân trái công tắc on-off-on
#define SWITCH_PIN1 4 // Chân nối với chân phải công tắc on-off-on
#define BUTTON_PIN 5 // Chân nối với button

struct can_frame canMsg;
MCP2515 mcp2515(CS_PIN); // Khởi tạo đối tượng mcp2515

void setup() {
  Serial.begin(9600); // Bắt đầu giao tiếp nối tiếp
  pinMode(SWITCH_PIN, INPUT_PULLUP); // Cài đặt chân công tắc là đầu vào
  pinMode(SWITCH_PIN1, INPUT_PULLUP); 
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  SPI.begin(); // Bắt đầu giao tiếp SPI
  mcp2515.reset(); // Đặt lại mcp2515
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); // Cài đặt tốc độ bit và tần số dao động
  mcp2515.setNormalMode(); // Cài đặt chế độ bình thường
}

void loop() {
  int switchState = digitalRead(SWITCH_PIN); // Đọc trạng thái của công tắc
  int switchState1 = digitalRead(SWITCH_PIN1); // Đọc trạng thái của công tắc
  int buttonState = digitalRead(BUTTON_PIN);// Đọc trạng thái nút nhấn

if (switchState == LOW && switchState1 == HIGH  ) { // Nếu công tắc ở vị trí off
    canMsg.can_id = 0x260; // Cài đặt ID của tin nhắn
    canMsg.can_dlc = 0x03; // Cài đặt độ dài của tin nhắn
    canMsg.data[0] = 25; // Cài đặt byte 1 là 0
    canMsg.data[1] = 0x03; // Cài đặt byte 2 là 03
    canMsg.data[2] = 0x80; // Cài đặt byte 3 là 80
  }
  else if (switchState == HIGH && switchState1 == LOW ) { // Nếu công tắc ở vị trí on
    canMsg.can_id = 0x260; // Cài đặt ID của tin nhắn
    canMsg.can_dlc = 0x03; // Cài đặt độ dài của tin nhắn
    canMsg.data[0] = 25; // Cài đặt byte 1 là 25
    canMsg.data[1] = 0x3A; // Cài đặt byte 2 là 3A
    canMsg.data[2] = 0x80; // Cài đặt byte 3 là 80
  } 
  else if (switchState == HIGH && switchState1 == HIGH ) { // Nếu điện áp ở chân A0 nhỏ hơn 2.5V
    canMsg.can_id = 0x260; // Cài đặt ID của tin nhắn
    canMsg.can_dlc = 0x03; // Cài đặt độ dài của tin nhắn
    canMsg.data[0] = 0; // Cài đặt byte 1 là 0
    canMsg.data[1] = 0; // Cài đặt byte 2 là 0
    canMsg.data[2] = 0; // Cài đặt byte 3 là 0
  }
  mcp2515.sendMessage(&canMsg); // Gửi tin nhắn qua mcp2515
    Serial.print("Đã gửi tin nhắn: ID = "); // In ra Serial
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
  if (buttonState == LOW) {
    canMsg.can_id = 0x405; // Cài đặt ID của tin nhắn
    canMsg.can_dlc = 0x06; // Cài đặt độ dài của tin nhắn
    canMsg.data[0] = 0; // Cài đặt byte 1 là 0
    canMsg.data[1] = 0; // Cài đặt byte 2 là 0
    canMsg.data[2] = 0; // Cài đặt byte 3 là 0
    canMsg.data[3] = 0x20; // Cài đặt byte 4 là 20
    canMsg.data[4] = 0; // Cài đặt byte 5 là 0
    canMsg.data[5] = 0; // Cài đặt byte 6 là 0
  } 
  else {
    canMsg.can_id = 0x405; // Cài đặt ID của tin nhắn
    canMsg.can_dlc = 0x06; // Cài đặt độ dài của tin nhắn
    canMsg.data[0] = 0; // Cài đặt byte 1 là 0
    canMsg.data[1] = 0; // Cài đặt byte 2 là 0
    canMsg.data[2] = 0; // Cài đặt byte 3 là 0
    canMsg.data[3] = 0; // Cài đặt byte 4 là 0
    canMsg.data[4] = 0; // Cài đặt byte 5 là 0
    canMsg.data[5] = 0; // Cài đặt byte 6 là 0
  }
  mcp2515.sendMessage(&canMsg); // Gửi tin nhắn qua mcp2515
    Serial.print("Đã gửi tin nhắn: ID = "); // In ra Serial
    Serial.print(canMsg.can_id, HEX); // In ra ID của tin nhắn
    Serial.print(", DLC = "); // In ra DLC của tin nhắn
    Serial.print(canMsg.can_dlc, HEX); // In ra độ dài của tin nhắn
    Serial.print(", DATA = "); // In ra dữ liệu của tin nhắn
    Serial.print(canMsg.data[0]);
  for (int j = 1; j < canMsg.can_dlc; j++) {
    Serial.print(" ");
    Serial.print(canMsg.data[j], HEX); // In ra từng byte dữ liệu
  }
  Serial.println(); // Xuống dòng
  delay(1000); // Đợi 1 giây
}