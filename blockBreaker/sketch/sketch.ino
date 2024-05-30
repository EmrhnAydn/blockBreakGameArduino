#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TM1637TinyDisplay.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define CLK 2  // Clock pin
#define DIO 1  // DIO pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TM1637TinyDisplay tm1637(CLK, DIO);


#define UP_BUTTON_PIN 9
#define DOWN_BUTTON_PIN 10
#define SELECT_BUTTON_PIN 11
#define LED_CAN_1 3
#define LED_CAN_2 4
#define LED_CAN_3 5
#define POT_PIN A0
#define BUZZER_PIN 12
#define BRICK_WIDTH 8
#define BRICK_HEIGHT 4
#define BRICK_GAP 1
#define BRICK_ROWS 5
#define BRICK_COLS 14
#define LDR_PIN A1

int ldrThreshold = 600; // LDR değeri için eşik değeri belirleyin
bool ldrHigh = false;

int brick[BRICK_ROWS][BRICK_COLS];
int canHakki = 3;
int gemiX = 0;
int menuSecimi = 0;
bool oyunBasladi = false;
int seviye = 1;
int upButtonState;
int downButtonState;
int selectButtonState;
const int numOptions = 2;
const char *menuOptions[numOptions] = {"START", "QUIT"};
int currentSelection = 0;
int score = 0;
int lvlScore = 0;
int topX = SCREEN_WIDTH / 2;
int topY = SCREEN_HEIGHT - 8;
int topSpeedX = 1;
int topSpeedY = -1;
int topSize = 3;
int brickCount;
int lvlNum = 1;
int heartX;
int heartY;
int hpChance;
int heartX1;
int heartY1;
int heartX2;
int heartY2;
int heartX3;
int heartY3;

bool hpMoveCnt = false;
bool menuCtrl = false; // if menu screen view second time, it will be true
bool gameLost = false;

void updateDisplay() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Menu:");
  display.setTextSize(1);
  display.println("-------------------");
  for (int i = 0; i < numOptions; i++) {
    if (i == currentSelection) {
      display.print("-> ");
    } else {
      display.print("   ");
    }
    display.print(menuOptions[i]);
    display.println();
  }
  display.println("-------------------");
  display.display();
}


void setup() {
  pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);
  pinMode(LED_CAN_1, OUTPUT);
  pinMode(LED_CAN_2, OUTPUT);
  pinMode(LED_CAN_3, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);  
  digitalWrite(LED_CAN_1, HIGH);
  digitalWrite(LED_CAN_2, HIGH);
  digitalWrite(LED_CAN_3, HIGH);
  
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  tm1637.setBrightness(0x0f);
  generateLevel();
  updateDisplay();
}

void clearBricks() {
  for (int i = 0; i < BRICK_ROWS; i++) {
    for (int j = 0; j < BRICK_COLS; j++) {
      brick[i][j] = 0;
    }
  }
}
void generateLevel() {

  brickCount = 0; 
  for (int i = 0; i < BRICK_ROWS; i++) {
    for (int j = 0; j < BRICK_COLS; j++) {
      brick[i][j] = random(0, 2);
      if(brick[i][j] == 1)
      {
        brickCount++;
      }
    }
  }
}
void resultScreen()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("U w U SUCCESS U w U");
  display.print("SCORE: ");
  display.println(score);
  display.println("-------------------");
  for (int i = 0; i < numOptions; i++) {
    if (i == currentSelection) {
      display.print("-> ");
    } else {
      display.print("   ");
    }
    display.print(menuOptions[i]);
    display.println();
  }
  display.println("-------------------");
  display.display();
}
void gameOver()
{
  
  lvlScore= 0;
  display.clearDisplay();
  clearBricks();
  display.setCursor(0, 0);
  display.println("-_- GAME OVER -_-");
  display.print("SCORE: ");
  display.println(score);
  score = 0;
  display.println("-------------------");
  for (int i = 0; i < numOptions; i++) {
    if (i == currentSelection) {
      display.print("-> ");
    } else {
      display.print("   ");
    }
    display.print(menuOptions[i]);
    display.println();
  }
  display.println("-------------------");
  display.display();
}


