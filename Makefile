TARGET = Dizzy
OBJS =csyntaxanalyzer.o cgame.o cvideo_software.o csprite.o clexicalanalyzer.o tga.o cpart.o ctilessequence.o cdizzy.o system.o cfontprinter.o cgamestate.o cautomath.o cconditionalofuse.o cconditionalofintersection.o main.o cconditionalofnotdizzyintersection.o cconditionalofdizzyintersection.o cconditionalofpickup.o cactioncopypositionoffset.o cactioncopyposition.o clexeme.o cconditionaloftimer.o cactionchangedescriptionglobal.o cactionchangenameglobal.o ctile.o cactionchangeanimationmode.o cactionmessage.o cactionchangedescription.o cactionsetenabled.o cactionchangeposition.o cactionsetanimationstep.o cactionenergyupdate.o cactionchangename.o cactionmove.o cactionaddscore.o cactionsingle.o cactionpickup.o cactionadditem.o cactionaddlife.o ivideo.o ipart.o iconditionalexpression.o craiifileout.o craiifilein.o iaction.o
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



