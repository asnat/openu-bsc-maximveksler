#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/LineParser.o \
	${OBJECTDIR}/CodeSegmentMgr.o \
	${OBJECTDIR}/DataSegmentMgr.o \
	${OBJECTDIR}/Assembler.o \
	${OBJECTDIR}/AsmCommands.o \
	${OBJECTDIR}/LabelTableMgr.o \
	${OBJECTDIR}/ErrorHandler.o \
	${OBJECTDIR}/PhaseOne.o \
	${OBJECTDIR}/main.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/assembler

dist/Release/GNU-Linux-x86/assembler: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/assembler ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/LineParser.o: nbproject/Makefile-${CND_CONF}.mk LineParser.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/LineParser.o LineParser.c

${OBJECTDIR}/CodeSegmentMgr.o: nbproject/Makefile-${CND_CONF}.mk CodeSegmentMgr.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CodeSegmentMgr.o CodeSegmentMgr.c

${OBJECTDIR}/DataSegmentMgr.o: nbproject/Makefile-${CND_CONF}.mk DataSegmentMgr.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataSegmentMgr.o DataSegmentMgr.c

${OBJECTDIR}/Assembler.o: nbproject/Makefile-${CND_CONF}.mk Assembler.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Assembler.o Assembler.c

${OBJECTDIR}/AsmCommands.o: nbproject/Makefile-${CND_CONF}.mk AsmCommands.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AsmCommands.o AsmCommands.c

${OBJECTDIR}/LabelTableMgr.o: nbproject/Makefile-${CND_CONF}.mk LabelTableMgr.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/LabelTableMgr.o LabelTableMgr.c

${OBJECTDIR}/ErrorHandler.o: nbproject/Makefile-${CND_CONF}.mk ErrorHandler.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ErrorHandler.o ErrorHandler.c

${OBJECTDIR}/PhaseOne.o: nbproject/Makefile-${CND_CONF}.mk PhaseOne.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/PhaseOne.o PhaseOne.c

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/assembler

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
