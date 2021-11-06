TARGET = Dizzy
OBJS =cactionadditem.o \
cactionaddlife.o \
cactionaddscore.o \
cactionchangeanimationmode.o  \
cactionchangedescription.o \
cactionchangedescriptionglobal.o \
cactionchangename.o \
cactionchangenameglobal.o \
cactionchangeposition.o \
cactioncopyposition.o \
cactioncopypositionoffset.o \
cactionenergyupdate.o \
cactionmessage.o \
cactionmove.o \
cactionpickup.o \
cactionsetanimationstep.o \
cactionsetenabled.o \
cactionsingle.o \
cautomath.o \
cconditionalofdizzyintersection.o \
cconditionalofintersection.o \
cconditionalofnotdizzyintersection.o \
cconditionalofpickup.o \
cconditionaloftimer.o \
cconditionalofuse.o \
cdizzy.o \
cfontprinter.o \
cgame.o \
cgamestate.o \
clexeme.o \
clexicalanalyzer.o \
cpart.o \
craiifilein.o \
craiifileout.o \
csprite.o \
csyntaxanalyzer.o \
ctile.o \
ctilessequence.o \
iaction.o \
iconditionalexpression.o \
ipart.o \
ivideo.o \
system.o \
tga.o \
cvideo_software.o \
main.o
INCDIR =
CFLAGS = -O3 -G0 -Wall -std=c++11
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LIBDIR =
LDFLAGS =
LIBS =-lpspgum -lpspgu -lm -lstdc++ -lpspaudiolib -lpspaudio -lpsprtc
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Dizzy
PSP_EBOOT_ICON = ICON.PNG
PSP_EBOOT_ICON1 =
PSP_EBOOT_UNKPNG = PIC.PNG
PSP_EBOOT_PIC1 =
PSP_EBOOT_SND0 =
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak



