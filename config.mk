# Project: LD29
# Makefile configurations

BIN		=	$(TOPDIR)/bin/fanten-bbts.elf

#DBGFLAGS	=	-O0 -g -D__DEBUG__
DBGFLAGS	=	-O3 -g
#Flags specific for tools
LDTOOLS		:=	$(LDFLAGS)
CFLAGS		:=	$(CFLAGS) -Wall -O3 $(DBGFLAGS)
#General flags
CFLAGS		+=	-Wall 
LDFLAGS		+=	-ldarnit

#Extra install targets
INSTARG		=	

#Makefile tools
RM		=	rm -Rf
MKDIR		=	mkdir -p

