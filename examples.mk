REPLACE_TAG=REPLACE_ME_PLEASE

examples:	$(BIN_DIR)/generic.arf

examples-clean:
	rm -f $(BIN_DIR)/*.com
	rm -f $(BIN_DIR)/*.ihx
	rm -f $(BIN_DIR)/*.arf

$(BIN_DIR)/generic.arf:	
	$(QUIET)$(ECHO) Generating generic.arf
	$(QUIET)$(ECHO) -mjx > $(BIN_DIR)/generic.arf
	$(QUIET)$(ECHO) -i $(BIN_DIR)/$(REPLACE_TAG).ihx >> $(BIN_DIR)/generic.arf
	$(QUIET)$(ECHO) -k $(COMPILER_LIBS) >> $(BIN_DIR)/generic.arf
	$(QUIET)$(ECHO) -l z80 >> $(BIN_DIR)/generic.arf
	$(QUIET)$(ECHO) $(BIN_DIR)/cpm0.rel >> $(BIN_DIR)/generic.arf
	$(QUIET)$(ECHO) $(BIN_DIR)/cpmbdos.rel >> $(BIN_DIR)/generic.arf
	$(QUIET)$(ECHO) $(BIN_DIR)/cprintf.rel >> $(BIN_DIR)/generic.arf
	$(QUIET)$(ECHO) $(BIN_DIR)/cpm_sysfunc.rel >> $(BIN_DIR)/generic.arf
	$(QUIET)$(ECHO) $(BIN_DIR)/ansi_term.rel >> $(BIN_DIR)/generic.arf
	$(QUIET)$(ECHO) $(BIN_DIR)/hw_common.rel >> $(BIN_DIR)/generic.arf
	$(QUIET)$(ECHO) $(BIN_DIR)/hw_modprn02.rel >> $(BIN_DIR)/generic.arf
	$(QUIET)$(ECHO) $(BIN_DIR)/$(REPLACE_TAG).rel >> $(BIN_DIR)/generic.arf
	$(QUIET)$(ECHO) -e >> $(BIN_DIR)/generic.arf