void loop() {
  
  upButtonState = digitalRead(UP_BUTTON_PIN);
  downButtonState = digitalRead(DOWN_BUTTON_PIN);
  selectButtonState = digitalRead(SELECT_BUTTON_PIN);

  if (upButtonState == LOW) {
    currentSelection--;
    if (currentSelection < 0) {
      currentSelection = numOptions - 1;
    }
    if(gameLost)
    {
      gameOver();
    }
    else if(menuCtrl){
      resultScreen();
    }
    else{
    updateDisplay();
    }
    delay(200);
  }

  if (downButtonState == LOW) {
    currentSelection++;
    if (currentSelection >= numOptions) {
      currentSelection = 0;
    }
    if(gameLost)
    {
      gameOver();
    }
    else if(menuCtrl){
      resultScreen();
    }
    else{
      updateDisplay();
    }
    delay(200);

  }

  if (selectButtonState == LOW) {
    if (currentSelection == 0 ) {
      if(menuCtrl){
        clearBricks();
        generateLevel();
        score = 0;
        lvlNum = 1;
        topX = gemiX + 6;
        topY = SCREEN_HEIGHT - 10;
        topSpeedX = 1;
        topSpeedY = -1;
        if(gameLost)
        {
          // new game
          gameLost = false;
          canHakki = 3;
          digitalWrite(LED_CAN_1, HIGH);
          digitalWrite(LED_CAN_2, HIGH);
          digitalWrite(LED_CAN_3, HIGH);
        }   
      }
      oyunBasladi = true;
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Selected:");
      display.println(menuOptions[currentSelection]);
      display.print("L E V E L ");
      display.print(lvlNum);
      display.display();
      delay(2000);
      updateDisplay();
    }
    else if (currentSelection == 1)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("///////////\\\\\\\\\\\\\\\\\\\\");
      display.println(" THANKS  FOR  PLAYING");
      display.println("\\\\\\\\\\\\\\\\\\\\///////////");
      display.println("U w U           U w U");
      display.println("       Creating");
      display.println("          by");
      display.println("   Emirhan & Havva");
      display.println("  IZMIT/KOCAELI 2024");
      display.display();
    }
  }

  if (oyunBasladi) {
    menuCtrl = true;
    gemiX = map(analogRead(POT_PIN), 0, 1023, 0, SCREEN_WIDTH - 8);

     int ldrValue = analogRead(LDR_PIN);
     ldrHigh = (ldrValue > ldrThreshold);
  
    //
    if(!ldrHigh){
      display.clearDisplay();
      display.fillRect(gemiX, 62, 12, 2, WHITE);
    }
    else
    {
      display.fillScreen(WHITE);
      display.fillRect(gemiX, 62, 12, 2, BLACK);
    }
    topX += topSpeedX;
    topY += topSpeedY;
    
    if (topX <= 0 || topX >= SCREEN_WIDTH - topSize) {
      topSpeedX *= -1;
    }

    if (topY <= 0) {
      topSpeedY *= -1;
    }

    if (topY >= SCREEN_HEIGHT - 8 && topX >= gemiX && topX <= gemiX + 12) {
      topSpeedY *= -1;
    }

    int hitBrickRow = -1;
    int hitBrickCol = -1;
    for (int i = 0; i < BRICK_ROWS; i++) {
      for (int j = 0; j < BRICK_COLS; j++) {
        if (brick[i][j] == 1 &&
            topX >= j * (BRICK_WIDTH + BRICK_GAP) && topX <= j * (BRICK_WIDTH + BRICK_GAP) + BRICK_WIDTH &&
            topY >= i * (BRICK_HEIGHT + BRICK_GAP) && topY <= i * (BRICK_HEIGHT + BRICK_GAP) + BRICK_HEIGHT) {
          hitBrickRow = i;
          hitBrickCol = j;
          break;
        }
      }
      if (hitBrickRow != -1) {
        break;
      }
    }

    if (hitBrickRow != -1 && hitBrickCol != -1) {
      brick[hitBrickRow][hitBrickCol] = 0;
      topSpeedY *= -1;
      score += 1;
      lvlScore += 1;
      tm1637.showNumberDec(score, true);
      hpChance = random(0,10);
      if(hpChance == 1 && hpMoveCnt == false) 
      {
        heartX = hitBrickCol * (BRICK_WIDTH + BRICK_GAP) + (BRICK_WIDTH / 2);
        heartY = hitBrickRow * (BRICK_HEIGHT + BRICK_GAP) + (BRICK_HEIGHT / 2);
        hpMoveCnt = true;
      }
    }

    if (hpMoveCnt) {
    // Kalp simgesini çiz
    heartX1 = heartX - 3;
    heartY1 = heartY + 3;
    heartX2 = heartX + 3;
    heartY2 = heartY + 3;
    heartX3 = heartX;
    heartY3 = heartY - 3;
    if(!ldrHigh){
    display.fillTriangle(heartX1, heartY1, heartX2, heartY2, heartX3, heartY3, WHITE);
    }
    else{
      display.fillTriangle(heartX1, heartY1, heartX2, heartY2, heartX3, heartY3, BLACK);
    }
    // Kalp simgesini aşağıya doğru hareket ettir
    heartY += 2;

    // Kalp simgesinin ekran dışına çıktığını kontrol et
    if (heartY >= SCREEN_HEIGHT) {
        hpMoveCnt = false; // Hareket etme işlemini durdur
    }

    // Kalp simgesinin oyuncuya ulaştığını kontrol et
    if (heartX >= gemiX && heartX <= gemiX + 12 && heartY >= SCREEN_HEIGHT - 8) {
        hpMoveCnt = false; // Hareket etme işlemini durdur
        // Oyuncunun canını artırma işlemini burada gerçekleştir
        if (canHakki == 2) {
            tone(BUZZER_PIN, 500, 100);
            digitalWrite(LED_CAN_1, HIGH);
            digitalWrite(LED_CAN_2, HIGH);
            digitalWrite(LED_CAN_3, HIGH);
        } else if (canHakki == 1) {
            tone(BUZZER_PIN, 500, 100);
            digitalWrite(LED_CAN_1, LOW);
            digitalWrite(LED_CAN_2, HIGH);
            digitalWrite(LED_CAN_3, HIGH);
        }
        if(canHakki < 3){
          canHakki++;
        }
    }
}

    if (topY >= SCREEN_HEIGHT) {
      
        topX = gemiX + 6;
        topY = SCREEN_HEIGHT - 10;
        delay(300);
        topSpeedY *= -1;

        canHakki--;
        if (canHakki == 2) {
          
          tone(BUZZER_PIN, 500, 100);
          digitalWrite(LED_CAN_1, LOW);
          digitalWrite(LED_CAN_2, HIGH);
          digitalWrite(LED_CAN_3, HIGH);
          
        } else if (canHakki == 1) {
          
          tone(BUZZER_PIN, 500, 100);
          digitalWrite(LED_CAN_1, LOW);
          digitalWrite(LED_CAN_2, LOW);
          digitalWrite(LED_CAN_3, HIGH);
        } else if (canHakki == 0) {
         
          tone(BUZZER_PIN, 500, 100); 
          digitalWrite(LED_CAN_1, LOW);
          digitalWrite(LED_CAN_2, LOW);
          digitalWrite(LED_CAN_3, LOW);
          oyunBasladi = false;
          lvlNum = 1;
          menuCtrl = true;
          gameLost = true;
          display.setCursor(15, 28);
          display.print("G A M E   O V E R ");
          display.display();
          delay(3000);         
          gameOver();
        }
    }
     if(!ldrHigh){
      display.fillCircle(topX, topY, topSize, WHITE);
     }
     else{
        display.fillCircle(topX, topY, topSize, BLACK);
     }

    for (int i = 0; i < BRICK_ROWS; i++) {
      for (int j = 0; j < BRICK_COLS; j++) {
        if (brick[i][j] == 1) {
           if(!ldrHigh){
            display.fillRect(j * (BRICK_WIDTH + BRICK_GAP), i * (BRICK_HEIGHT + BRICK_GAP), BRICK_WIDTH, BRICK_HEIGHT, WHITE);
           }
           else{
            display.fillRect(j * (BRICK_WIDTH + BRICK_GAP), i * (BRICK_HEIGHT + BRICK_GAP), BRICK_WIDTH, BRICK_HEIGHT, BLACK);
           }
        }
      }
    }
    
    display.display();
  }
  if (lvlScore == brickCount) {
    lvlScore =0;
    lvlNum++;
    if(lvlNum > 3)
    {
      oyunBasladi = false;
      lvlNum = 1;
      resultScreen();
    }
    else{
    display.clearDisplay();
    display.setCursor(40, 28);
    display.print("L E V E L ");
    display.print(lvlNum);
    display.display();
    delay(5000);
    clearBricks();
    generateLevel();
    topX = gemiX + 6;
    topY = SCREEN_HEIGHT - 10;   
    topSpeedY *= -2;
    updateDisplay();
    }
  }
}