/* With the help of https://github.com/Razvan201013/Bmw-F10-cluster-canbus */

#include <stdio.h>
#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10); // Set CS Pin

#define BUF_SIZE                    64

#define ENGINE_SPEED_FACTOR         32

// Button-Pins
#define AKBTN_PIN                   3
#define BKBTN_PIN                   4
#define CKBTN_PIN                   5
#define DKBTN_PIN                   6
#define FKBTN_PIN                   7

char simhub_message_buf[BUF_SIZE];

static uint8_t count = 0x00;
static uint8_t steering_count = 0xA0;
uint8_t steering_bit = 0b00100000;

void splitBytes(uint16_t num, uint8_t *lowByte, uint8_t *highByte) {
    *lowByte = (uint8_t)(num & 0xFF);
    *highByte = (uint8_t)((num >> 8) & 0xFF);
}

void setup() {
    Serial.begin(115200);
    SPI.begin();

    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
    {
        Serial.println("MCP2515 Initialized Successfully!");
        delay(1000);
    }
    else
    {
        Serial.println("Error Initializing MCP2515...");
        delay(2000);
        setup();
    }
    CAN0.setMode(MCP_NORMAL);

    pinMode(AKBTN_PIN, INPUT_PULLUP);
    pinMode(BKBTN_PIN, INPUT_PULLUP);
    pinMode(CKBTN_PIN, INPUT_PULLUP);
    pinMode(DKBTN_PIN, INPUT_PULLUP);
    pinMode(FKBTN_PIN, INPUT_PULLUP);

    memset(simhub_message_buf, 0x0, BUF_SIZE);
}

