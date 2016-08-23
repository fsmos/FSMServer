##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=libfsmpo08
ConfigurationName      :=Release
WorkspacePath          :=/home/gusenkovs/FSMCoreFile
ProjectPath            :=/home/gusenkovs/FSMCoreFile/libfsmpo8
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=gusenkovs
Date                   :=03/08/16
CodeLitePath           :=/home/gusenkovs/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="libfsmpo08.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O2
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)fsmctl 
ArLibs                 :=  "libfsmctl" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=   $(Preprocessors)
CFLAGS   :=  -fPIC $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/libfsmpo08.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)
	@$(MakeDirCommand) "/home/gusenkovs/FSMCoreFile/.build-release"
	@echo rebuilt > "/home/gusenkovs/FSMCoreFile/.build-release/libfsmpo08"

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/libfsmpo08.c$(ObjectSuffix): libfsmpo08.c $(IntermediateDirectory)/libfsmpo08.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/libfsmpo8/libfsmpo08.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/libfsmpo08.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/libfsmpo08.c$(DependSuffix): libfsmpo08.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/libfsmpo08.c$(ObjectSuffix) -MF$(IntermediateDirectory)/libfsmpo08.c$(DependSuffix) -MM "libfsmpo08.c"

$(IntermediateDirectory)/libfsmpo08.c$(PreprocessSuffix): libfsmpo08.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/libfsmpo08.c$(PreprocessSuffix) "libfsmpo08.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


