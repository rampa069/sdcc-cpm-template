include common.mk

all: tools libraries hello 

clean:	tools-clean libraries-clean hello-clean 
	rm -f $(BIN_DIR)/*

include tools.mk # Local tools
include libraries.mk # Libraries
include hello.mk #  hello world

include esrc/hello/hello.mk

