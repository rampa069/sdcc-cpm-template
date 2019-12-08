tools:	$(LBIN_DIR)/load $(LBIN_DIR)/binpak

LCFLAGS=-O2

tools-clean:
	rm -f $(LBIN_DIR)/*

$(LBIN_DIR)/load: $(LSRC_DIR)/load.c
	$(CC) $(LCFLAGS) $(LSRC_DIR)/load.c -o $(LBIN_DIR)/load

$(LBIN_DIR)/binpak: $(LSRC_DIR)/binpak.c
	$(CC) $(LCFLAGS) $(LSRC_DIR)/binpak.c -o $(LBIN_DIR)/binpak
