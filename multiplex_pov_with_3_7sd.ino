
/*
Example to demonstrate how MULTIPLEX 
and POV (Persistence of Vison) works, 
using 3 Seven Segment Display on Arduino.
(No expansion ports used)

Licensed under MIT License.

02/03/2015 Gilmar Palega

*/

int pausa = 1;

const int pin_pot = A5;
const int pin_tempo = A4;

const int pin_a = 7;
const int pin_b = 8;
const int pin_c = 9;
const int pin_d = 10;
const int pin_e = 11;
const int pin_f = 12;
const int pin_g = 3;

const int pin_com1 = 4;
const int pin_com2 = 5;
const int pin_com3 = 6;


void setup() {               
  pinMode(pin_a, OUTPUT);  
  pinMode(pin_b, OUTPUT);  
  pinMode(pin_c, OUTPUT);  
  pinMode(pin_d, OUTPUT);  
  pinMode(pin_e, OUTPUT);  
  pinMode(pin_f, OUTPUT);    
  pinMode(pin_g, OUTPUT);  
  
  pinMode(pin_com1, OUTPUT);  
  pinMode(pin_com2, OUTPUT);  
  pinMode(pin_com3, OUTPUT); 

  pinMode(pin_pot, INPUT); 
  pinMode(pin_tempo, INPUT); 
  
  //Serial.begin(9600);
  
}


/*
Conversion table number to bit
If a segment is used to compose the digit, then sum the bit value

	A	B	C	D	E	F	G	
#	1	2	4	8	16	32	64	
------------------------------------------------------------------								
0	1	1	1	1	1	1		63
1		1	1					6
------------------------------------------------------------------
2	1	1		1	1		1	91
3	1	1	1	1			1	79
------------------------------------------------------------------
4		1	1			1	1	102
5	1		1	1		1	1	109
------------------------------------------------------------------
6	1		1	1	1	1	1	125
7	1	1	1					7
------------------------------------------------------------------
8	1	1	1	1	1	1	1	127
9	1	1	1			1	1	103
*/
int get_7SD_value(int n) {
  if (n>9) n=9;
  if (n<0) n=0;
 
  switch(n) {
    case 0: return 63; break;
    case 1: return 6; break;
    case 2: return 91; break;
    case 3: return 79; break;
    case 4: return 102; break;
    case 5: return 109; break;
    case 6: return 125; break;
    case 7: return 7; break;
    case 8: return 127; break;
    case 9: return 103;
  }
  return 0;
}


/*
ATTENTION: I'm using Common Anodes 7 Segment Display.
For Commom Cathodes, you have to invert HIGH and LOW on code bellow.
*/

void check_pin(int pin, int b) {
    if (b == 1) {
      digitalWrite(pin, LOW); 
      delay(pausa);
      digitalWrite(pin, HIGH);  
    } else 
      digitalWrite(pin, HIGH);
}


/*
ATTENTION: I'm using Common Anodes 7 Segment Display.
For Commom Cathodes, you have to invert HIGH and LOW on code bellow.
*/

void display_7sd(int v, int pin_com) {
  if (v>9) v=9;
  if (v<0) v=0;
  
  int n = get_7SD_value(v);
  
  /* turn on common */
  digitalWrite(pin_com, HIGH);
  
  
  /* check all segments, and turn on the necessary ones to compose the number */
  check_pin(pin_a, bitRead(n, 0));
  check_pin(pin_b, bitRead(n, 1));
  check_pin(pin_c, bitRead(n, 2));
  check_pin(pin_d, bitRead(n, 3));  
  check_pin(pin_e, bitRead(n, 4));
  check_pin(pin_f, bitRead(n, 5));
  check_pin(pin_g, bitRead(n, 6));

  /* turn off common */
  digitalWrite(pin_com, LOW);     
}

void display_value(int v) {
  int n;
  
  // Print hundred part - first digit
  n = v / 100;  
  v = v - (n*100);
  display_7sd(n, pin_com1);
  
  // Print decimal part - second digit  
  n = v / 10;
  v = v - (n*10);
  display_7sd(n, pin_com2);
  
  // Print the unit, the remainder - third digit  
  display_7sd(v, pin_com3);
  
  
}  


void loop() {
	
  int tpot = analogRead(pin_pot);
  pausa = analogRead(pin_tempo) + 1;

  if (tpot > 999) tpot=999;
  display_value(tpot);

}
