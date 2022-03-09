/* TeensyTransfer library code is placed under the MIT license
 * Copyright (c) 2016 Frank Bösing
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _TeensyTransfer_h_
#define _TeensyTransfer_h_


//Disable unneeded functionality by commenting-out one or more of the following lines:
#define _HAVE_SERFLASH	//Serial Flash
#define _HAVE_EEPROM	//Teensy internal EEPROM
//#define _HAVE_PARFLASH	//Parallel Flash

/***********************************************************************/


#include <mk20dx128.h>
#include <avr_functions.h>

#if !defined(KINETISK) && !defined(KINETISL)
#error Use Teensy 3.x
#endif

#if !defined(USB_RAWHID)
#error "Raw Hid" mode not set.
#endif


#ifdef _HAVE_SERFLASH
#include <SerialFlash.h>
#include <SPI.h>

#ifdef FLASHCHIPSELECT  // digital pin for flash chip CS pin
const int FlashChipSelect = FLASHCHIPSELECT;
#else
const int FlashChipSelect = 6;
#endif
#endif

#ifdef _HAVE_PARFLASH
#include <ParallelFlash.h>
#endif


class TeensyTransfer {
public:
	void transfer(void);
private:
	uint8_t buffer[64];// RawHID packets are always 64 bytes
	int hid_sendAck(void);
	int hid_checkAck(void);
	int hid_sendWithAck(void);

#ifdef _HAVE_SERFLASH
	void serflash_write(void);
	void serflash_read(void);
	void serflash_list(void);
	void serflash_erasefile(void);
#endif

#ifdef _HAVE_PARFLASH
	void parflash_write(void);
	void parflash_read(void);
	void parflash_list(void);
	void parflash_erasefile(void);
#endif

#ifdef _HAVE_EEPROM
	void eeprom_write(void);
	void eeprom_read(void);
#endif

};

extern TeensyTransfer ttransfer;
#endif
