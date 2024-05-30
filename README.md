# Arduino Brick Breaker Game

This project is an implementation of a classic Brick Breaker game using an Arduino board, an OLED display, a TM1637 7-segment display, buttons, a potentiometer, and other components. The game involves controlling a paddle to bounce a ball and break bricks, with additional features like lives and power-ups.

## Components

- Arduino Board (e.g., Arduino Uno)
- OLED Display (128x64, I2C)
- TM1637 7-segment Display
- Buttons (UP, DOWN, SELECT)
- Potentiometer
- LEDs (for representing lives)
- Buzzer
- Light Dependent Resistor (LDR)
- Resistors
- Jumper Wires
- Breadboard

## Pin Configuration

- OLED Display: Uses I2C (SCL and SDA pins)
- TM1637 7-segment Display: CLK pin to 2, DIO pin to 1
- UP Button: 9
- DOWN Button: 10
- SELECT Button: 11
- Potentiometer: A0
- LEDs: 3, 4, 5
- Buzzer: 12
- LDR: A1

## Setup Instructions

1. **Connect the Components:**
   - Wire the OLED display, TM1637 display, buttons, potentiometer, LEDs, buzzer, and LDR to the Arduino board as per the pin configuration above.

2. **Install the Required Libraries:**
   - Ensure you have the following libraries installed:
     - `Adafruit_GFX`
     - `Adafruit_SSD1306`
     - `TM1637TinyDisplay`

   You can install these libraries via the Arduino Library Manager (`Sketch` -> `Include Library` -> `Manage Libraries...`).

3. **Upload the Code:**
   - Copy the provided code into the Arduino IDE.
   - Verify and upload the code to your Arduino board.

## How to Play

1. **Start the Game:**
   - On startup, you will see a menu on the OLED display with options "START" and "QUIT".
   - Use the UP and DOWN buttons to navigate the menu.
   - Press the SELECT button to choose an option.

2. **Control the Paddle:**
   - Use the potentiometer to move the paddle left and right at the bottom of the screen.

3. **Gameplay:**
   - The goal is to bounce the ball using the paddle to break all the bricks on the screen.
   - You have 3 lives, represented by the LEDs. Each time you miss the ball, you lose a life.
   - Occasionally, a heart icon may fall; catching it with the paddle will restore a life.
   - The game progresses through multiple levels with increasing difficulty.
   - The game ends when all lives are lost.

4. **LDR Interaction:**
   - The LDR changes the display mode based on light levels. In bright light, the display inverts colors.

5. **Game Over and Victory:**
   - When all lives are lost, the game displays a "GAME OVER" screen.
   - If all levels are completed, a victory screen is displayed with your score.

## Authors

- Emirhan & Havva
- Izmit/Kocaeli 2024

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

