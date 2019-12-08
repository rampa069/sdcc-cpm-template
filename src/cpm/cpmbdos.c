#include "cpmbdos.h"


uint8_t cpmbdos(BDOSCALL *p) __naked {
	p;
	__asm
		push	ix
		ld		ix,#0
		add		ix,sp
		
		ld		l,4(ix)
		ld		h,5(ix)
		ld		c,(hl)	; Load function
		inc		hl
		ld		e,(hl)	; Prepare parameter in E ...
		inc		hl
		ld		d,(hl)  ; And prepare parameter in D
		call	5		; Make BDOS call!
		pop		ix
		ret
	__endasm;
}


uint8_t cpmbdos_extn(BDOSCALL *p, uint16_t* ret_ba, uint16_t *ret_hl) __naked {
	p; ret_ba; ret_hl;

	__asm
		push	ix
		ld		ix,#0x00
		add		ix,sp

		ld		l,4(ix)	; Load the pointer to BDOSCALL p into HL 
		ld		h,5(ix)	; Prepare HL to contain the parameter address

		ld		c,(hl)	; Load p->func8 in register C

		inc		hl		; Inrease the address so we point to first byte of p->parm16
		ld		e,(hl)	; Read first byte...
		inc		hl
		ld		d,(hl)	; Read second byte. We have p->parm16 in DE

		call	5		; Execute BDOS call!

		; We now have the return values in BA and HL
		push bc
		push hl

		ld		ix,#0x00
		add		ix,sp

		ld		l,10(ix)
		ld		h,11(ix) ; Load pointer to ret_ba
		ld		(hl),b
		inc		hl
		ld		(hl),a

		ld		l,12(ix)
		ld		h,13(ix)

		pop		bc		; Recover the HL we have pushed
		ld		(hl),b
		inc		hl
		ld		(hl),c

		push 	bc; Put HL back where it belongs
		pop		hl;

		pop		bc ; Restore BC
		pop		ix ; Restore IX
		ret
	__endasm;
}

