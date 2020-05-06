/*
 * BLINK Tester (This Code Tests the Basic Functionality of MicroControllers)
 * https://www.instagram.com/siddhantshah2212/
 * https://www.github.com/SiddhantShah2001/BlinkTester
 */

// [NOTE] Tested with Arduino(Mini, Nano, Uno, Mega) & ESP(8266, 32)

/*
 # Parts Needed:
 * 01. Development Board/MicroController + Suitable USB Cable (To Connect to the Computer).
 * 02. [OPTIONAL] LED + 220Ω Resistor.
 */

/*
 # STEPS:
 * 01. Connect your Development Board/MicroController to the Computer.
 * 02. Select Board from: Tools > Board > (Select the Board you are Using) <. [NOTE] You will Need to Install 3rd Party Non-Arduino Development Boards.
 * 03. Select the Right COM Port for your Microcontroller from: Tools > Port > (Select the COM Port used by your Board) <. 
 * 04. Press Upload.
 * 05. Open Serial Monitor from: Tools > Serial Monitor < (CTRL + SHIFT + M).
 * 06. Set Line Ending to "Both NL & CR" (Both New Line and Carriage Return).
 * 07. Set Baud Rate to "9600".
 */

// [ERROR] If No LED is Blinking but there is Data Being Updated on Serial Monitor, Connect an External LED with a 220Ω Resistor to the "BUILTIN_LED" Pin (Line 4 on Serial Monitor(>>Built-In LED Pin Number "?")). LED Cathode -> GND/Negative, LED Anode -> 220Ω Resistor -> I/O Pin of MicroController.

// Setup Function for Initial Non-Repetitive Tasks. Executes Only Once at the Time of Boot.
void setup() 
{
  Serial.begin(9600);                                                                                                                             // Initialize Serial Communication with a Baud Rate of 9600 bps (bits per second).
  // F() Macros are used to Store the String Content in Flash(Program) Memory, by Default they are Stored in RAM.
  Serial.println();                                                                                                                               // Leave a Line (Spacer).
  Serial.print(F("Arduino Code File Used \"")); Serial.print(__FILE__); Serial.println(F("\""));                                                  // Print the Name/Path of Program File Uploaded using "__FILE__" Macro.
  Serial.print(F("Uploaded on ")); Serial.println(__DATE__);                                                                                      // Print the Date on which the MicroController was Flashed with the Above Mentioned Program File using the "__DATE__" Macro.
  Serial.println();                                                                                                                               // Leave a Line (Spacer).
  Serial.println(F(">>MicroController Built-In LED Blink Tester (This Code Tests PORT Manipulation, TIMER Registers and Serial Communication)")); // Print the Following String on Serial Monitor.
  Serial.print(F(">>Built-In LED Pin Number ")); Serial.println(LED_BUILTIN);                                                                     // Print the Number of Pin used as the Built-in LED Pin.
  Serial.println();                                                                                                                               // Leave a Line (Spacer).
  Serial.println(F("#Press 0 to Pause and 1 to Resume Blinking (LED is Blinking by Default)"));                                                   // Print the Following String on Serial Monitor.
  Serial.println();                                                                                                                               // Leave a Line (Spacer).
  
  pinMode(LED_BUILTIN, OUTPUT);                                                                                                                   // Set Data Direction Register for the Specified Pin to 1 (OUTPUT).
  digitalWrite(LED_BUILTIN, LOW);                                                                                                                 // Set PORT Register for the Specified Pin to 0 (LOW).
}

// Loop Function for Continous Code Execution (in a Loop). Goes on Forever.
void loop() 
{
  // Local Variables (Visible to only this Function)
  static bool state = true;                                                                                                                       // Create Local Variable named "state" with Initial Value as "1/HIGH/true" (LED is Blinking by Default after a Power Cycle).
  static int time = 500;                                                                                                                          // Create Local Variable named "time" with Initial Value as "500" (Default Blinking Rate for LED is 500mS after a Power Cycle).
  if (Serial.available())                                                                                                                         // If there's Incoming Serial Data, do/check the Following.
  {
    uint8_t data = Serial.read();                                                                                                                 // Create Local Variable named "data" with the Value Returned from "read" Function of Serial Object.
    if (data == 48 && state == true)                                                                                                              // If the Received data is '0'(ASCII 48) and current Value of "state" is "true". Do the Following.
    {
      state = false;                                                                                                                              // Set "state" Value to "false" (Stop Blinking).
      time = 5000;                                                                                                                                // Set "time" Value to "5000" (Next Update in 5 Seconds).
      Serial.println(F("Blinking Paused! (Update Interval 5 Secs)"));                                                                             // Print the Following String on Serial Monitor.
    }
    else if (data == 49 && state == false)                                                                                                        // Otherwise If the Received data is '1'(ASCII 49) and current Value of "state" is "false". Do the Following.
    {
      state = true;                                                                                                                               // Set "state" Value to "true" (Start Blinking).
      time = 500;                                                                                                                                 // Set "time" Value to "500" (Next Update in 0.5 Seconds).
      Serial.println(F("Blinking Resumed! (Update Interval 0.5 Secs)"));                                                                          // Print the Following String on Serial Monitor.
    }
  }
  blink(state,time);                                                                                                                              // Call "blink" Function with Parameters Being Blink State and Blink Duration.
}

// Custom User Defined Function Called "blink" with Arguements being Blink State and Blink Duration.
void blink(bool flash, int duration)
{
  static unsigned long counter = 0;                                                                                                               // Create Local Variable named "counter" with Initial Value as "0". (Counts the Number of Times the State was Updated)
  unsigned long currentTime = millis();                                                                                                           // Create Local Variable named "currentTime" with Values Returned "millis()" Function. (Records Current System Time in MilliSeconds)
  static unsigned long previousTime = 0;                                                                                                          // Create Local Variable named "previousTime" with Initial Value as "0". (Keeps Track of Time after Last Update)
  if (currentTime - previousTime >= duration)                                                                                                     // If Current System Time is Subracted by the Last Time the State was Updated and the Remainder is Greater than or Equal to the Duration, do the Following.
  {
    previousTime = currentTime;                                                                                                                   // Set Previous Update Time to Current Time.
    counter++;                                                                                                                                    // Add 1 to the "counter" Variable.
    Serial.print(F("#")); Serial.print(counter); Serial.print(F(". "));                                                                           // Print the Counter Value on Serial Monitor.
    if (!flash)                                                                                                                                   // If Blinking is Disabled, do the Following.
    {
      Serial.println(F("PAUSED!"));                                                                                                               // Print the Following String on Serial Monitor.
      Serial.print(F("Total System Time: ")); Serial.print(currentTime); Serial.println(F("mS"));                                                 // Print Total System Time Since Boot.
      Serial.println();                                                                                                                           // Leave a Line (Spacer).
      return;                                                                                                                                     // Return From Here and Don't Execute any Line of Code after it.
    }
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));                                                                                         // Set the Next Led State to the Opposite of Current Led State. (Turn On if it's OFF, and Vice Versa)
    Serial.print(F("Built-in LED turned "));                                                                                                      // Print the Following String on Serial Monitor.
    digitalRead(LED_BUILTIN)?Serial.println(F("ON")):Serial.println(F("OFF"));                                                                    // Check the Logic State of LED and Print the State Accordingly.
    Serial.print(F("Total System Time: ")); Serial.print(currentTime); Serial.println(F("mS"));                                                   // Print Total System Time Since Boot.
    Serial.println();                                                                                                                             // Leave a Line (Spacer).
  }
}
