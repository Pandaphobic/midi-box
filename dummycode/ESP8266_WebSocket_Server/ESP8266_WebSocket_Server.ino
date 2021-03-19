/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-websocket-server-arduino/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "figureitout";
const char* password = "idontknow";

bool ledState = 0;
const int ledPin = 2;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>OMB - WebServer - MidHeavy</title>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <link rel="icon" href="data:," />
    <style>
      html {
        font-family: Arial, Helvetica, sans-serif;
        text-align: center;
      }
      h1 {
        font-size: 1.8rem;
        color: #ececec;
      }
      h2 {
        font-size: 1.6rem;
        font-weight: bold;
        color: #09bdff;
      }
      .topnav {
        overflow: hidden;
        background-color: #242424;
      }
      body {
        margin: 0;
        background-color: #313131;
      }
      .content {
        padding: 30px;
        max-width: 600px;
        margin: 0 auto;
      }
      .card {
        background-color: #242424;
        box-shadow: 2px 2px 12px 1px rgba(15, 15, 15, 0.5);
        padding-top: 10px;
        padding-bottom: 20px;
      }
      .form-group {
        margin: .5em;
      }
      label {
        color: #09bdff;
        background-color: #1a1a1a;
        padding: 5px;
      }
      .text-input {
        font-family: Arial, Helvetica, sans-serif;
        text-align: center;
        font-size: 18px;
        padding: 5px;
        background-color: #1a1a1a;
        color: #09bdff;
        border: none;
      }
      .button {
        padding: 10px 25px;
        font-size: 16px;
        font-weight: 600;
        text-align: center;
        outline: none;
        color: #242424;
        background-color: #09bdff;
        border: none;
        border-radius: 5px;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        -webkit-tap-highlight-color: rgba(0, 0, 0, 0);
      }
      /*.button:hover {background-color: #0f8b8d}*/
      .button:active {
        background-color: rgb(22, 114, 189);
        box-shadow: 2 2px #cdcdcd;
        transform: translateY(2px);
      }
      .state {
        font-size: 1.5rem;
        color: #8c8c8c;
        font-weight: bold;
      }
    </style>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <link rel="icon" href="data:," />
  </head>
  <body>
    <div class="topnav">
      <h1>Open Midi Box - Settings</h1>
    </div>
    <div class="content">
      <div class="card">
        <h2>BUTTONS CONFIG</h2>
        <form action="">
          <div class='form-group'>
            <label  for="MIDI_IN_1">MIDI_IN_1</label>
            <input type="text" class='ml-2 text-input' placeholder="command"/>
            <select class='text-input' name="com-type" id="com-type">
              <option value="cc">CC</option>
              <option value="pc">PC</option>
              <option value="sysex">SysEx</option>
            </select>
          </div class='form-group'>

          <div class='form-group'>
            <label  for="MIDI_IN_2">MIDI_IN_2</label>
            <input type="text" class='ml-2 text-input' placeholder="command"/>
            <select class='text-input' name="com-type" id="com-type">
              <option value="cc">CC</option>
              <option value="pc">PC</option>
              <option value="sysex">SysEx</option>
            </select>
          </div class='form-group'>

          <div class='form-group'>
            <label  for="MIDI_IN_3">MIDI_IN_3</label>
            <input type="text" class='ml-2 text-input' placeholder="command"/>
            <select class='text-input' name="com-type" id="com-type">
              <option value="cc">CC</option>
              <option value="pc">PC</option>
              <option value="sysex">SysEx</option>
            </select>
          </div class='form-group'>

          <div class='form-group'>
            <label  for="MIDI_IN_4">MIDI_IN_4</label>
            <input type="text" class='ml-2 text-input' placeholder="command"/>
            <select class='text-input' name="com-type" id="com-type">
              <option value="cc">CC</option>
              <option value="pc">PC</option>
              <option value="sysex">SysEx</option>
            </select>
          </div class='form-group'>

          <div class='form-group'>
            <label  for="MIDI_IN_5">MIDI_IN_5</label>
            <input type="text" class='ml-2 text-input' placeholder="command"/>
            <select class='text-input' name="com-type" id="com-type">
              <option value="cc">CC</option>
              <option value="pc">PC</option>
              <option value="sysex">SysEx</option>
            </select>
          </div class='form-group'>

          <div class='form-group'>
            <label  for="MIDI_IN_6">MIDI_IN_6</label>
            <input type="text" class='ml-2 text-input' placeholder="command"/>
            <select class='text-input' name="com-type" id="com-type">
              <option value="cc">CC</option>
              <option value="pc">PC</option>
              <option value="sysex">SysEx</option>
            </select>
          </div class='form-group'>
        </form>

        <p>
          <button id="button" class="button">LOAD</button>
          <button id="button" class="button">RESET</button>
          <button id="button" class="button">SAVE</button>
        </p>
      </div>

    </div>

    <script>
      var gateway = `ws://${window.location.hostname}/ws`
      var websocket
      window.addEventListener("load", onLoad)
      function initWebSocket() {
        console.log("Trying to open a WebSocket connection...")
        websocket = new WebSocket(gateway)
        websocket.onopen = onOpen
        websocket.onclose = onClose
        websocket.onmessage = onMessage // <-- add this line
      }
      function onOpen(event) {
        console.log("Connection opened")
      }
      function onClose(event) {
        console.log("Connection closed")
        setTimeout(initWebSocket, 2000)
      }
      function onMessage(event) {
        var state
        if (event.data == "1") {
          state = "ON"
        } else {
          state = "OFF"
        }
        document.getElementById("state").innerHTML = state
      }
      function onLoad(event) {
        initWebSocket()
        initButton()
      }
      function initButton() {
        document.getElementById("button").addEventListener("click", toggle)
      }
      function toggle() {
        websocket.send("toggle")
      }
    </script>
  </body>
</html>

)rawliteral";

void notifyClients() {
  ws.textAll(String(ledState));
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "toggle") == 0) {
      ledState = !ledState;
      notifyClients();
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if (ledState){
      return "ON";
    }
    else{
      return "OFF";
    }
  }
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
}

void loop() {
  ws.cleanupClients();
  digitalWrite(ledPin, ledState);
}
