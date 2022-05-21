void setup()
{
  DDRB = 0b00000011;
  DDRD = 0b11111110;
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}


void loop()
{
  int decimal = (digitalRead(13)* 8)+ (digitalRead(12)*4) +(digitalRead(11)*2)+ digitalRead(10);
  int ttens = decimal / 10;
  int oones = decimal % 10;
  disp(ttens, oones);
}

void start()
{ int i = 2;
  while (i != 0)
  {
    if (i == 2)
    {
      PORTB = 0b00000010;
    }
    if (i == 1)
    {
      PORTB = 0b00000001;
    }
    PORTD = 0b00000010;
    delay(100);
    PORTD = 0b00000110;
    delay(100);
    PORTD = 0b00001110;
    delay(100);
    PORTD = 0b00011110;
    delay(100);
    PORTD = 0b00111110;
    delay(100);
    PORTD = 0b01111110;
    delay(100);
    PORTD = 0b11111110;
    delay(200);
    PORTD = 0b01111110;
    delay(100);
    PORTD = 0b00111110;
    delay(100);
    PORTD = 0b00011110;
    delay(100);
    PORTD = 0b00001110;
    delay(100);
    PORTD = 0b00000110;
    delay(100);
    PORTD = 0b00000010;
    delay(100);
    PORTD = 0b00000000;
    delay(200);
    i--;
  }
}

void zero()
{
  PORTD = 0b01111110;
}

void one()
{
  PORTD = 0b00001100;
}

void two()
{
  PORTD = 0b10110110;
}

void three()
{
  PORTD = 0b10011110;
}

void four()
{
  PORTD = 0b11001100;
}

void five()
{
  PORTD = 0b11011010;
}

void six()
{
  PORTD = 0b11111010;
}

void seven()
{
  PORTD = 0b00001110;
}

void eight()
{
  PORTD = 0b11111110;
}

void nine()
{
  PORTD = 0b11001110;
}

void digit1(int x)
{
  PORTB = 0b00000001;
  switch (x) {
    case 1: one(); break;
    case 2: two(); break;
    case 3: three(); break;
    case 4: four(); break;
    case 5: five(); break;
    case 6: six(); break;
    case 7: seven(); break;
    case 8: eight(); break;
    case 9: nine(); break;
    case 10: zero(); break;
    case 0: zero(); break;
  }
}

void digit2(int x)
{
  PORTB = 0b000000010;
  switch (x) {
    case 1: one(); break;
    case 2: two(); break;
    case 3: three(); break;
    case 4: four(); break;
    case 5: five(); break;
    case 6: six(); break;
    case 7: seven(); break;
    case 8: eight(); break;
    case 9: nine(); break;
    case 0: zero(); break;
    case 10: zero(); break;
  }
}

void disp(int i, int j)
{
  digit1(i);
  delay(10);
  digit2(j);
  delay(10);
}
