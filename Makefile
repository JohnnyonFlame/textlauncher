TARGET=textlauncher
CFLAGS=-I/usr/include/SDL -I. -I./textscreen/ -Wno-write-strings -O2
CXXFLAGS=-I/usr/include/SDL -I. -I./textscreen/ -fpermissive -Wno-write-strings -O2
LDFLAGS=
LIBS=-lSDL -lpthread

CC=gcc
CXX=g++

SRC= 	c_cvars.cpp \
		cl_cvarlist.cpp \
		sv_cvarlist.cpp \
		main.cpp \
		network.cpp \
		panel.cpp \
		wad.cpp
		
SRC2=	textscreen/txt_radiobutton.c \
		textscreen/txt_window_action.c \
		textscreen/txt_io.c \
		textscreen/txt_strut.c \
		textscreen/txt_inputbox.c \
		textscreen/txt_table.c \
		textscreen/txt_dropdown.c \
		textscreen/txt_desktop.c \
		textscreen/txt_widget.c \
		textscreen/txt_window.c \
		textscreen/txt_scrollpane.c \
		textscreen/txt_spinctrl.c \
		textscreen/txt_separator.c \
		textscreen/txt_button.c \
		textscreen/txt_utf8.c \
		textscreen/txt_sdl.c \
		textscreen/txt_checkbox.c \
		textscreen/txt_gui.c \
		textscreen/txt_label.c

	 
OBJ= $(patsubst %.cpp,%.o,$(SRC))
OBJ2= $(patsubst %.c,%.o,$(SRC2))

all: $(OBJ) $(OBJ2)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJ) $(OBJ2) $(LIBS)
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	@rm -rf $(TARGET) $(OBJ) $(OBJ2)