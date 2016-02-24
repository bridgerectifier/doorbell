const int buttonPin = 6;
const int ledPin = 9;
int buttonState = 0;
int playSong = 0;

int dacPins[] = {2, 3, 4, 5};

int sin16[] = {7, 8, 10, 11, 12, 13, 14, 14, 15, 14, 14, 13, 12, 11,
              10, 8, 7, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6};

int lowToneDurations[] = {120, 105, 98, 85, 72, 68, 57};
//                        A    B    C   D   E   F   G
int highToneDurations[] = { 49, 41, 37, 31, 25, 23, 18 };
//                          a   b   c   d   e   f   g

// Scale
//char* song = "A B C D E F G a b c d e f g";

// Jingle Bells
//char* song = "E E EE E E EE E G C D EEEE F F F F F E E E E D D E DD
//              GG E E EE E E EE E G C D EEEE F F F F F E E E G G F D CCCC";

// Jingle Bells - Higher
//char* song = "e e ee e e ee e g c d eeee f f f f f e e e e d d e dd gg
//              e e ee e e ee e g c d eeee f f f f f e e e g g f d cccc";

// Pictures at an Exhibition
char* song = "DD CC FF G c aa G c aa FF GG DD CC";


void setup()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(dacPins[i], OUTPUT);
  }
  pinMode(ledPin, OUTPUT);
}


void loop()
{
    buttonState = digitalRead(buttonPin);
 
    if (buttonState == LOW)
    {
        playSong = 1;
    }
    else
    {
        playSong = 0;
    }

    if(playSong == 1)
    {
        int i = 0;
        char ch = song[0];
        while (ch != 0)
        {
            if (ch == ' ')
            {
                delay(60);
            }
            else if (ch >= 'A' and ch <= 'G')
            {
                playNote(lowToneDurations[ch - 'A']);
            }
            else if (ch >= 'a' and ch <= 'g')
            {
                playNote(highToneDurations[ch - 'a']);
            }
            i++;
            ch = song[i];
        }
    }
}


void setOutput(byte value)
{
    digitalWrite(dacPins[3], ((value & 8) > 0));
    digitalWrite(dacPins[2], ((value & 4) > 0));
    digitalWrite(dacPins[1], ((value & 2) > 0));
    digitalWrite(dacPins[0], ((value & 1) > 0));
}


void playNote(int pitchDelay)
{
  digitalWrite(ledPin, HIGH);
  long numCycles = 5000 / pitchDelay + (pitchDelay / 4);
  for (int c = 0; c < numCycles; c++)
  {

    for (int i = 0; i < 32; i++)
    {
      setOutput(sin16[i]);
      delayMicroseconds(pitchDelay);
    }
  }
  digitalWrite(ledPin, LOW);
}
