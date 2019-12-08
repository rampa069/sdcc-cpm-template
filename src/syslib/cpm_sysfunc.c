#include "cpm_sysfunc.h"

#include "common_datatypes.h"
#include "cpmbdos.h"

#include <stdlib.h>
#include <string.h>

typedef struct {
	uint8_t size;
	uint8_t len;
	char bytes[80];
} RS_BUFFER;

static BDOSCALL bdos_readstr;
static RS_BUFFER rs_buf;

static uint16_t ret_ba, ret_hl;

void cpm_sysfunc_init(void) {
	// Initialize READSTR BDOS call
	bdos_readstr.func8 = C_READSTR;
	bdos_readstr.parm16 = (uint16_t)&rs_buf;
}

char *cpm_gets(char *p) {
	memset(rs_buf.bytes, 0, sizeof(rs_buf.bytes));
	rs_buf.size = sizeof(rs_buf.bytes);
	rs_buf.len = 0;

	cpmbdos_extn(&bdos_readstr, &ret_ba, &ret_hl);

	rs_buf.bytes[rs_buf.len] = '\n';
	strcpy(p, rs_buf.bytes);

	return p;
}

char cpm_getchar(void) {
	BDOSCALL cread = { C_READ, { (uint16_t)0 } };
	return cpmbdos_extn(&cread, &ret_ba, &ret_hl);
}

void cpm_putchar(char c) {
	BDOSCALL cwrite = { C_WRITE, { (uint16_t)c } };
	cpmbdos_extn(&cwrite, &ret_ba, &ret_hl);
}

void cpm_setDMAAddr(uint16_t addr) {
	BDOSCALL fdma = { F_DMAOFF, {addr} };

	cpmbdos_extn(&fdma, &ret_ba, &ret_hl);
}

uint8_t cpm_getCurDrive(void) {
	BDOSCALL drv = { DRV_GET, { 0 } };

	return cpmbdos_extn(&drv, &ret_ba, &ret_hl);	
}

uint8_t cpm_resetDrives(void) {
	BDOSCALL drv = { DRV_ALLRESET, { 0 } };

	return cpmbdos_extn(&drv, &ret_ba, &ret_hl);	
}

uint8_t cpm_setCurDrive(uint8_t drive) {
	BDOSCALL drv = { DRV_SET, { drive } };

	return cpmbdos_extn(&drv, &ret_ba, &ret_hl);
}

void cpm_setFCBname(char *fname, char *ftype, FCB *cb) {
	int idx;
	char c;

	for (idx = 0; (idx < 8) && (fname[idx] != '\0'); idx++) {
		c = fname[idx] & 0x7F;
		if (c >= 0x61 && c <= 0x7a)
			c -= 0x20; 

		cb->filename[idx] = c;
	}

	while (idx < 8) {
		cb->filename[idx] = ' '; // Pad the filename
		idx++;
	}
	
	for (idx = 0; (idx < 3) && (ftype[idx] != '\0'); idx++) {
		c = ftype[idx] & 0x7F;
		if (c >= 0x61 && c <= 0x7a)
			c -= 0x20; 
		
		cb->filetype[idx] = c;
	}

	while (idx < 3) {
		cb->filetype[idx] = ' '; // Pad the filetype
		idx++;
	}
}

uint8_t cpm_performFileOp(FileOperation fop, FCB *cb) {
	BDOSCALL call = { 0, {(uint16_t)cb} };

	switch (fop) {
		case fop_open:
			call.func8 = F_OPEN;
			break;
		case fop_close:
			call.func8 = F_CLOSE;
			break;
		case fop_firstNameMatch:
			call.func8 = F_SMATCH;
			break;
		case fop_nextMatch:
			call.func8 = F_NMATCH;
			break;
		case fop_makeFile:
			call.func8 = F_MAKE;
			break;
		case fop_delFile:
			call.func8 = F_DELETE;
			break;
		case fop_setFileAttr:
			call.func8 = F_ATTRIB;
			break;
		case fop_readSeqRecord:
			call.func8 = F_READ;
			break;
		case fop_writeSeqRecord:
			call.func8 = F_WRITE;
			break;
		case fop_readRandRecord:
			call.func8 = F_READRAND;
			break;
		case fop_writeRandRecord:
			call.func8 = F_WRITERAND;
			break;
		case fop_updRandRecPtr:
			call.func8 = F_RANDREC;
			break;
		case fop_calcFileSize:
		default:
			call.func8 = F_SIZE;
			break;
	}

	return cpmbdos_extn(&call, &ret_ba, &ret_hl);
	//return cpmbdos(&call);
}

void cpm_reset(void) {
	BDOSCALL sreset = { S_RESET, { (uint16_t)0 } };
	cpmbdos_extn(&sreset, &ret_ba, &ret_hl);
}
