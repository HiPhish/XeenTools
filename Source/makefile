CFLAGS   = -std=c11 -pedantic-errors -Werror -Wall -g
CC       = clang
OBJECTS  = cc_tool.o     \
           sprite_tool.o \
		   chr_tool.o    \
           pal_tool.o    \
		   cpp_tool.o    \
		   gnd_tool.o    \
		   sky_tool.o    \
		   raw_tool.o    \
           fnt_tool.o
BINARIES = cc_extract sprite_extract pal_extract cpp_extract fnt_extract \
           raw_extract

#===[ TARGETS ]=================================================================

# Unoptimised build for debugging.
debug: CFLAGS += -O0
debug: binaries objects

# Optimised build for release.
release: CFLAGS += -O2
release: binaries objects

binaries: ${BINARIES}

objects: ${OBJECTS}

# Run static analyser.
analyze: CFLAGS += --analyze
analyze: ${BINARIES} $(OBJECTS)

# Alternate spelling.
analyse: analyze

#---[ BINARIES ]----------------------------------------------------------------

cc_extract: cc_extract.c cc_tool.o
	@${CC} ${CFLAGS} -o cc_extract cc_tool.o cc_extract.c

sprite_extract: sprite_extract.c sprite_tool.o pal_tool.o
	@${CC} ${CFLAGS} -o sprite_extract sprite_extract.c sprite_tool.o pal_tool.o

pal_extract: pal_extract.c pal_tool.o
	@${CC} ${CFLAGS} -o pal_extract pal_extract.c pal_tool.o

cpp_extract: cpp_extract.c cpp_tool.o
	@${CC} ${CFLAGS} -o cpp_extract cpp_extract.c cpp_tool.o

fnt_extract: fnt_extract.c fnt_tool.o
	@${CC} ${CFLAGS} -o fnt_extract fnt_extract.c fnt_tool.o

raw_extract: raw_extract.c raw_tool.o sprite_tool.o pal_tool.o
	@${CC} ${CFLAGS} -o raw_extract raw_extract.c raw_tool.o sprite_tool.o pal_tool.o

#---[ OBJECTS ]-----------------------------------------------------------------

cc_tool.o: cc_tool/cc_tool.c cc_tool/cc_tool.h
	@${CC} ${CFLAGS} -c -o cc_tool.o $*/$*.c

sprite_tool.o: sprite/sprite_tool.c sprite/sprite_tool.h
	@${CC} ${CFLAGS} -c -o sprite_tool.o sprite/$*.c

pal_tool.o: pal/pal_tool.c pal/pal_tool.h
	@${CC} ${CFLAGS} -c -o pal_tool.o pal/$*.c

cpp_tool.o: cpp/cpp_tool.c cpp/cpp_tool.h
	@${CC} ${CFLAGS} -c -o cpp_tool.o cpp/$*.c

fnt_tool.o: fnt/fnt_tool.c fnt/fnt_tool.h
	@${CC} ${CFLAGS} -c -o fnt_tool.o fnt/$*.c

gnd_tool.o: gnd/gnd_tool.c gnd/gnd_tool.h
	@${CC} ${CFLAGS} -c -o gnd_tool.o gnd/$*.c

sky_tool.o: sky/sky_tool.c sky/sky_tool.h
	@${CC} ${CFLAGS} -c -o sky_tool.o sky/$*.c

chr_tool.o: chr/chr_tool.c chr/chr_tool.h
	@${CC} ${CFLAGS} -c -o chr_tool.o chr/$*.c

raw_tool.o: raw/raw_tool.c raw/raw_tool.h xeen/xeen.h
	@${CC} ${CFLAGS} -c -o raw_tool.o raw/$*.c

#---[ Phony targets ]-----------------------------------------------------------

clean:
	@rm -R *.o *.plist *.dSYM ${BINARIES}

