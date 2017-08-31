#include <IRremote.h> // Include the IRremote library

/* Connect the output of the IR receiver diode to pin 11. */
int RECV_PIN = 11;
/* Initialize the irrecv part of the IRremote  library */
IRrecv irrecv(RECV_PIN);
decode_results results; // This will store our IR received codes
IRsend irsend; // Enables IR transmit on pin 3

/* Storage variables for the received IR code: */
unsigned int irLen = 0; // The length of the code
unsigned int irBuffer[RAWBUF]; // Storage for raw (UNKNOWN) codes
const int buttonPin = 12; // Button pin. Pulled up. Triggered when connected to ground.

// DX Soul Chogokin Mazinger Z remote codes. Missing 1 to 3
static unsigned int button6 [RAWBUF]= {8750 ,4500 ,400 ,650 ,400 ,650 ,450 ,1600 ,400 ,650 ,400 ,700 ,400 ,600 ,450 ,650 ,400 ,1650 ,350 ,700 ,400 ,650 ,400 ,650 ,400 ,1600 ,450 ,650 ,400 ,1650 ,350 ,700 ,400 ,650 ,400 ,650 /**/,450 ,650 /**/,450 ,1550 /**/,400 ,650 ,450 ,1600 ,400 ,1650 ,400 ,1600 ,450 ,1600 ,400 ,1650 ,400 ,1650 /**/,400 ,650 /**/,400 ,1650 ,400 /**/,650 /**/,400 ,650 ,400 ,650 ,400 ,650 ,400};
static unsigned int button5 [RAWBUF]= {8750 ,4500 ,400 ,650 ,450 ,600 ,450 ,1600 ,400 ,650 ,400 ,700 ,400 ,650 ,450 ,600 ,400 ,1650 ,350 ,700 ,400 ,650 ,400 ,650 ,500 ,1550 ,400 ,650 ,400 ,1650 ,350 ,700 ,400 ,650 ,400 ,1650 /**/,400 ,1600 /**/,450 ,650 /**/,400 ,650 ,400 ,1650 ,400 ,1650 ,400 ,1600 ,400 ,1650 ,400 ,650 ,400 ,700 ,350 ,1650 ,400 ,1650 ,400 ,650 ,400 ,650 ,400 ,650 ,400 ,650 ,400};
static unsigned int button4 [RAWBUF]= {8750 ,4550 ,400 ,650 ,400 ,650 ,400 ,1650 ,400 ,650 ,400 ,650 ,400 ,650 ,450 ,600 ,400 ,1650 ,400 ,700 ,400 ,650 ,400 ,650 ,400 ,1600 ,400 ,700 ,400 ,1600 ,400 ,700 ,400 ,650 ,400 ,650 /**/,400 ,1650 /**/,400 ,650 /**/,400 ,650 ,400 ,1650 ,400 ,1600 ,450 ,1600 ,400 ,1650 ,400 ,1650 ,400 ,650 /**/,400 ,1650 /**/,400 ,1650 ,350 /**/,700 /**/,400 ,650 ,400 ,650 ,400 ,650 ,400};

static unsigned int counter = 1;

// setup() initializes serial and the Infrared receiver.
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(buttonPin, INPUT_PULLUP);
}

// loop() checks for either a button press or a received IR code.
void loop()
{
  if (irrecv.decode(&results)) 
  { 
    updateIRReceive(); // Sort out the received code
    irrecv.resume(); // re-enable receive
  }

  // If the button is pressed, and we've received a code...
  if ((digitalRead(buttonPin) == LOW))
  {
    sendCode(); // Sends out our code. (See bottom of sketch).
    irrecv.enableIRIn(); // Re-enable receiver
    // We only want to be able to send the code once. Re-set
    // codeReceived to false:
  }
}

void updateIRReceive()
{
    irLen = results.rawlen;
    irLen--;
    // We need to convert from ticks to microseconds
    for (int i = 1; i <= irLen; i++) 
    {
      if (i % 2) 
      {
        // Mark
        irBuffer[i-1] = results.rawbuf[i]*USECPERTICK - MARK_EXCESS;

      } 
      else 
      {
        // Space
        irBuffer[i-1] = results.rawbuf[i]*USECPERTICK + MARK_EXCESS;
      }
      Serial.print(" ,");
      Serial.print(irBuffer[i-1], DEC);
    }
    Serial.println();
}


void sendCode() {
  Serial.println("Sent raw" );
  Serial.println(counter);
  if(counter == 1) {
        irsend.sendRaw(button4, sizeof(button4), 38);
        counter = 2;
  }else if(counter == 2) {
        irsend.sendRaw(button5, sizeof(button5), 38);
        counter = 3;
  } else if(counter ==3) {
        irsend.sendRaw(button6, sizeof(button6), 38);
        counter =1;
  } 
}
