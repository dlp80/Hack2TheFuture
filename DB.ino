#include <LiquidCrystal.h>

LiquidCrystal lcd(3, 5, 6, 7, 9, 10);


const int MIC = A0; //the MICrophone amplifier output is connected to pin A0

const int LED2 = 22;
const int LED1 = 26;
const int LED3 = 30;
const int LED4 = 34;
const int LED5 = 38;
const int LED6 = 42;
const int LED7 = 46;
const int LED8 = 50;
int v = 0;


int pausey = 0;

int x;

int button1 = 2;
int button2 = 4; //the variable that will hold the value read from the MICrophone each time
int button3 = 8;

double High, Low, Delta;


void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);


  Serial.begin(9600); //sets the baud rate at 9600 so we can check the values the MICrophone is obtaining on the Serial Monitor
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(MIC, INPUT);
  //Serial.println("Hello World");


  // put your setup code here, to run once:
  lcd.begin(16, 2);

  High = 0;
  Low = 100000;
}


void loop() {


  //ADD CODE HERE TO ASK IF DEFAULT OR NOT
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print("Hello! Welcome 2");
  delay(3000);

  lcd.setCursor(1, 1);
  lcd.print("Speech-O-meter!");

  //3 second delay
  delay(3000);
  //clear
  lcd.clear();

  //interface for choosing between default voice bins or custom ones
  lcd.print("Would you like");
  lcd.setCursor(1, 1);
  lcd.print("Default mode?");


  delay(3000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("or Custom mode?");

  delay(3000);
  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("Hold Button Down");

  delay(500);

  lcd.setCursor(0, 1);
  lcd.print("To Make Choice");

  delay(3000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("You Have");

  lcd.setCursor(0, 1);
  lcd.print("5 seconds");

  delay(5000);
  lcd.clear();


  if (digitalRead(button1) == LOW)  x = 0;
  else if (digitalRead(button2) == LOW)  x = 1;


  if (x == 0)
  {
    Serial.println("Default Value code");
    Low = 250;
    High = 320;
    Delta = (High - Low) / 7;
  }
  if (x == 1)
  {
    Serial.println("HOLD BUTTON TO STOP measuring your voice levels");

    while (1)
    {
      if (analogRead(MIC) > High) High = analogRead(MIC);
      if (analogRead(MIC) < Low && analogRead(MIC) > 250) High = analogRead(MIC) + 40;

      if (digitalRead(button1) == LOW) break;
    }

    Delta = (High - Low) / 7;
  }


  int y = 0;

 
  int p  = 0;
  
  while (y == 0)
  {

    // INSERT HOLD BUTTON TO STOP PRINT //

    // ODAY CODE START //
    v = analogRead(MIC);
    Serial.println(v);


    // Checking The Volume Of the LEDS
    if (v <= Low)
    {
      // creating flashing mechanism for Volume that is at Noise Level
      digitalWrite(LED1, HIGH);

      
     p = 0;
    }
    else
      digitalWrite(LED1, LOW);

    v = analogRead(MIC);

    if (v > Low)
    {

      digitalWrite(LED2, HIGH);


      p++;
    }
    else
      digitalWrite(LED2, LOW);

    v = analogRead(MIC);

    if (v > (Low + Delta))
    {

      digitalWrite(LED3, HIGH);

      p = 0;
    }
    else
      digitalWrite(LED3, LOW);

    v = analogRead(MIC);

    if (v > (Low + (2 * Delta)))
    {

      digitalWrite(LED4, HIGH);

      p = 0;
    }
    else
      digitalWrite(LED4, LOW);

    v = analogRead(MIC);

    if (v > (Low + (3 * Delta)))
    {

      digitalWrite(LED5, HIGH);

      p = 0;
    }
    else
      digitalWrite(LED5, LOW);

    v = analogRead(MIC);

    if (v > (Low + (4 * Delta)))
    {

      digitalWrite(LED6, HIGH);

      p = 0;
    }
    else
      digitalWrite(LED6, LOW);

    v = analogRead(MIC);

    if (v > (Low + (5 * Delta)))
    {

      digitalWrite(LED7, HIGH);

      p = 0;
    }
    else
      digitalWrite(LED7, LOW);

    v = analogRead(MIC);

    if (v > (Low + (6 * Delta) + 40))
    {

      // creating flashing mechanism for Volume that is at Noise Level
      digitalWrite(LED8, HIGH);

      p = 0;
    }
    else
      digitalWrite(LED8, LOW);

    // ODAY CODE END //

    if (p == 1000)
    {
      
      lcd.setCursor(0, 0);
      lcd.print("Pause");
      lcd.setCursor(0, 1);
      lcd.print("Detected!");
      delay(2000);
      lcd.clear();

      p = 0;
      pausey++;
    }

    if (digitalRead(button3) == LOW)
    {
      Serial.println("Button Pushed");
      y = 1;
    }

  }

  if (pausey <= 3)
  {
    lcd.setCursor(0, 0);
    lcd.print("GOOD JOB!!!");
    lcd.setCursor(0, 1);
    lcd.print("  <3  ");
    delay(3000);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("You Paused 3");
    lcd.setCursor(0, 1);
    lcd.print(" Or less Times ");
    delay(3000);
    lcd.clear();
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("You Paused More");
    lcd.setCursor(0, 1);
    lcd.print("Than 3 Times");
    delay(3000);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Keep Practicing");
    delay(3000);
    lcd.clear();

  }

}
