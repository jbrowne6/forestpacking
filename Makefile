#Compiler and Linker
#CC          := g++-mp-4.7
CC          := g++ -std=c++11
#CC          := g++-6 -std=c++11

#The Target Binary Program
#TARGET      := packer
TARGET      := packerWriteTime

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
INCDIR      := inc
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := res
SRCEXT      := cpp
DEPEXT      := d
OBJEXT      := o

#Flags, Libraries and Includes
CFLAGS      := -fopenmp -Wall -O3 -ffast-math 
#LIB         := -fopenmp -lm 
#LIB         := -fopenmp -lm -lnuma
LIB         := -fopenmp -lm -O3 -ffast-math 
#LIB         := -fopenmp -lm -O3 -ffast-math -llikwid
INC         := -I$(INCDIR) -I/usr/local/include -I/usr/local/bin/../include/ -L/usr/local/bin/../lib/ 
#INC         := -I$(INCDIR) -I/usr/local/include -I/usr/local/bin/../include/ -L/usr/local/bin/../lib/ -DLIKWID_PERFMON
INCDEP      := -I$(INCDIR)

#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
ALLOBJS			:= obj/improv1.o obj/improv2.o obj/improv4.o obj/improv6.o obj/improv8.o obj/naive.o obj/inferenceSamples.o obj/padForest.o obj/padNode.o obj/padNodeStat.o obj/treeBin2.o

###########################ExperimentAll####################
experimentAll: | resources experimentAllMove experimentAllCombine

experimentAllMove:	
experimentAllMove:	SOURCES    := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
experimentAllMove:	OBJECTS    := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

experimentAllCombine: $(OBJECTS)
	$(CC) -o $(TARGETDIR)/experiment1 obj/experiment1.o $(ALLOBJS) $(LIB)
	$(CC) -o $(TARGETDIR)/experiment2 obj/experiment2.o $(ALLOBJS) $(LIB)
	$(CC) -o $(TARGETDIR)/experiment3 obj/experiment3.o $(ALLOBJS) $(LIB)
	$(CC) -o $(TARGETDIR)/experiment4 obj/experiment4.o $(ALLOBJS) $(LIB)
	$(CC) -o $(TARGETDIR)/experiment5a obj/experiment5a.o $(ALLOBJS) $(LIB)
	$(CC) -o $(TARGETDIR)/experiment5d obj/experiment5d.o $(ALLOBJS) $(LIB)
###########################################################




packer: mvPacker all rmPacker

mvPacker:
	cp res/packerWriteTime.cpp src/

rmPacker:
	rm src/packerWriteTime.cpp


#Defauilt Make
all: resources $(TARGET)

#Remake
remake: cleaner all

#Copy Resources from Resources Directory to Target Directory
resources: directories
#	@cp $(RESDIR)/* $(TARGETDIR)/

###########################Experiment1####################
experiment1: | experiment1Move resources experiment1Remove

experiment1Move:	
#	@cp experiments/experiment1/experiment1.cpp src/
experiment1Move:	TARGET     := experiment1
experiment1Move:	SOURCES    := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
experiment1Move:	OBJECTS    := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

experiment1Remove: $(OBJECTS)
	$(CC) -o $(TARGETDIR)/experiment1 obj/experiment1.o $(ALLOBJS) $(LIB)
	$(CC) -o $(TARGETDIR)/experiment2 obj/experiment2.o $(ALLOBJS) $(LIB)
###########################################################




###########################Experiment2####################
experiment2: | experiment2Move resources experiment2Remove

experiment2Move:	
	@cp experiments/experiment2/experiment2.cpp src/
experiment2Move:	TARGET     := experiment2
experiment2Move:	SOURCES    := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
experiment2Move:	OBJECTS    := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

experiment2Remove: $(OBJECTS)
	$(CC) -o $(TARGETDIR)/experiment2 $^ $(LIB)
	@rm src/experiment2.cpp
###########################################################

###########################Experiment3####################
experiment3: | experiment3Move resources experiment3Remove

experiment3Move:	
	@cp experiments/experiment3/experiment3.cpp src/
experiment3Move:	TARGET     := experiment3
experiment3Move:	SOURCES    := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
experiment3Move:	OBJECTS    := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

experiment3Remove: $(OBJECTS)
	$(CC) -o $(TARGETDIR)/experiment3 $^ $(LIB)
	@rm src/experiment3.cpp
###########################################################

###########################Experiment3####################
experiment4: | experiment4Move resources experiment4Remove

experiment4Move:	
	@cp experiments/experiment4/experiment4.cpp src/
experiment4Move:	TARGET     := experiment4
experiment4Move:	SOURCES    := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
experiment4Move:	OBJECTS    := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

experiment4Remove: $(OBJECTS)
	$(CC) -o $(TARGETDIR)/experiment4 $^ $(LIB)
	@rm src/experiment4.cpp
###########################################################

###########################Experiment5a####################
experiment5a: | experiment5aMove resources experiment5aRemove

experiment5aMove:	
	@cp experiments/experiment5/experiment5a.cpp src/
experiment5aMove:	TARGET     := experiment5a
experiment5aMove:	SOURCES    := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
experiment5aMove:	OBJECTS    := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

experiment5aRemove: $(OBJECTS)
	$(CC) -o $(TARGETDIR)/experiment5a $^ $(LIB)
	@rm src/experiment5a.cpp
###########################################################


###########################Experiment5d####################
experiment5d: | experiment5dMove resources experiment5dRemove

experiment5dMove:	
	@cp experiments/experiment5/experiment5d.cpp src/
experiment5dMove:	TARGET     := experiment5a
experiment5dMove:	SOURCES    := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
experiment5dMove:	OBJECTS    := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

experiment5dRemove: $(OBJECTS)
	$(CC) -o $(TARGETDIR)/experiment5d $^ $(LIB)
	@rm src/experiment5d.cpp
###########################################################


###########################Experiment6####################
experiment6: | experiment6Move resources experiment6Remove

experiment6Move:	
	@cp experiments/experiment6/experiment6.cpp src/
experiment6Move:	TARGET     := experiment6
experiment6Move:	SOURCES    := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
experiment6Move:	LIB        += -llikwid
experiment6Move:	INC        += -DLIKWID_PERFMON
experiment6Move:	OBJECTS    := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

experiment6Remove: $(OBJECTS)
	$(CC) -o $(TARGETDIR)/experiment6 $^ $(LIB) 
	@rm src/experiment6.cpp
###########################################################

###########################Experiment7####################
experiment7: | experiment7Move resources experiment7Remove

experiment7Move:	
	@cp experiments/experiment7/experiment7.cpp src/
experiment7Move:	TARGET     := experiment7
experiment7Move:	SOURCES    := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
experiment7Move:	OBJECTS    := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

experiment7Remove: $(OBJECTS)
	$(CC) -o $(TARGETDIR)/experiment7 $^ $(LIB)
	@rm src/experiment7.cpp
###########################################################

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Debug
debug: CFLAGS := -fopenmp -Wall -O3 -g -ggdb -ffast-math
debug: LIB := -fopenmp -ggdb
debug: cleaner all
 

#Non-File Targets
.PHONY: all remake clean cleaner resources debug experiment1Move experiment1Remove 

