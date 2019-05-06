char buffer[12];   //maximum expected length 
int len = 0;

int led1 = 9;
int led2 = 10;
int led3 = 11;

int led1Br = 0;
int led2Br = 0;
int led3Br = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}
void loop()
{
  //
  // Parse incoming messages consisting of three decimal values followed by a carriage return
  //  Example  "12 34 56\n"
  //  In TouchDesigner:     op('serial1').send("12 34 56", terminator="\n")
  //
  while (len < 12) {
    if (Serial.available() > 0) 
    {
        int incomingByte = Serial.read();
        buffer[len++] = incomingByte;
        // check for overflow
        if (len >= 12)
        {
            // overflow, resetting
            len = 0;
        }
        // check for newline (end of message)
        if (incomingByte == '\n')
        {
            int br1, br2, br3;
            int n = sscanf(buffer, "%d %d %d", &br1, &br2, &br3);
            if (n == 3)
            {
                // valid message received, use values here..
                analogWrite(led1, br1);
                analogWrite(led2, br2);
                analogWrite(led3, br3);
            }
            else
            {
              // parsing error, reject
            }
            len = 0; // reset buffer counter
        }
     }
 }
  delay(30);
}
