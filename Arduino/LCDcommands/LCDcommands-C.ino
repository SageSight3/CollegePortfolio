void setup() {
  // put your setup code here, to run once:
  // Function prototypes
  void ClearScreen();
  void SetDisplaySize();
  void SetContrast(int val);
  void SetBrightness(int val);
  void GoHome();
  void SetPosition(int column, int row);

  // Initialization code
  Serial.begin(9600);
  SetBrightness(10);
  SetContrast(180);
}

void loop() {
  // put your main code here, to run repeatedly:
  ClearScreen();              // clear LCD and return cursor to (1,1)
  Serial.println("I am home"); // print string to LCD, advance to next line
  delay(1000);
  Serial.print("Today is here");  // print string to LCD, do NOT adavance to next line
  delay(1000);
  SetPosition(5,1);
  //Serial.print(100);
  delay(1000);
}

// Clears the LCD display and returns to position (1,1)
void ClearScreen(){
  Serial.write(0xFE);
  Serial.write(0x58);
  delay(10);
}

// set the size of the display if it isn't 16x2 (you only have to do this once)
void SetDisplaySize(){
  Serial.write(0xFE);
  Serial.write(0xD1);
  Serial.write(16); // 16 columns
  Serial.write(2); // 2 rows
  delay(10);
}

// set the contrast, 200 is a good place to start, adjust as desired
// (maximum is 255 = 1 byte)
void SetContrast(int val){
  Serial.write(0xFE);
  Serial.write(0x50);
  Serial.write(val);
  delay(10);
}

// set the brightness of back light
// (max brightness is 255 = 1 byte)
void SetBrightness(int val){
  Serial.write(0xFE);
  Serial.write(0x99);
  Serial.write(val);
  delay(10);
}

// go 'home' means return cursor to position (1,1)
void GoHome(){
  Serial.write(0xFE);
  Serial.write(0x48);
  delay(10); // we suggest putting delays after each command
}

void SetPosition(int column, int row){
  Serial.write(0xFE);
  Serial.write(0x47);
  Serial.write(column);
  Serial.write(row);
}
