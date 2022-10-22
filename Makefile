#OS := windows
OS := linux
# add source files here (pdr_rodando.c)
SRCS := menu.c partida.c letras.c director.c pila.c arrancar_xogo.c transf.c graficos.c boton.c lista.c

# generate names of object files
OBJS := $(SRCS:.c=.o)
HDRS := menu.h partida.h letras.h director.h pila.h transf.h graficos.h boton.h lista.h
# name of executable
EXEC := game
#-static -static-libgcc
#x86_64-w64-mingw32-gcc
#i686-w64-mingw32-gcc
#`sdl2-config --libs --cflags`
#-I/home/dev/ccrlibs/usr/local/include/SDL2 -I/home/dev/ccrlibs/usr/local/include
#-w -fpermissive /home/dev/ccrlibs/usr/local/bin/sdl2-config --cflags
#`/home/dev/ccrlibs/usr/local/bin/sdl2-config --static-libs`
#-lmingw32 -lSDL2main -lmpg123 -lpng -lz
ifeq ($(OS),windows)
	CC := x86_64-w64-mingw32-gcc
	CFLAGS= -I/home/dev/ccrlibs/usr/local/include/SDL2 -I/home/dev/ccrlibs/usr/local/include
	HDRS :=
	LDFLAGS := -static -static-libgcc
	LIBS= -L/home/dev/ccrlibs/usr/local/lib -lmingw32 -lSDL2main -lSDL2 -lm -lkernel32 -ladvapi32 -lgdi32 -limm32 -lmsvcrt -lole32 -loleaut32 -lsetupapi -lshell32 -luser32 -lversion -lwinmm
	#-lSDL_image -lSDL_ttf -lSDL_mixer
else
	CC := gcc
	CFLAGS := -ggdb3 -O0 --std=c99 -Wall
	# add header files here
	HDRS :=
	LDFLAGS :=
	LIBS := -lSDL2 -lm
endif
# default recipe
all: $(EXEC)

# ESTA E A DE WINDOWS
$(EXEC): ${OBJS}
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
	#$(CC) -o pdr_rodando.exe pdr_rodando.o -L/usr/local/x86_64-w64-mingw32/lib -lSDL2main -lSDL2 -lSDL_image -lSDL_ttf -lSDL_mixer

#$(OBJS): $(@:.o=.c) $(HDRS) Makefile
#	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)
# ESTA E A DE WINDOWS
arrancar_xogo.o: arrancar_xogo.c director.o menu.o
	$(CC) $(CFLAGS) $< -c -o $@

director.o: director.c pila.o
	$(CC) $(CFLAGS) $< -c -o $@

pila.o: pila.c
	$(CC) $(CFLAGS) $< -c -o $@

menu.o: menu.c letras.o boton.o
	$(CC) $(CFLAGS) $< -c -o $@
#	#$(CC) -o ${OBJS} -c -I/usr/local/x86_64-w64-mingw32/include/SDL2 pdr_rodando.c

partida.o: partida.c graficos.o transf.o lista.o
	$(CC) $(CFLAGS) $< -c -o $@

boton.o: boton.c letras.o graficos.o
	$(CC) $(CFLAGS) $< -c -o $@

letras.o: letras.c transf.o graficos.o
	$(CC) $(CFLAGS) $< -c -o $@

transf.o: transf.c graficos.o
	$(CC) $(CFLAGS) $< -c -o $@

graficos.o: graficos.c
	$(CC) $(CFLAGS) $< -c -o $@

lista.o: lista.c
	$(CC) $(CFLAGS) $< -c -o $@
#letras.o: letras.c
#	$(CC) $(CFLAGS) $< -c -o $@

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: clean

# recipe for building the final executable
#$(EXEC): $(OBJS) $(HDRS) Makefile
#	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
#$(OBJS): $(@:.o=.c) $(HDRS) Makefile
#	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)
