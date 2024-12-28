# ----------------------------

NAME = RENDER
DESCRIPTION = "OBJ Renderer for TI-84"
COMPRESSED = YES
ARCHIVED = YES

CFLAGS = -Wall -Oz

LTO = YES

# ----------------------------

all: asset
include $(shell cedev-config --makefile)

# ----------------------------

.PHONY: asset

asset:
	xxd -i -n data assets/* | sed 's/unsigned char/const char/g; s/unsigned int/const unsigned int/g;' > src/data.h

clean:
	rm -r obj bin src/data.h