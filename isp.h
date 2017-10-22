#ifndef __ISP_H__
#define __ISP_H__




#define PIN_MOSI	11
#define PIN_MISO	12
#define PIN_SCK		14




#include "defines.h"
#include "bitbangspi.h"




struct parameter {
	uint8_t		devicecode;
	uint8_t		revision;
	uint8_t		progtype;
	uint8_t		parmode;
	uint8_t		polling;
	uint8_t		selftimed;
	uint8_t		lockbytes;
	uint8_t		fusebytes;
	uint8_t		flashpoll;
	uint16_t	eeprompoll;
	uint16_t	pagesize;
	uint16_t	eepromsize;
	uint32_t	flashsize;
};




class isp : public spidergame {
public:
	isp() {
		side		= false;
		reset_high	= false;
		error		= 0;
		pmode		= 0;
		here		= 0;
		memset(&param,	0, sizeof(param));
		memset(buff,	0, sizeof(buff));
	}


	virtual void loop( pixelArray **strip, WII **wii);
	virtual void frame(pixelArray **strip, WII **wii);


	INLINE uint8_t reset_pin() {
		return side ? 15 : 10;
	}


protected:
	void avrisp();
	void read_signature();
	void read_page();
	char eeprom_read_page(int length);
	char flash_read_page(int length);
	uint8_t flash_read(uint8_t hilo, unsigned int addr);
	void program_page();
	uint8_t write_eeprom_chunk(unsigned int start, unsigned int length);
	uint8_t write_eeprom(unsigned int length);
	uint8_t write_flash_pages(int length);
	void write_flash(int length);
	unsigned int current_page();
	void commit(unsigned int addr);
	void flash(uint8_t hilo, unsigned int addr, uint8_t data);
	void universal();
	void end_pmode();
	void start_pmode();
	void set_parameters();
	void get_version(uint8_t c);
	void breply(uint8_t b);
	void empty_reply();
	uint8_t spi_transaction(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
	void prog_lamp(int state);
	void fill(int n);
	uint8_t getch();
	void reset_target(bool reset);


private:
	bool	side;

	int		error;
	int		pmode;

	// address for reading and writing, set by 'U' command
	int32_t	here;
	uint8_t	buff[256]; // global block storage

	parameter param;

	bool reset_high;

	BitBangedSPI SPI;
};








#endif //__ISP_H__
