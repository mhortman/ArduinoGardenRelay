const uint8_t       pinWATER_PUMP_RELAY         = 2;
const uint8_t       pinMSGLED         = 13;

const uint8_t       WATER_PUMP_OFF              = HIGH;
const uint8_t       WATER_PUMP_ON               = LOW;

const unsigned long ONE_SECOND                  = 1000UL;
const unsigned long ONE_MINUTE                  = 60UL * ONE_SECOND;
const unsigned long ONE_HOUR                    = 60UL * ONE_MINUTE;
const unsigned long THIRTY_MINUTES                = 30UL * ONE_MINUTE;
const unsigned long WATER_PUMP_TIME_ON          = 5UL  * ONE_MINUTE;
const unsigned long WATER_PUMP_TIME_NEXT_CYCLE  = THIRTY_MINUTES - WATER_PUMP_TIME_ON;
//const unsigned long WATER_PUMP_TIME_ON          = 5UL  * ONE_SECOND;
//const unsigned long WATER_PUMP_TIME_NEXT_CYCLE  = 5UL * ONE_MINUTE - WATER_PUMP_TIME_ON;
#define SERIAL_BAUD   38400
#if 1
#define DEBUG1(expression)  Serial.print(expression)
#define DEBUG2(expression, arg)  Serial.print(expression, arg)
#define DEBUGLN1(expression)  Serial.println(expression)
#else
#define DEBUG1(expression)
#define DEBUG2(expression, arg)
#define DEBUGLN1(expression)
#endif

unsigned long       tmNextTrigger;


// See <http://arduino.cc/playground/Code/TimingRollover>

bool hasTimeExpired(const unsigned long& tmsTarget)
{
    unsigned long tRemain = tmsTarget - millis();
    DEBUG1(millis());
    DEBUG1("   tar  ");
    DEBUG1(tmsTarget);
    char    szStr[20];

    sprintf( szStr, " Remain %ld", tRemain );
    DEBUG1( szStr );

    if (tRemain > 0){
       DEBUG1("   Remain POS ");
       int blinks = (int)(tRemain/(60UL*1000UL));
       DEBUGLN1(blinks);
       for (int i = 0; i < blinks; i++) {
          setLED(1);
          delay(100);
          setLED(0);
          delay(100);
       }
       delay(1000);
    }
    return ((long)(tmsTarget - millis()) <= 0);
}

void setup() {
  Serial.begin(9600);
  tmNextTrigger   = millis();
    pinMode(pinWATER_PUMP_RELAY, OUTPUT);
    pinMode(pinMSGLED, OUTPUT);
    setPump(WATER_PUMP_OFF);
}

void cycleWaterPump()
{
  DEBUG1("CYCLE ON");
    setPump(WATER_PUMP_ON);

    delay(WATER_PUMP_TIME_ON);

    setPump(WATER_PUMP_OFF);
   DEBUGLN1("CYCLE OFF");
}

void setLED(uint8_t state)
{
    digitalWrite(pinMSGLED, state);
}

void setPump(uint8_t state)
{
    digitalWrite(pinWATER_PUMP_RELAY, state);
}
void loop() {
 // delay(10UL * ONE_SECOND);
 //  cycleWaterPump();
    if ( hasTimeExpired(tmNextTrigger) )
    {
        cycleWaterPump();
        DEBUG1("B4 Cycle ");
        DEBUG1(tmNextTrigger);
        tmNextTrigger += WATER_PUMP_TIME_NEXT_CYCLE;
        DEBUG1("Next Trig ");
        DEBUG1(tmNextTrigger);
        DEBUG1(" -> ");
        DEBUGLN1(millis());
    }
 
}
