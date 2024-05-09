# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.

PS2DEV = /usr/local
PS2SDK = $(PS2DEV)/ps2sdk
GSKIT = $(PS2DEV)/gsKit
PS2EEBIN = $(PS2DEV)/ee/bin

ISO_TGT = prod_triangle.iso

EE_BIN = main.elf
EE_OBJS = main.o
EE_INCLUDE = -I$(GSKIT)/include
EE_LIBS = -L. -L$(GSKIT)/lib -L$(GSKIT)/lib -lpacket -ldma -lgraph -ldraw -lc -lgskit -ldmakit

all: $(ISO_TGT)

all_strip: $(EE_BIN)
	$(EE_STRIP) --strip-all $(EE_BIN)

$(ISO_TGT): $(EE_BIN)
	mkisofs -l -o $(ISO_TGT) $(EE_BIN) SYSTEM.CNF

clean:
	rm -f $(EE_BIN) $(EE_OBJS)

include Makefile.pref
include Makefile.eeglobal
