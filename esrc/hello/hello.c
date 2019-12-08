#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpmbdos.h"
#include "cprintf.h"
#include "syslib/cpm_sysfunc.h"
#include "syslib/ansi_term.h"


void sys_init(void) {
	cpm_sysfunc_init();
}

void main()
{
  sys_init();
  printf("Hello World!\n");
}