void sendConstantMessages() {
    // Ignition
    uint8_t data12f[8] = { 0xFB, count, 0x8A, 0x1C, 0xF1, 0x05, 0x30, 0x86 };
    // TPMS
    uint8_t datab68[8] = { 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00 };

    CAN0.sendMsgBuf(0x12F, 0, 8, data12f);
    CAN0.sendMsgBuf(0xB68, 0, 8, datab68);

    // Buttons
    uint8_t data1d6[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    
    if (digitalRead(AKBTN_PIN) == LOW) {
        uint8_t newData[8] = { 0xC8, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        memcpy(data1d6, newData, sizeof(data1d6));
    }


    if (digitalRead(BKBTN_PIN) == LOW) {
        uint8_t newData[8] = { 0xC4, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        memcpy(data1d6, newData, sizeof(data1d6));
    }

    CAN0.sendMsgBuf(0x1D6, 0, 8, data1d6);

    // Drive-Mode
    // 1= Traction, 2= Comfort, 4= Sport, 5= Sport+, 6= DSC off,
    uint8_t drive_mode = 5;
    uint8_t data3a7[8] = { 0x00, count, 0x00, 0x00, drive_mode, 0x00, 0x00, 0x00 };
    CAN0.sendMsgBuf(0x3a7, 0, 8, data3a7);

    // Cruise & Lane
    uint8_t data327[8] = { 0xA2, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    CAN0.sendMsgBuf(0x327, 0, 8, data327);

    // Seatbelt
    uint8_t data581[8] = { 0x40, 0x4D, 0, 0x28, 0xFF, 0xFF, 0xFF, 0xFF };
    CAN0.sendMsgBuf(0x581, 0, 8, data581);

    // Language & Units
    // uint8_t language = 0;
    // uint8_t temp_unit = 0;
    // uint8_t unit = 0;
    // uint8_t data291[8] = { language, temp_unit, unit, 0x00, 0x00, 0x00, 0x00, 0x00 };
    // CAN0.sendMsgBuf(0x291, 0, 8, data291);

    // Airbag
    uint8_t data0d7[8] = { count, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    CAN0.sendMsgBuf(0x0d7, 0, 8, data0d7);

    // Brake
    uint8_t data36f[3] = { count, count, 0x00 };
    CAN0.sendMsgBuf(0x36f, 0, 3, data36f);
    
    // Steering Lock
    uint8_t data2a7[8] = { steering_bit, steering_count, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    CAN0.sendMsgBuf(0x2a7, 0, 8, data2a7);
    steering_bit ^= 0b00000001;
    
    // Adaptive Cruise
    uint8_t adaptive_cruise = 0xFF;
    uint8_t data33b[8] = { 0x00, 0x00, adaptive_cruise, 0x00, 0x00, 0x00, 0x00, 0x00 };
    CAN0.sendMsgBuf(0x33b, 0, 8, data33b);

    // ABS 1
    uint8_t data36e[8] = { 0x00, count, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    CAN0.sendMsgBuf(0x36e, 0, 8, data36e);

    // ABS 2
    uint8_t datab6e[8] = { count, count, count, count, count, count, count, 0x00 };
    CAN0.sendMsgBuf(0xb6e, 0, 8, datab6e);

}

void process_message() {
    unsigned int revs;
    unsigned int speed_kmh;
    unsigned int fuel_percent;
    int water_temperature_degC;
    int turn_left;
    int turn_right;
    int brake;
    int oil_temperature_degC;
    
    sscanf(simhub_message_buf, "%u&%u&%u&%d&%d&%d&%d&%d",
        &revs,
        &speed_kmh,
        &fuel_percent,
        &water_temperature_degC,
        &turn_left,
        &turn_right,
        &brake,
        &oil_temperature_degC
    );

    uint8_t light_state = 0x00;

    if (turn_left == 1)
    {
        light_state = light_state | 0b01000000;
    }
    if (turn_right == 1)
    {
        light_state = light_state | 0b00100000;
    }

    // Turn Signal
    uint8_t data1f6[8] = { 0x91, 0xF2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    // Lights
    uint8_t data21a[8] = { 0x04, 0x12, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00 };

    // RPM
    // uint8_t calculated_revs = revs / ENGINE_SPEED_FACTOR;
    uint8_t data0f3[8] = { 0x76, count, 0x00, 2, 1, 0xC4, 0xFF, 0xFF };
    
    // Speed
    // unsigned char lowByte, highByte;
    // splitBytes(speed_kmh * 10, &lowByte, &highByte);
    uint8_t data1a1[8] = { count, count, 0x12, 0x14, (uint8_t)speed_kmh, 0x00, 0x00, 0x00 };

    // Fuel
    uint8_t data349[8] = { 0x00, 0x01, 0xBE, 0x0A, 0x00, 0x00, 0x00, 0x00 };

    // Oiltemp
    uint8_t data3f9[8] = { 0x02, count, count, 0x00, 0x00, (uint8_t)oil_temperature_degC, count, count };

    CAN0.sendMsgBuf(0x1f6, 0, 8, data1f6);
    CAN0.sendMsgBuf(0x21a, 0, 8, data21a);
    CAN0.sendMsgBuf(0x0f3, 0, 8, data0f3);
    CAN0.sendMsgBuf(0x1a1, 0, 8, data1a1);
    CAN0.sendMsgBuf(0x349, 0, 8, data349);
    CAN0.sendMsgBuf(0x3f9, 0, 8, data3f9);
}

void loop() {
    if (Serial.available() > 0)
    {
        Serial.readBytesUntil('{', simhub_message_buf, BUF_SIZE);
        int readCount = Serial.readBytesUntil('}', simhub_message_buf, BUF_SIZE);
        simhub_message_buf[min(readCount, BUF_SIZE - 1)] = 0x0;
        process_message();
        memset(simhub_message_buf, 0x0, BUF_SIZE);
    }
    sendConstantMessages();
    
    if (count >= 0xFF)
    {
        count = 0x00;
    }
    else 
    {
        count++;
    }
    
    
    if (steering_count >= 0xFF)
    {
        steering_count = 0xA0;
    }
    else
    {
        steering_count++;
    }
}