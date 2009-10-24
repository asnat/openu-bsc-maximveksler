# SlickEdit generated file.  Do not edit this file except in designated areas.

# Make command to use for dependencies
MAKE=make
RM=rm
MKDIR=mkdir

# -----Begin user-editable area-----

# -----End user-editable area-----

# If no configuration is specified, "Debug" will be used
ifndef CFG
CFG=Debug
endif

#
# Configuration: Debug
#
ifeq "$(CFG)" "Debug"
OUTDIR=Debug
OUTFILE=$(OUTDIR)/20465
CFG_INC=
CFG_LIB=
CFG_OBJ=
COMMON_OBJ=$(OUTDIR)/CharEncodeDemo.o 
OBJ=$(COMMON_OBJ) $(CFG_OBJ)
ALL_OBJ=$(OUTDIR)/CharEncodeDemo.o 

COMPILE=gcc -ansi -c    -g -o "$(OUTDIR)/$(*F).o" $(CFG_INC) "$<"
LINK=gcc -ansi  -g -o "$(OUTFILE)" $(OBJ) $(CFG_LIB)

# Pattern rules
$(OUTDIR)/%.o : %.c
	$(COMPILE)

# Build rules
all: $(OUTFILE)

$(OUTFILE): $(OUTDIR)  $(OBJ)
	$(LINK)

$(OUTDIR):
	$(MKDIR) -p "$(OUTDIR)"

# Rebuild this project
rebuild: cleanall all

# Clean this project
clean:
	$(RM) -f $(OUTFILE)
	$(RM) -f $(OBJ)

# Clean this project and all dependencies
cleanall: clean
endif

#
# Configuration: Release
#
ifeq "$(CFG)" "Release"
OUTDIR=Release
OUTFILE=$(OUTDIR)/20465
CFG_INC=
CFG_LIB=
CFG_OBJ=
COMMON_OBJ=$(OUTDIR)/CharEncodeDemo.o 
OBJ=$(COMMON_OBJ) $(CFG_OBJ)
ALL_OBJ=$(OUTDIR)/CharEncodeDemo.o 

COMPILE=gcc -ansi -c   -o "$(OUTDIR)/$(*F).o" $(CFG_INC) "$<"
LINK=gcc -ansi  -o "$(OUTFILE)" $(OBJ) $(CFG_LIB)

# Pattern rules
$(OUTDIR)/%.o : %.c
	$(COMPILE)

# Build rules
all: $(OUTFILE)

$(OUTFILE): $(OUTDIR)  $(OBJ)
	$(LINK)

$(OUTDIR):
	$(MKDIR) -p "$(OUTDIR)"

# Rebuild this project
rebuild: cleanall all

# Clean this project
clean:
	$(RM) -f $(OUTFILE)
	$(RM) -f $(OBJ)

# Clean this project and all dependencies
cleanall: clean
endif