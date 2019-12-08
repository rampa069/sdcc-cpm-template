example-hello: $(BIN_DIR)/hello.com

$(BIN_DIR)/hello.com:	tools $(BIN_DIR)/hello.ihx
	$(LBIN_DIR)/load $(BIN_DIR)/hello

$(BIN_DIR)/hello.ihx:	libraries $(BIN_DIR)/hello.rel $(BIN_DIR)/hello.arf 
	$(CLD) $(CLD_FLAGS) -nf $(BIN_DIR)/hello.arf

$(BIN_DIR)/hello.rel: $(ESRC_DIR)/hello/hello.c
	$(CCC) $(CCC_FLAGS) -o $(BIN_DIR) -DPRINTF $(ESRC_DIR)/hello/hello.c

$(BIN_DIR)/hello.arf:	$(BIN_DIR)/generic.arf
	$(QUIET)$(SED) 's/$(REPLACE_TAG)/hello/' $(BIN_DIR)/generic.arf > $(BIN_DIR)/hello.arf 
