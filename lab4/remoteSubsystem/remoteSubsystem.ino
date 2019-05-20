/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "RemoteSurgery";
const char* password = "Group7";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Assign output variables to GPIO pins
const int request = 5;

double temp;
double sys;
double dia;
double pulse;
double resp;
char dataTransfered[20];

void setup() {
    Serial.begin(9600);
    // Initialize the output variables as outputs
    pinMode(request, OUTPUT);
    // Set outputs to LOW
    digitalWrite(request, LOW);
    // Connect to Wi-Fi network with SSID and password
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    }
    // Print local IP address and start web server
    server.begin();

    temp = 0;
    sys = 0;
    dia = 0;
    pulse = 0;
    resp = 0;
}

void loop(){
    if (Serial.read() == 'V') {                                                                //execture if the letter 'V' is read
        Serial.readBytes(dataTransfered, 20);                                                  //store the next 4 characters written on serial one to dataTranfered character array
        unsigned int digit1 = dataTransfered[1] - '0';                                          //convert the characters to digits
        unsigned int digit2 = dataTransfered[2] - '0';                                          //convert the characters to digits
        unsigned int digit3 = dataTransfered[3] - '0';                                          //convert the characters to digits
        unsigned int digit5 = dataTransfered[5] - '0';                                          //convert the characters to digits
        unsigned int digit6 = dataTransfered[6] - '0';                                          //convert the characters to digits
        unsigned int digit7 = dataTransfered[7] - '0';                                          //convert the characters to digits
        unsigned int digit9 = dataTransfered[9] - '0';                                          //convert the characters to digits
        unsigned int digit10 = dataTransfered[10] - '0';                                        //convert the characters to digits
        unsigned int digit11 = dataTransfered[11] - '0';                                        //convert the characters to digits
        unsigned int digit13 = dataTransfered[13] - '0';                                        //convert the characters to digits
        unsigned int digit14 = dataTransfered[14] - '0';                                        //convert the characters to digits
        unsigned int digit15 = dataTransfered[15] - '0';                                        //convert the characters to digits
        unsigned int digit13 = dataTransfered[17] - '0';                                        //convert the characters to digits
        unsigned int digit14 = dataTransfered[18] - '0';                                        //convert the characters to digits
        unsigned int digit15 = dataTransfered[19] - '0';                                        //convert the characters to digits

        if ((dataTransfered[0] == 'T')  && (digit1 < 10)  && (digit2 < 10)  && (digit3 < 10)  &&
            (dataTransfered[4] == 'S')  && (digit5 < 10)  && (digit6 < 10)  && (digit7 < 10)  &&
            (dataTransfered[8] == 'D')  && (digit9 < 10)  && (digit10 < 10) && (digit11 < 10) &&
            (dataTransfered[12] == 'P') && (digit13 < 10) && (digit14 < 10) && (digit15 < 10) &&
            (dataTransfered[16] == 'R') && (digit17 < 10) && (digit18 < 10) && (digit19 < 10) &&) {//make sure all data revieced is valied
            temp =  5 + (0.75 * ((digit1  * 100) + (digit2  * 10)  + (digit3 * 1)));                    //assign the value of the temperature raw pointer from the measure struct to corrected buffer
            sys =   9 + (2    * ((digit5  * 100) + (digit6  * 10)  + (digit7 * 1)));                     //assign the value of the systolic raw pointer from the measure struct to corrected buffer
            dia =   6 + (1.5  * ((digit9  * 100) + (digit10 * 10) + (digit11 * 1)));                   //assign the value of the diastolic raw pointer from the measure struct to corrected buffer
            pulse = 8 + (3    * ((digit13 * 100) + (digit14 * 10) + (digit15 * 1)));                //assign the value of the pulse raw pointer from the measure struct to corrected buffer
            resp =  7 + (3    * ((digit17 * 100) + (digit18 * 10) + (digit19 * 1)));                //assign the value of the pulse raw pointer from the measure struct to corrected buffer
        }
    }
    WiFiClient client = server.available();   // Listen for incoming clients

    if (client) {                             // If a new client connects,
        String currentLine = "";                // make a String to hold incoming data from the client
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

                        // turns the GPIOs on and off
                        if (header.indexOf("GET data") >= 0) {
                            digitalWrite(output5, HIGH);
                        } else {
                            digitalWrite(output5, LOW);
                        }

                        // Display the HTML web page
                        client.println("<!DOCTYPE html>");
                        client.println("<html lang=\"en\" dir=\"ltr\">");
                        client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
                        client.println("<head>");
                        client.println("<meta charset=\"utf-8\">");
                        client.println("<title>RemoteSurgery</title>");
                        client.println("</head>");
                        client.println("<body style=\"background-color: #636363;\">");
                        client.println("<div style=\"position: relative; font-size:25px; color: white; text-align: left; left: 50%; transform: translate(-50%); width: 80%;\">");
                        client.println("<p style=\"color: #d1a7a7; text-align: left; font-size: 40px;\">Remote Surgery System</p>");
                        client.println("<p>Temp: " + temp + " C </p>");
                        client.println("<p>Syst: " + sys + " mmHg </p>");
                        client.println("<p>Dias: " + dia + " mmHg </p>");
                        client.println("<p>Puls: " + pulse + " BPM </p>");
                        client.println("<p>Resp: " + resp + " RR </p>");
                        client.println("<br>");
                        client.println("<button href=\"data\" type=\"button\" style=\"position: relative; font-size: 25px;  background-color: #4b74b7; color: #d6d6d6;\">Get Data</button>");
                        client.println("</div>");
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
