# project name (generate executable with this name)
TARGET = undirect_graph_jrb_test

CC=gcc
# compiling flags here
CFLAGS= -g -Wall
# -g adds debugging information to the executable file
# -Wall turns on most, but not all, complier warnings

IDIR = ../libfdr
# define any directories containing header file other then /usr/include
INCLUDES = -I $(IDIR)

# define any libraries to link into executable:
# if I want to link in libraries
# (libx.so or libx.a) I use the -llibname (-lx -lx) = (-lx)
# libfdr => -lfdr
LIBS = -lfdr
# LIBS = -lm -lbt -lfdr

# define any directories containing implementation of the file in INCLUDES
# ../..lib means up 2 level then search for /lib
LDIR = ../libfdr
LFLAGS = -L $(LDIR)

# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
# For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix

SRCS = $(wildcard *.c)
ODIR = obj
_OBJS = $(SRCS:.c=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

.PHONY: clean
#action
all: $(TARGET) 
# This uses Suffix Replacement within a macro:
#   $@ = left-part of ":" ( == $(TARGET))
# 
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LFLAGS) $(LIBS)
	@echo "Linking complete!"

$(ODIR)/%.o: %.c $(DEPS)
	@mkdir -p obj
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	rm -f core $(ODIR)/*.o *~ $(TARGET)
	@echo "Cleanup complete!"
#depend: $(SRCS)
#        makedepend $(INCLUDES) $^
