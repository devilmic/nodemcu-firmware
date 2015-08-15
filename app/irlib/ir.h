 /***************************************************
  IRremote for ESP8266
  Based on the IRremote library for Arduino by Ken Shirriff
  Written by Mat Salvaris.
  salvaris@gmail.com
  Copyright (C) 2015 Mat Salvaris

  MIT license, all text above must be included in any redistribution
 ****************************************************/

#ifndef ir_h
#define ir_h

#define IR_LIB_VERSION "0.1.0"

#define IRLIB_OK                0
#define IRLIB_ERROR_CHECKSUM   -1
#define IRLIB_ERROR_TIMEOUT    -2
#define IRLIB_INVALID_VALUE    -999

#include "c_types.h"

#define DIRECT_READ(pin)         (0x1 & GPIO_INPUT_GET(GPIO_ID_PIN(pin_num[pin])))
#define DIRECT_MODE_INPUT(pin)   GPIO_DIS_OUTPUT(pin_num[pin])
#define DIRECT_MODE_OUTPUT(pin)
#define DIRECT_WRITE_LOW(pin)    (GPIO_OUTPUT_SET(GPIO_ID_PIN(pin_num[pin]), 0))
#define DIRECT_WRITE_HIGH(pin)   (GPIO_OUTPUT_SET(GPIO_ID_PIN(pin_num[pin]), 1))

enum decode_type_t {
  NEC = 1,
  SONY = 2,
  RC5 = 3,
  RC6 = 4,
  DISH = 5,
  SHARP = 6,
  PANASONIC = 7,
  JVC = 8,
  SANYO = 9,
  MITSUBISHI = 10,
  SAMSUNG = 11,
  LG = 12,
  WHYNTER = 13,
  AIWA_RC_T501 = 14,

  UNKNOWN = -1
};

// Results returned from the decoder
typedef struct {
	int decode_type; // NEC, SONY, RC5, UNKNOWN
  union { // This is used for decoding Panasonic and Sharp data
    unsigned int panasonicAddress;
    unsigned int sharpAddress;
  };
  unsigned long value; // Decoded value
  int bits; // Number of bits in decoded value
  volatile unsigned int *rawbuf; // Raw intervals in .5 us ticks
  int rawlen; // Number of records in rawbuf.
}
decode_result_t;

// Values for decode_type
#define NEC 1
#define SONY 2
#define RC5 3
#define RC6 4
#define DISH 5
#define SHARP 6
#define PANASONIC 7
#define JVC 8
#define SANYO 9
#define MITSUBISHI 10
#define SAMSUNG 11
#define LG 12
#define WHYNTER 13
#define UNKNOWN -1

// Decoded value for NEC when a repeat code is received
#define REPEAT 0xffffffff


void initIRrecv(int recvpin);
void blink13(int blinkflag);
int decode();
void enableIRIn();
void disableIRIn();
void resume();
int getRClevel(int *offset, int *used, int t1);
long decodeNEC();
long decodeSony();
long decodeSanyo();
long decodeMitsubishi();
long decodeRC5();
long decodeRC6();
long decodePanasonic();
long decodeLG();
long decodeJVC();
long decodeSAMSUNG();
long decodeWhynter();
long decodeHash();
int compare(unsigned int oldval, unsigned int newval);


void sendWhynter(unsigned long data, int nbits);
void sendNEC(unsigned long data, int nbits);
void sendSony(unsigned long data, int nbits);
// Neither Sanyo nor Mitsubishi send is implemented yet
//  void sendSanyo(unsigned long data, int nbits);
//  void sendMitsubishi(unsigned long data, int nbits);
void sendRaw(unsigned int buf[], int len, int hz);
void sendRC5(unsigned long data, int nbits);
void sendRC6(unsigned long data, int nbits);
void sendDISH(unsigned long data, int nbits);
void sendSharp(unsigned int address, unsigned int command);
void sendSharpRaw(unsigned long data, int nbits);
void sendPanasonic(unsigned int address, unsigned long data);
void sendJVC(unsigned long data, int nbits, int repeat); // *Note instead of sending the REPEAT constant if you want the JVC repeat signal sent, send the original code value and change the repeat argument from 0 to 1. JVC protocol repeats by skipping the header NOT by sending a separate code value like NEC does.
// private:
void sendSAMSUNG(unsigned long data, int nbits);
void enableIROut(int khz);

void mark(int usec);
void space(int usec);
void bitbangOutput(int time);
// Some useful constants

#define USECPERTICK 50  // microseconds per clock interrupt tick
#define RAWBUF 100 // Length of raw duration buffer

#define TIMER_MODE_SINGLE 0
#define TIMER_MODE_AUTO 1

// Marks tend to be 100us too long, and spaces 100us too short
// when received due to sensor lag.
#define MARK_EXCESS 100

#endif

