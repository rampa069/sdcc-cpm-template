#ifndef _CPM_SYSFUNC_HEADER_
#define _CPM_SYSFUNC_HEADER_

#include "common_datatypes.h"

typedef struct {
	uint8_t drive; // 0 -> Searches in default disk drive
	char filename[8]; // File name (when opening a '?' means 'any character')
	char filetype[3]; // File type
	uint8_t ex; // Extent
	uint16_t resv; // Reserved for CP/M
	uint8_t rc; // Records used in extent
	uint8_t alb[16]; // Allocation blocks used
	uint8_t seqreq; // Sequential records to read/write
	uint16_t rrec; // Random record to read/write 
	uint8_t rrecob; // Random record overflow byte (MS)
} FCB; /* File Control Block */

typedef struct {
	uint8_t status;
	char filename[8];
	char filetype[3];
	uint8_t xl;
	uint8_t bc;
	uint8_t xh;
	uint8_t rc;
	uint8_t alb[16];
} CPM_DIR;

typedef enum {
	fop_open,
	fop_close,
	fop_firstNameMatch,
	fop_nextMatch,
	fop_makeFile,
	fop_delFile,
	fop_setFileAttr,
	fop_readSeqRecord,
	fop_writeSeqRecord,
	fop_readRandRecord,
	fop_writeRandRecord,
	fop_updRandRecPtr,
	fop_calcFileSize
} FileOperation;

void cpm_sysfunc_init(void);

void cpm_reset(void);

char *cpm_gets(char *p);
char cpm_getchar(void);
void cpm_putchar(char c);

uint8_t cpm_performFileOp(FileOperation fop, FCB *cb);

uint8_t cpm_deleteFile(FCB *cb);
uint8_t cpm_setFileAttribs(FCB *cb);

void cpm_setDMAAddr(uint16_t addr);

uint8_t cpm_getCurDrive(void);
uint8_t cpm_setCurDrive(uint8_t drive);
uint8_t cpm_resetDrives(void);

void cpm_setFCBname(char *fname, char *ftype, FCB *cb);

#endif /* _CPM_SYSFUNC_HEADER_ */
