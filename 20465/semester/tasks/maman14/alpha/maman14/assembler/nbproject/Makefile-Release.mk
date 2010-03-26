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
	${OBJECTDIR}/codeSegmentMgr.o \
	${OBJECTDIR}/labelTableMgr.o \
	${OBJECTDIR}/phaseOne.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/label.o \
	${OBJECTDIR}/stringUtil.o \
	${OBJECTDIR}/errorHandler.o \
	${OBJECTDIR}/assembler.o \
	${OBJECTDIR}/lineParser.o \
	${OBJECTDIR}/dataSegmentMgr.o \
	${OBJECTDIR}/hash.o \
	${OBJECTDIR}/asmCommands.o

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

${OBJECTDIR}/codeSegmentMgr.o: nbproject/Makefile-${CND_CONF}.mk codeSegmentMgr.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/codeSegmentMgr.o codeSegmentMgr.c

${OBJECTDIR}/labelTableMgr.o: nbproject/Makefile-${CND_CONF}.mk labelTableMgr.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/labelTableMgr.o labelTableMgr.c

${OBJECTDIR}/phaseOne.o: nbproject/Makefile-${CND_CONF}.mk phaseOne.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/phaseOne.o phaseOne.c

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/label.o: nbproject/Makefile-${CND_CONF}.mk label.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/label.o label.c

${OBJECTDIR}/stringUtil.o: nbproject/Makefile-${CND_CONF}.mk stringUtil.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/stringUtil.o stringUtil.c

${OBJECTDIR}/errorHandler.o: nbproject/Makefile-${CND_CONF}.mk errorHandler.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/errorHandler.o errorHandler.c

${OBJECTDIR}/assembler.o: nbproject/Makefile-${CND_CONF}.mk assembler.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/assembler.o assembler.c

${OBJECTDIR}/lineParser.o: nbproject/Makefile-${CND_CONF}.mk lineParser.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/lineParser.o lineParser.c

${OBJECTDIR}/dataSegmentMgr.o: nbproject/Makefile-${CND_CONF}.mk dataSegmentMgr.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/dataSegmentMgr.o dataSegmentMgr.c

${OBJECTDIR}/hash.o: nbproject/Makefile-${CND_CONF}.mk hash.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/hash.o hash.c

${OBJECTDIR}/asmCommands.o: nbproject/Makefile-${CND_CONF}.mk asmCommands.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/asmCommands.o asmCommands.c

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
