// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <TimedAction.h>

// Replace with your network credentials
const char* ssid     = "d1r1karsy";
const char* password = "fenerbahce";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Assign output variables to GPIO pins
const int megareq = 5;
const int megaack = 4;

double temp;
double sys;
double dia;
double pulse;
double resp;
double ekg;
double bat;
double oldtemp;
double oldsys;
double olddia;
double oldpulse;
double oldresp;
double oldekg;
double oldbat;
char dataTransfered[29];
int start;
int tempWarningCount;
int sysWarningCount;
int diaWarningCount;
int pulseWarningCount;
int respWarningCount;
int batWarningCount;
int ekgWarningCount;


void requestdata() {
    digitalWrite(megareq, HIGH);
    //Serial.println("PIN HIGH DELETE THIS LINE");
}

TimedAction request = TimedAction(5000, requestdata);

void getDataFromMega() {
    if (Serial.available() && Serial.read() == 'V') {                                                                //execture if the letter 'V' is read
        Serial.readBytes(dataTransfered, 29);                                                  //store the next 4 characters written on serial one to dataTranfered character array
        unsigned int digit1  = dataTransfered[1]  - '0';                                          //convert the characters to digits
        unsigned int digit2  = dataTransfered[2]  - '0';                                          //convert the characters to digits
        unsigned int digit3  = dataTransfered[3]  - '0';                                          //convert the characters to digits
        unsigned int digit5  = dataTransfered[5]  - '0';                                          //convert the characters to digits
        unsigned int digit6  = dataTransfered[6]  - '0';                                          //convert the characters to digits
        unsigned int digit7  = dataTransfered[7]  - '0';                                          //convert the characters to digits
        unsigned int digit9  = dataTransfered[9]  - '0';                                          //convert the characters to digits
        unsigned int digit10 = dataTransfered[10] - '0';                                        //convert the characters to digits
        unsigned int digit11 = dataTransfered[11] - '0';                                        //convert the characters to digits
        unsigned int digit13 = dataTransfered[13] - '0';                                        //convert the characters to digits
        unsigned int digit14 = dataTransfered[14] - '0';                                        //convert the characters to digits
        unsigned int digit15 = dataTransfered[15] - '0';                                        //convert the characters to digits
        unsigned int digit17 = dataTransfered[17] - '0';                                        //convert the characters to digits
        unsigned int digit18 = dataTransfered[18] - '0';                                        //convert the characters to digits
        unsigned int digit19 = dataTransfered[19] - '0';                                        //convert the characters to digits
        unsigned int digit21 = dataTransfered[21] - '0';                                        //convert the characters to digits
        unsigned int digit22 = dataTransfered[22] - '0';                                        //convert the characters to digits
        unsigned int digit23 = dataTransfered[23] - '0';                                        //convert the characters to digits
        unsigned int digit24 = dataTransfered[24] - '0';                                        //convert the characters to digits
        unsigned int digit26 = dataTransfered[26] - '0';                                        //convert the characters to digits
        unsigned int digit27 = dataTransfered[27] - '0';                                        //convert the characters to digits
        unsigned int digit28 = dataTransfered[28] - '0';                                        //convert the characters to digits

        if ((dataTransfered[0] == 'T')  && (digit1 < 10)  && (digit2 < 10)  && (digit3 < 10)  &&
            (dataTransfered[4] == 'S')  && (digit5 < 10)  && (digit6 < 10)  && (digit7 < 10)  &&
            (dataTransfered[8] == 'D')  && (digit9 < 10)  && (digit10 < 10) && (digit11 < 10) &&
            (dataTransfered[12] == 'P') && (digit13 < 10) && (digit14 < 10) && (digit15 < 10) &&
            (dataTransfered[16] == 'R') && (digit17 < 10) && (digit18 < 10) && (digit19 < 10) &&
            (dataTransfered[20] == 'F') && (digit21 < 10) && (digit22 < 10) && (digit23 < 10) && (digit24 < 10) &&
            (dataTransfered[25] == 'B') && (digit26 < 10) && (digit27 < 10) && (digit28 < 10)) {//make sure all data revieced is valied
            digitalWrite(megaack, HIGH);
            oldtemp = temp;
            oldsys = sys;
            olddia = dia;
            oldpulse = pulse;
            oldresp = resp;
            oldekg = ekg;
            oldbat = bat;
            temp =  5 + (0.75 * ((digit1  * 100) + (digit2  * 10)  + (digit3 * 1)));                    //assign the value of the temperature raw pointer from the measure struct to corrected buffer
            sys =   9 + (2    * ((digit5  * 100) + (digit6  * 10)  + (digit7 * 1)));                     //assign the value of the systolic raw pointer from the measure struct to corrected buffer
            dia =   6 + (1.5  * ((digit9  * 100) + (digit10 * 10) + (digit11 * 1)));                   //assign the value of the diastolic raw pointer from the measure struct to corrected buffer
            pulse = 8 + (3    * ((digit13 * 100) + (digit14 * 10) + (digit15 * 1)));                //assign the value of the pulse raw pointer from the measure struct to corrected buffer
            resp =  7 + (3    * ((digit17 * 100) + (digit18 * 10) + (digit19 * 1)));                //assign the value of the pulse raw pointer from the measure struct to corrected buffer
            bat =               ((digit26 * 100) + (digit27 * 10) + (digit28 * 1)) / 2;
            ekg = (digit21 * 1000) + (digit22 * 100) + (digit23 * 10) + (digit24 * 1);
            digitalWrite(megaack, LOW);
            digitalWrite(megareq, LOW);
        }
    }
}

