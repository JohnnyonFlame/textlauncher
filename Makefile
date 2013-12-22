TARGET=textlauncher

# Platform related settings
ifeq ($(PLATFORM), gcw)
	CC=mipsel-linux-gcc
	CXX=mipsel-linux-g++
	
	INCLUDE=-I/opt/gcw0-toolchain/usr/mipsel-gcw0-linux-uclibc/sysroot/usr/include/ -I/opt/gcw0-toolchain/usr/mipsel-gcw0-linux-uclibc/sysroot/usr/include/SDL
else
	CC=gcc
	CXX=g++
	
	INCLUDE=-I/usr/include/SDL -I. -I./textscreen/
endif

ifeq ($(BUILD), debug)
	CFLAGS=-Wno-write-strings -O0 -ggdb
	CXXFLAGS=$(CFLAGS) -fpermissive
else
	CFLAGS=-Wno-write-strings -O2
	CXXFLAGS=$(CFLAGS) -fpermissive
endif

LDFLAGS=
LIBS=-lSDL -lpthread

SRC_COMMON= textscreen/txt_radiobutton.o \
			textscreen/txt_window_action.o \
			textscreen/txt_io.o \
			textscreen/txt_strut.o \
			textscreen/txt_inputbox.o \
			textscreen/txt_table.o \
			textscreen/txt_dropdown.o \
			textscreen/txt_desktop.o \
			textscreen/txt_widget.o \
			textscreen/txt_window.o \
			textscreen/txt_scrollpane.o \
			textscreen/txt_spinctrl.o \
			textscreen/txt_separator.o \
			textscreen/txt_button.o \
			textscreen/txt_utf8.o \
			textscreen/txt_sdl.o \
			textscreen/txt_checkbox.o \
			textscreen/txt_gui.o \
			textscreen/txt_label.o \
			common.o
			
SRC_MP = 	c_cvars.o \
			cl_cvarlist.o \
			sv_cvarlist.o \
			mp_main.o \
			network.o \
			panel.o \
			wad.o
			
SRC_SP =	sp_main.o \
			iwad_selector.o \
			wad.o
	 
# OBJ= $(patsubst %.cpp,%.o,$(SRC))

all: $(SRC_MP) $(SRC_SP) $(SRC_COMMON)
	$(CXX) $(LDFLAGS) -o $(TARGET)-mp $(SRC_COMMON) $(SRC_MP) $(LIBS)
	$(CXX) $(LDFLAGS) -o $(TARGET)-sp $(SRC_COMMON) $(SRC_SP) $(LIBS)
	
%.o: %.cpp
	$(CXX) $(INCLUDE) $(CXXFLAGS) -c $< -o $@
	
%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@
	
clean:
	@rm -rf $(TARGET)-* $(SRC_MP) $(SRC_SP) $(SRC_COMMON)