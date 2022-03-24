##############################################################################
#           Makefile for use by LiveData developers                          #
#                                                                            #
#  NOTE: "vcvarsall amd64" must be run before attempting to compile the API  #
#  examples. Please see the API documentation for information.               #
#                                                                            #
##############################################################################

#
# If the location of the Alias libraries and header files are
# different from $ALIAS_LOCATION, set it here.
#
ALIAS_LOCATION=C:\Program Files\Autodesk\AliasSurface2021

EXAMPLES = helloWorld.plugin


#
# Run vcvarsall to properly configure the 
# development environment.
#
CC = cl.exe
CPLUSPLUS = cl.exe
LINK = link.exe
RC = rc.exe
INCLUDES = /I. /I"$(ALIAS_LOCATION)\ODS\Common\include"

#
# Some code is conditionally compiled because it produces a lot of output.
# (see AlPrint.cpp for example) Uncomment the following line if you would
# like to see all the output.
#
# COPIOUS_OUTPUT = /DCOPIOUS_OUTPUT

#
# Debug Flags - uncomment to remove debug information.
#
CDBFLAG = /DEBUG /Z7
LDBFLAG = /DEBUG

#
# Flags
#
CFLAGS = /nologo /MD $(CDBFLAG) $(INCLUDES) $(COPIOUS_OUTPUT)
CPLUSPLUSFLAGS = $(CFLAGS) /EHsc

# 
# The 'libAlisCore.lib' is used for resolving the plug-ins symbols.
#
PLUGINFLAGS = /nologo  /DLL /opt:noref /incremental:no \
	"$(ALIAS_LOCATION)\lib\libAliasCore.lib" $(LDBFLAG)
	
LFLAGS=

# Extra link libraries
EXTRA_LIBS = kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

#
# Rules for building.
#
.SUFFIXES: .plugin .obj .cpp .c

.cpp.plugin: 
	$(CPLUSPLUS) -c $(CPLUSPLUSFLAGS) $<
	$(LINK) $(PLUGINFLAGS) /out:.\lib\$*.plugin $*.obj

.obj.plugin: 
	$(LINK) $(PLUGINFLAGS) /out:.\lib\$*.plugin $<

.cpp.obj:
	$(CPLUSPLUS) -c $(CPLUSPLUSFLAGS) $*.cpp

.c.obj:
	$(CC) -c $(CFLAGS) $*.c

.c.i:
	 $(CC) -E $(CFLAGS) $*.c | sed -e '/^[    ]*$$/d' > $*.i

.cpp.i:
	$(CPLUSPLUS) -E $(CPLUSPLUSFLAGS) $*.cpp | sed -e '/^[  ]*$$/d' > $*.i

#
# Build all the examples.
#
default: $(EXAMPLES)

#
# Copy all the source files for the examples, ignoring errors ( - option )
#
copy:
	- copy "$(ALIAS_LOCATION)\ODS\OpenAlias\examples\*.cpp" .
	- copy "$(ALIAS_LOCATION)\ODS\OpenAlias\examples\*.c" .
	- copy "$(ALIAS_LOCATION)\ODS\OpenAlias\examples\*.h" .
	- copy "$(ALIAS_LOCATION)\ODS\OpenAlias\examples\*.rc" .
	- mkdir scm  
	- mkdir lib
	- copy "$(ALIAS_LOCATION)\ODS\OpenAlias\examples\scm\*" scm
	- copy "$(ALIAS_LOCATION)\ODS\Common\examples\*.cpp" .
	- copy "$(ALIAS_LOCATION)\ODS\Common\examples\*.c" .
	- copy "$(ALIAS_LOCATION)\ODS\Common\examples\*.h" .

#
# Clean up.
#
clean:
	del *.obj lib\*.plugin lib\*.exp lib\*.lib
	
#
# Rules for building specific examples.
#
helloWorld.plugin: helloWorld.obj
	$(LINK) $(PLUGINFLAGS) /out:.\lib\$@ helloWorld.obj $(EXTRA_LIBS)