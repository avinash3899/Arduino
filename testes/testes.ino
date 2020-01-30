enum Commands_Enum
        {
          NotSet        = 0x00,   // Default value for enum. Scanner will return error if sent this.
          Open        = 0x01,   // Open Initialization
          Close       = 0x02,   // Close Termination
          UsbInternalCheck  = 0x03,   // UsbInternalCheck Check if the connected USB device is valid
          ChangeEBaudRate   = 0x04,   // ChangeBaudrate Change UART baud rate
          SetIAPMode      = 0x05,   // SetIAPMode Enter IAP Mode In this mode, FW Upgrade is available
          CmosLed       = 0x12,   // CmosLed Control CMOS LED
          GetEnrollCount    = 0x20,   // Get enrolled fingerprint count
          CheckEnrolled   = 0x21,   // Check whether the specified ID is already enrolled
          EnrollStart     = 0x22,   // Start an enrollment
          Enroll1       = 0x23,   // Make 1st template for an enrollment
          Enroll2       = 0x24,   // Make 2nd template for an enrollment
          Enroll3       = 0x25,   // Make 3rd template for an enrollment, merge three templates into one template, save merged template to the database
          IsPressFinger   = 0x26,   // Check if a finger is placed on the sensor
          DeleteID      = 0x40,   // Delete the fingerprint with the specified ID
          DeleteAll     = 0x41,   // Delete all fingerprints from the database
          Verify1_1     = 0x50,   // Verification of the capture fingerprint image with the specified ID
          Identify1_N     = 0x51,   // Identification of the capture fingerprint image with the database
          VerifyTemplate1_1 = 0x52,   // Verification of a fingerprint template with the specified ID
          IdentifyTemplate1_N = 0x53,   // Identification of a fingerprint template with the database
          CaptureFinger   = 0x60,   // Capture a fingerprint image(256x256) from the sensor
          MakeTemplate    = 0x61,   // Make template for transmission
          GetImage      = 0x62,   // Download the captured fingerprint image(256x256)
          GetRawImage     = 0x63,   // Capture & Download raw fingerprint image(320x240)
          GetTemplate     = 0x70,   // Download the template of the specified ID
          SetTemplate     = 0x71,   // Upload the template of the specified ID
          GetDatabaseStart  = 0x72,   // Start database download, obsolete
          GetDatabaseEnd    = 0x73,   // End database download, obsolete
          UpgradeFirmware   = 0x80,   // Not supported
          UpgradeISOCDImage = 0x81,   // Not supported
          Ack         = 0x30,   // Acknowledge.
          Nack        = 0x31    // Non-acknowledge
      };
    Commands_Enum Command;
    byte Parameter[4];                // Parameter 4 bytes, changes meaning depending on command              
    static const byte COMMAND_START_CODE_1 = 0x55;  // Static byte to mark the beginning of a command packet  - never changes
    static const byte COMMAND_START_CODE_2 = 0xAA;  // Static byte to mark the beginning of a command packet  - never changes
    static const byte COMMAND_DEVICE_ID_1 = 0x01; // Device ID Byte 1 (lesser byte)             - theoretically never changes
    static const byte COMMAND_DEVICE_ID_2 = 0x00; // Device ID Byte 2 (greater byte)              - theoretically never changes
    byte command[2];                // Command 2 bytes

    byte* GetPacketBytes()
{
  byte* packetbytes= new byte[12];

  // update command before calculating checksum (important!)
  word cmd = Command;
  command[0] = GetLowByte(cmd);
  command[1] = GetHighByte(cmd);

  word checksum = _CalculateChecksum();

  packetbytes[0] = COMMAND_START_CODE_1;
  packetbytes[1] = COMMAND_START_CODE_2;
  packetbytes[2] = COMMAND_DEVICE_ID_1;
  packetbytes[3] = COMMAND_DEVICE_ID_2;
  packetbytes[4] = Parameter[0];
  packetbytes[5] = Parameter[1];
  packetbytes[6] = Parameter[2];
  packetbytes[7] = Parameter[3];
  packetbytes[8] = command[0];
  packetbytes[9] = command[1];
  packetbytes[10] = GetLowByte(checksum);
  packetbytes[11] = GetHighByte(checksum);

  return packetbytes;
}

// Converts the int to bytes and puts them into the paramter array
void ParameterFromInt(int i)
{
  Parameter[0] = (i & 0x000000ff);
  Parameter[1] = (i & 0x0000ff00) >> 8;
  Parameter[2] = (i & 0x00ff0000) >> 16;
  Parameter[3] = (i & 0xff000000) >> 24;
}

// Returns the high byte from a word
byte GetHighByte(word w)
{
  return (byte)(w>>8)&0x00FF;
}

// Returns the low byte from a word
byte GetLowByte(word w)
{
  return (byte)w&0x00FF;
}

word _CalculateChecksum()
{
  word w = 0;
  w += COMMAND_START_CODE_1;
  w += COMMAND_START_CODE_2;
  w += COMMAND_DEVICE_ID_1;
  w += COMMAND_DEVICE_ID_2;
  w += Parameter[0];
  w += Parameter[1];
  w += Parameter[2];
  w += Parameter[3];
  w += command[0];
  w += command[1];

  return w;
}
Command_Packet();

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  
  // put your main code here, to run repeatedly:

}
