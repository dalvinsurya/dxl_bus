//Written by Dalvin.S 13/08/2021
//Tested on Teensy 3.1/3.2 boards
//Slave object for embedded boards using dynamixel protocols

#include <Dynamixel2Arduino.h>
#define dxlSerial   Serial3
#define dbgSerial   Serial
const uint8_t dxlDir = 2; //Txen

const int ledPin = 13; //Onboard LED for Teensy 3.1/3.2
const int potPin = A0; 

DYNAMIXEL::SerialPortHandler dxlPort(dxlSerial, dxlDir);

const uint16_t dxlMdl = 0x1D; //Emulating mx-28
DYNAMIXEL::Slave dxl(dxlPort, dxlMdl);

//Addresses for registers
const uint16_t addr_l1  = 0x1A;
const uint16_t addr_l2  = 0x1C;
const uint16_t addr_l3  = 0x1E;
const uint16_t addr_l4  = 0x20;

uint16_t //Stored variables
stored_l1,
stored_l2,
stored_l3,
stored_l4;

using namespace ControlTableItem;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
  
  dbgSerial.begin(115200);
  dxlPort.begin(1000000);
  dxl.setPortProtocolVersion(2.0);
  dxl.setFirmwareVersion(1);
  dxl.setID(101);

  dxl.addControlItem(addr_l1, stored_l1);
  dxl.addControlItem(addr_l2, stored_l2);
  dxl.addControlItem(addr_l3, stored_l3);
  dxl.addControlItem(addr_l4, stored_l4);
  
  //Blink showing init completed
  digitalWrite(ledPin, !digitalRead(ledPin));
  delay(100);
  digitalWrite(ledPin, !digitalRead(ledPin));
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(dxl.processPacket() == false){
    //Print error
    dbgSerial.print("Last lib err code: ");
    dbgSerial.print(dxl.getLastLibErrCode());
    dbgSerial.print(", ");
    dbgSerial.print("Last status packet err code: ");
    dbgSerial.println(dxl.getLastStatusPacketError());
    dbgSerial.println();
  }
  stored_l1 = analogRead(A0);
  stored_l2 = analogRead(A0);
  stored_l3 = 3;
  stored_l4 = 4;

  // Update or use variables for each control item.
}
