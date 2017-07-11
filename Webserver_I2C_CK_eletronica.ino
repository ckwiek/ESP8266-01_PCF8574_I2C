
 /*http://www.esp8266.com/viewtopic.php?p=15054
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disc laimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * Adaptado por Carlos kwiek para tutorial sobre I2C
 * contato@carloskwiek.com.br
 */

#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
 #include <Wire.h>          
 #include <PortExpander_I2C.h>
 PortExpander_I2C placa(0x20);
 

const char *ssid = "Sua REDE"; //  SSID da sua rede
const char *password = "Senha sua REDE"; // senha da sua rede

//IPAddress ip(192,168,9,28);
IPAddress ip(192,168,0,45); // ip atribuido ao módulo
IPAddress gateway(192,168,0,1); // base ip da sua rede
IPAddress subnet(255,255,255,0);

     int pin_SDA = 0;
     int pin_SCL = 2;

WiFiServer server(80); // porta para entrada externa
const int rele1 = 16;
const int rele2 = 14;
String header;

const char* APssid = "CARLOSKWIEK.COM.BR"; // para mudar o nome da placa na rede
const char* APpassword = "12345678"; // senha para conexão à placa

void setup ( void ) {

   Wire.begin(pin_SDA, pin_SCL);
   placa.init();

	pinMode ( rele1, OUTPUT );
  digitalWrite ( rele1, 1 );
  
  pinMode ( rele2, OUTPUT );
  digitalWrite ( rele2, 1 );

// Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("creating ");
  Serial.println(APssid);
  
  //WiFi.softAP(APssid);
  int channel = 2;
  WiFi.softAP(APssid, APpassword, channel);
  WiFi.begin(ssid, password);
  WiFi.config( ip,  gateway,  subnet);
  

	Serial.begin ( 115200 );
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Conectando a...");
  Serial.println();
  Serial.println(ssid);
  
  
	WiFi.begin ( ssid, password );
	Serial.println ( "" );

	// Wait for connection
	while ( WiFi.status() != WL_CONNECTED ) {
		delay ( 500 );
		Serial.print ( "." );
	}

	Serial.println ( "" );
	Serial.print ( "Connected a " );
  Serial.println();
	Serial.println ( ssid );

  server.begin();
  Serial.print ( "Server Inicializado" );
  Serial.println();
	Serial.print ( "IP address: " );
	Serial.println ( WiFi.localIP() );

  

}

