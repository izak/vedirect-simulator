const char* message = 
"\r\nV\t12800"
"\r\nVS\t24500"
"\r\nVM\t1280"
"\r\nDM\t120"
"\r\nVPV\t3350"
"\r\nPPV\t196"
"\r\nI\t15000"
"\r\nIL\t1500"
"\r\nLOAD\tON"
"\r\nT\t25"
"\r\nP\t192"
"\r\nCE\t13500"
"\r\nSOC\t876"
"\r\nTTG\t45"
"\r\nAlarm\tOFF"
"\r\nRelay\tOFF"
"\r\nAR\t1"
"\r\nH1\t55000"
"\r\nH2\t15000"
"\r\nH3\t13000"
"\r\nH4\t230"
"\r\nH5\t12"
"\r\nH6\t234000"
"\r\nH7\t11000"
"\r\nH8\t14800"
"\r\nH9\t7200"
"\r\nH10\t45"
"\r\nH11\t5"
"\r\nH12\t0"
"\r\nH13\t0"
"\r\nH14\t0"
"\r\nH15\t11500"
"\r\nH16\t14800"
"\r\nH17\t34"
"\r\nH18\t45"
"\r\nH19\t456"
"\r\nH20\t45"
"\r\nH21\t300"
"\r\nH22\t45"
"\r\nH23\t350"
"\r\nERR\t0"
"\r\nCS\t5"
"\r\nBMV\t702"
"\r\nFW\t1.19"
"\r\nPID\t0x204"
"\r\nSER#\tHQ14415IZFW"
"\r\nHSDS\t0"
"\r\nChecksum\t";

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int count = 0;

char checksum(const char *msg){
    uint8_t chr = 0;
    int i;
    for (i=0; msg[i]!='\0'; i++) {
        chr = (chr + msg[i]);
    }
    return (char)(256 - chr);
}

void setup() {
    Serial.begin(19200);
    inputString.reserve(1024);
}

void serialEvent() {
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        // add it to the inputString:
        inputString += inChar;
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '\n') {
            stringComplete = true;
        }
    }
}

void loop() {
    if (stringComplete) {
        if (inputString.startsWith(":7")){
            // GET command
            String id = inputString.substring(2, 6);
            if (id == "0A01"){
                Serial.print(":70A010048513134343044345135522C48513134343135495A46572C0D0A0000000000004A\n");
            }
        }
        inputString = "";
        stringComplete = false;
    }
    if (!count){
        Serial.print(message);
        Serial.print(checksum(message));
    }
    delay(10);
    count = (count + 1) % 100;
}
