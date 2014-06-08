// Control Lego Power Functions

// Pinout
#define POT_INPUT A1
#define PWM_OUT1 6
#define CTRL1 7
#define CTRL2 8

void setup() 
{
  TCCR0B &= ~(CS02 | CS01 |CS00);
  TCCR0B |= CS00;
}

void loop() 
{
  int pot = 0;
  pot = analogRead(POT_INPUT);
  if(pot < 500)
  {
    // forward
    digitalWrite(CTRL1, HIGH);
    digitalWrite(CTRL2, LOW);
    analogWrite(PWM_OUT1, 255 - (pot >>1));
    // speed up the PWM on pin 6
  }
  else
  {
    if(pot > 524)
    {
      // Reverse
      digitalWrite(CTRL2, HIGH);
      digitalWrite(CTRL1, LOW);
      analogWrite(PWM_OUT1, (pot - 513) >>1);
      // speed up the PWM on pin 6
    }
    else
    {
      // Stopped
      analogWrite(PWM_OUT1, 0);
      
    }
  }
}
