//Conditional compile
#define DEBUG 0 // change to 1 to get serial debug output

// Pin definition macros
#define PowerCtrl 1 //Pin that controls the power switch

#define BoardTemp A0 //Connection the onboard thermometer

//Connection to the offboard thermometers
#define ExternTemp1 A1
#define ExternTemp2 A2

//Define constants
const float ADC_Scale = (5.0 / 1023.0);
const float Temp_Target = 30; //top plate value
const float Temp_Tol = 2.5; // From datasheet tolerance values

const float board_minTemp = -20;

//timer
int tic = 0;
int toc = 0;

#define updateDelay 100 //Delay control update by x ms


void setup() {
  #if DEBUG
    Serial.begin(9600);
  #endif
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  //Initialise heating ping to stop heating
  pinMode(PowerCtrl, OUTPUT);
  digitalWrite(PowerCtrl, HIGH);

  //Initialise thermometers to read (not necessary)
  pinMode(BoardTemp, INPUT);
  pinMode(ExternTemp1, INPUT);
  pinMode(ExternTemp2, INPUT);

  //start timer
  tic = millis();
}

float readTemp(int Pin) {
  //perform an analog read on the pin and convert to temperature
  int measure = analogRead(Pin); // 100µs
  float voltage = measure * ADC_Scale; // Convert to voltage

  /*Calculate temp as specified by TMP36 rev.H datasheet page 8 */
  return (voltage - 0.5) * 100;
}

void loop() {
  toc = millis();
  // first we wait for the 
  if (abs(tic - toc) < updateDelay) {
    // pass
  } else {
    tic = millis();
    //Check if the temperature is within bounds
    float board = readTemp(BoardTemp);
    float extern1 = readTemp(ExternTemp1);
    float extern2 = readTemp(ExternTemp2);

    #if DEBUG
      Serial.print(board - board_minTemp);
      Serial.print("\t");
      Serial.println(extern1-Temp_Target);
    #endif
    
    // if the viability conditions are met
    //Condition 1 board is dying
    if (board - board_minTemp < Temp_Tol) {
      digitalWrite(PowerCtrl, LOW); // Start heating
      digitalWrite(LED_BUILTIN, HIGH);

    //Condition 2 temperature sensor 1 is bad
    } else if (extern1 - Temp_Target < Temp_Tol) {
      digitalWrite(PowerCtrl, LOW); // Start heating
      digitalWrite(LED_BUILTIN, HIGH);
      
    } else {
      digitalWrite(PowerCtrl, HIGH); // Stop heating
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
