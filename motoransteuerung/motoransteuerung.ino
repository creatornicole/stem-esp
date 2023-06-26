/////////////////////////////////////////////////////////////////////////////
//
// Program to test how to control the direction and speed of a DC motor
// Using ESP32 and L298N Motor Driver
//
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// TODO:
// Check Function of DC motor (PWM and Enable Pin implemented correct?)
//
/////////////////////////////////////////////////////////////////////////////

// Motor A //////////////////////////////////////////////////////////////////
// GPIOs the motor pins are connected to
// Motor Spin Forward: IN1 LOW, IN2 HIGH
// Motor Spin Backwards: IN1 HIGH, IN2 LOW
const int motor1Pin1 = ; // connected to IN1 L298N Motor Driver
const int motor1Pin2 = ; // connected to IN2 L298N Motor Driver

// Enable Pin for Motor A
// Motor enabled (ON) - HIGH
// Motor not enabled (OFF) - LOW
const int enable1Pin = ;

// Setting PWM properties ///////////////////////////////////////////////////
// PWM signal to enable pin of motor driver to control speed (proportional to duty cycle)
const int freq = 30000; // 30000 Hz
const int pwmChannel = 0; // Channel 0
const int resolution = 8; // 8-bit resolution
int dutyCycle = 200; // possible duty cycle value from 0 to 255
                     // for frequency of 30000, duty cycle < 200 -> motor won't move

// Set Up Code
void setup() {
  // Set Up Pins as Outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  // Configure PWN signal
  ledcSetup(pwmChannel, freq, resolution);

  // Attach Channel to the GPIO to be controlled
  // Define from where to get the signal
  ledcAttachPin(enable1Pin, pwmChannel);

  Serial.begin(9600);
}

// Main Code - run repeadtedly
void loop() {

    // move DC motor forward at maximum speed
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motro1Pin2, HIGH);

    delay(200);

    // stop DC motor
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motro1Pin2, LOW);

    delay(200);

    // move DC motor backwards at maximum speed
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    
    delay(200);

    // stop DC motor
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motro1Pin2, LOW);
   
}