void loop ( void ) {
 //String buf = "";
    int estado_rele1 = digitalRead(rele1);
   // Serial.println(estado_rele1);
 
 // Listenning for new clients
  WiFiClient client = server.available();


  if (client) {
    Serial.println("Novo Cliente");
       
    // bolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;
      // String req = client.readStringUntil('\r');
      // Serial.print(req);
  
        if (c == '\n' && blank_line) {
              // Serial.print(header);
          
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println("Refresh: 10");  // refresh the page automatically every 10 sec
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");

            client.println("");
            
            if(estado_rele1 == 0)
            client.println("");
            else if(estado_rele1 == 1)
            client.println("");
            
                
                
                 String buf = "";
 
                 buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
                 buf += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
                 buf += "<title>ESP8266 Web Server</title>";
                 buf += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:80%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;}</style>";
                 buf += "</head>";
                
                  
                  buf += "<h3> ESP8266 Web Server by CK_ELetronica</h3>";
                  buf += "<p>RELE1 <a href=\"?function=Rele1_off\"><button>ON</button></a> <a href=\"?function=Rele1_on\"><button>OFF</button></a></p>";
                 // buf += "<p>RELE2 <a href=\"?function=Rele2_off\"><button>ON</button></a> <a href=\"?function=Rele2_on\"><button>OFF</button></a></p>";
                  buf += "<p>RELE2 <a href=\"?function=Rele3_off\"><button>ON</button></a> <a href=\"?function=Rele3_on\"><button>OFF</button></a></p>";
                  buf += "<p>RELE3 <a href=\"?function=Rele4_off\"><button>ON</button></a> <a href=\"?function=Rele4_on\"><button>OFF</button></a></p>";
                  buf += "<p>RELE4 <a href=\"?function=Rele5_off\"><button>ON</button></a> <a href=\"?function=Rele5_on\"><button>OFF</button></a></p>";
                  buf += "<p>RELE5 <a href=\"?function=Rele6_off\"><button>ON</button></a> <a href=\"?function=Rele6_on\"><button>OFF</button></a></p>";
                  buf += "<p>RELE6 <a href=\"?function=Rele7_off\"><button>ON</button></a> <a href=\"?function=Rele7_on\"><button>OFF</button></a></p>";
                  buf += "<p>OnAll <a href=\"?function=OnAll_off\"><button>ON</button></a> <a href=\"?function=OnAll_on\"><button>OFF</button></a></p>";
                  buf += "<h4>CK_ELetronica</h4>";
                  buf += "</html>\n";
                  
                 //  client.println ("<button style=\"width:300px;height:40px;color:green;background-color:#87CEFB\"");
                 client.print(buf);
                
               // buf +=("<button style=\"width:300px;height:40px;color:green;background-color:#87CEFB\"");
                // client.println("<button style=\"width:120px;height:40px;color:green;background-color:#87CEFB\"");
           
                  //client.flush();

                  if (header.indexOf("Rele1_on") != -1){
                        placa.digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
                    }
                  else if (header.indexOf("Rele1_off") != -1){
                        placa.digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
                  }
                  
                 else if (header.indexOf("Rele2_on") != -1)
                      //digitalWrite(rele2, 0);
                       placa.digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
                  else if (header.indexOf("Rele2_off") != -1)
                      //digitalWrite(rele2, 1);
                      placa.digitalWrite(6, LOW);   // turn the LED on (HIGH is the voltage level)


                 else if (header.indexOf("Rele3_on") != -1)
                      //digitalWrite(rele2, 0);
                       placa.digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
                  else if (header.indexOf("Rele3_off") != -1)
                      //digitalWrite(rele2, 1);
                      placa.digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)

                  else if (header.indexOf("Rele4_on") != -1)
                      //digitalWrite(rele2, 0);
                       placa.digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
                  else if (header.indexOf("Rele4_off") != -1)
                      //digitalWrite(rele2, 1);
                      placa.digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
                  
                  else if (header.indexOf("Rele5_on") != -1)
                      //digitalWrite(rele2, 0);
                       placa.digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
                  else if (header.indexOf("Rele5_off") != -1)
                      //digitalWrite(rele2, 1);
                      placa.digitalWrite(0, LOW);   // turn the LED on (HIGH is the voltage level)

                  else if (header.indexOf("Rele6_on") != -1)
                      //digitalWrite(rele2, 0);
                       placa.digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)
                  else if (header.indexOf("Rele6_off") != -1)
                      //digitalWrite(rele2, 1);
                      placa.digitalWrite(1, LOW);   // turn the LED on (HIGH is the voltage level)

                  else if (header.indexOf("Rele7_on") != -1)
                        {
                          //digitalWrite(rele2, 0);
                           placa.digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
                           int valor_pino = placa.digitalRead(7);
                           Serial.println(valor_pino);
                             if(valor_pino==1)
                             {
                                client.print("Rele 7 esta ligado");
                             }
                        }
                        
                  else if (header.indexOf("Rele7_off") != -1)
                        {
                          //digitalWrite(rele2, 1);
                          placa.digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
                          int valor_pino = placa.digitalRead(7);
                          Serial.println(valor_pino);
                              if(valor_pino==0)
                              {
                                 Serial.print("Rele 7 esta desligado");
                                 client.print("Rele 7 OFF");
                                
                              }
                       
                        }
                        

                  else if (header.indexOf("OnAll_on") != -1)
                    {//digitalWrite(rele2, 0);
                        placa.digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level
                        placa.digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
                    }
    
                  else if (header.indexOf("OnAll_off") != -1)
                   {
                        //digitalWrite(rele2, 1);
                        placa.digitalWrite(0, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(1, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level
                        placa.digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(6, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(7, LOW);   // turn the LED on (HIGH is the voltage level)
                        placa.digitalWrite(8, LOW);   // turn the LED on (HIGH is the voltage level)
                   }
                    
   
                    
                  else {
                    Serial.println("invalid request");
                  //  client.stop();
                  }
                 // Serial.println("Client disonnected");
            
        header = "";
        break;
        }
        if (c == '\n') {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r') {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }  
    // closing the client connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");

  }
                   
                 
  }

