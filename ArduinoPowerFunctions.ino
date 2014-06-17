// Control Lego Power Functions

// Pinout
#define POT_INPUT A1
#define PWM_OUT1 6
#define CTRL1 7
#define CTRL2 8

// Range macro: like a switch, but with ranges instead of single values!
#define RANGE(V, L, U, R) if((L <= V) && (U >= V)) return R;

int check_Range(int adc)
{
  RANGE(adc, 0, 34, 0);
  RANGE(adc, 34, 83, 68);
  RANGE(adc, 83, 112, 97);
  RANGE(adc, 112, 144, 126);
  RANGE(adc, 144, 177, 162);
  RANGE(adc, 177, 207, 191);
  RANGE(adc, 207, 239, 223);
  RANGE(adc, 239, 255, 255);
}

void setup() 
{
  TCCR0B &= ~(CS02 | CS01 |CS00);
  TCCR0B |= CS02;
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
    analogWrite(PWM_OUT1, check_Range(255 - (pot >>1)));
    // speed up the PWM on pin 6
  }
  else
  {
    if(pot > 524)
    {
      // Reverse
      digitalWrite(CTRL2, HIGH);
      digitalWrite(CTRL1, LOW);
      analogWrite(PWM_OUT1, check_Range((pot - 513) >>1));
      // speed up the PWM on pin 6
    }
    else
    {
      // Stopped
      analogWrite(PWM_OUT1, 0);
      
    }
  }
}