void setup() {
    Serial.begin(9600);
    // Initialize the output variables as outputs
    pinMode(megareq, OUTPUT);
    pinMode(megaack, OUTPUT);
    // Set outputs to LOW
    digitalWrite(megareq, LOW);
    // Connect to Wi-Fi network with SSID and password
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    // Print local IP address and start web server
    server.begin();
    start = 0;
    temp = 0;
    tempWarningCount = 0;
    sys = 0;
    sysWarningCount = 0;
    dia = 0;
    diaWarningCount = 0;
    pulse = 0;
    pulseWarningCount = 0;
    resp = 0;
    respWarningCount = 0;
    bat = 0;
    batWarningCount = 0;
    ekg = 0;
    ekgWarningCount = 0;
    oldtemp = temp;
    oldsys = sys;
    olddia = dia;
    oldpulse = pulse;
    oldresp = resp;
    oldekg = ekg;
    oldbat = bat;
}

void loop(){
    WiFiClient client = server.available();   // Listen for incoming clients

    if (client) {                             // If a new client connects,
        String currentLine = "";                // make a String to hold incoming data from the client
        Serial.println("TEST");
        while (client.connected()) {            // loop while the client's connected
            if (client.available()) {             // if there's bytes to read from the client,
                char c = client.read();             // read a byte, then
                header += c;
                if (c == '\n') {                    // if the byte is a newline character
                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0) {
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        request.check();
                        getDataFromMega();

                        if (header.indexOf("GET /init") >= 0) {
                            //Serial.println("I");
                        }

                        if (header.indexOf("GET /start") >= 0) {
                            //Serial.println("S");
                        }

                        if (header.indexOf("GET /pause") >= 0) {
                            //Serial.println("P");
                        }

                        if (header.indexOf("GET /disp") >= 0) {
                            //Serial.println("D");
                        }

                        if (header.indexOf("GET /measure") >= 0) {
                            //Serial.println("M");
                        }

                        if (header.indexOf("GET /warn") >= 0) {
                            //Serial.println("W");
                        }



                        // Display the HTML web page
                        client.println("<!DOCTYPE html>");
                        client.println("<html lang=\"en\" dir=\"ltr\">");
                        client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
                        client.println("<meta http-equiv=\"refresh\" content=\"10\">"); //refresh every 10 seconds
                        client.println("<head>");
                        client.println("<meta charset=\"utf-8\">");
                        client.println("<title>RemoteSurgery</title>");
                        client.println("</head>");
                        client.println("<body style=\"background-color: #636363;\">");
                        client.println("<div style=\"position: relative; font-size:25px; color: white; text-align: left; left: 50%; transform: translate(-50%); width: 80%;\">");
                        client.println("<p style=\"color: #d1a7a7; text-align: left; font-size: 40px;\">Remote Surgery System<br><a style=\"font-size: 20px;\">Doctor: Dr. James Peckol</a><br><a style=\"font-size: 20px;\">Patient: Aubrey Graham</a></p>");

                        if (!((temp <= 39.7) && (temp >= 34.3))) {
                            client.print("<p style=\"animation-name: flash; animation-duration: 1s; animation-iteration-count: infinite;\">");
                            if (temp != oldtemp) {
                                tempWarningCount++;
                            }
                        } else {
                            client.print("<p>");
                        }
                        client.print("Temp: ");
                        client.print(temp);
                        client.print(" C <a style=\"position: absolute; right: 0%\">");
                        client.print(tempWarningCount);
                        client.println("</a></p>");

                        if (!((sys >= 114) && (sys <= 136.5))) {
                            client.print("<p style=\"animation-name: flash; animation-duration: 1s; animation-iteration-count: infinite;\">");
                            if (sys != oldsys) {
                                sysWarningCount++;
                            }
                        } else {
                            client.print("<p>");
                        }
                        client.print("Syst: ");
                        client.print(sys);
                        client.print(" mmHg <a style=\"position: absolute; right: 0%\">");
                        client.print(sysWarningCount);
                        client.println("</a></p>");

                        if (!((dia >= 66.5) && (dia <= 84))) {
                            client.print("<p style=\"animation-name: flash; animation-duration: 1s; animation-iteration-count: infinite;\">");
                            if (dia != olddia) {
                                diaWarningCount++;
                            }
                        } else {
                            client.print("<p>");
                        }
                        client.print("Dias: ");
                        client.print(dia);
                        client.print(" mmHg <a style=\"position: absolute; right: 0%\">");
                        client.print(diaWarningCount);
                        client.println("</a></p>");

                        if (!((pulse >= 57) && (pulse <= 105))) {
                            client.print("<p style=\"animation-name: flash; animation-duration: 1s; animation-iteration-count: infinite;\">");
                            if (pulse != oldpulse) {
                                pulseWarningCount++;
                            }
                        } else {
                            client.print("<p>");
                        }
                        client.print("Puls: ");
                        client.print(pulse);
                        client.print(" BPM <a style=\"position: absolute; right: 0%\">");
                        client.print(pulseWarningCount);
                        client.println("</a></p>");

                        if (!((resp >= 11.4) && (resp <= 26.25))) {
                            client.print("<p style=\"animation-name: flash; animation-duration: 1s; animation-iteration-count: infinite;\">");
                            if (resp != oldresp) {
                                respWarningCount++;
                            }
                        } else {
                            client.print("<p>");
                        }
                        client.print("Resp: ");
                        client.print(resp);
                        client.print(" RR <a style=\"position: absolute; right: 0%\">");
                        client.print(respWarningCount);
                        client.println("</a></p>");

                        if (!((ekg > 35) && (ekg < 3750))) {
                            client.print("<p style=\"animation-name: flash; animation-duration: 1s; animation-iteration-count: infinite;\">");
                            if (ekg != oldekg) {
                                ekgWarningCount++;
                            }
                        } else {
                            client.print("<p>");
                        }
                        client.print("EKG: ");
                        client.print(ekg);
                        client.print(" Hz <a style=\"position: absolute; right: 0%\">");
                        client.print(ekgWarningCount);
                        client.println("</a></p>");

                        if (!(bat > 20)) {
                            client.print("<p style=\"animation-name: flash; animation-duration: 1s; animation-iteration-count: infinite;\">");
                            if (bat != oldbat) {
                                batWarningCount++;
                            }
                        } else {
                            client.print("<p>");
                        }
                        client.print("Batt: ");
                        client.print(bat);
                        client.print("% <a style=\"position: absolute; right: 0%\">");
                        client.print(batWarningCount);
                        client.println("</a></p>");

                        client.println("<br>");

                        client.println("<a href = \"/init\"><button type=\"button\" style=\"position: relative; font-size: 25px;  background-color: #4b74b7; color: #d6d6d6;\">Initialize</button></a>");
                        client.println("<a href = \"/start\"><button type=\"button\" style=\"position: relative; font-size: 25px;  background-color: #4b74b7; color: #d6d6d6;\">Start</button></a>");
                        client.println("<a href = \"/pause\"><button type=\"button\" style=\"position: relative; font-size: 25px;  background-color: #4b74b7; color: #d6d6d6;\">Pause</button></a>");
                        client.println("<a href = \"/disp\"><button type=\"button\" style=\"position: relative; font-size: 25px;  background-color: #4b74b7; color: #d6d6d6;\">Display</button></a>");
                        client.println("<a href = \"/measure\"><button type=\"button\" style=\"position: relative; font-size: 25px;  background-color: #4b74b7; color: #d6d6d6;\">Measure</button></a>");
                        client.println("<a href = \"/warn\"><button ype=\"button\" style=\"position: relative; font-size: 25px;  background-color: #4b74b7; color: #d6d6d6;\">Warning</button></a>");

                        client.println("<p style=\"position: relative; width: 100%; background-color: #4c4c4c; border-style: solid; border-color: white; border-width: 2px;\">");
                        client.println("Messages:");
                        client.println("<br><br>");
                        client.print("<a style=\"font-family: Courier New, monospace; font-size: 18px;\">");
                        client.print("5 warnings");
                        //message
                        client.println("</a></p>");
                        client.println("</div>");
                        client.println("<style>");
                        client.println("@keyframes flash {0% {color:white;} 50% {color:#ad3442;} 100% {color:white;}}");
                        client.println("</style>");
                        client.println("</body>");
                        client.println("</html>");
                        // The HTTP response ends with another blank line
                        client.println();
                        // Break out of the while loop
                        break;
                    } else { // if you got a newline, then clear currentLine
                        currentLine = "";
                    }
                } else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }
            }
        }
        // Clear the header variable
        header = "";
        // Close the connection
        client.stop();
    }
}
