##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=libfsmgpio
ConfigurationName      :=Release
WorkspacePath          :=/home/gusenkovs/FSMCoreFile
ProjectPath            :=/home/gusenkovs/FSMCoreFile/libfsmgpiio
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=gusenkovs
Date                   :=28/07/16
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
ObjectsFileList        :="libfsmgpio.txt"
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
Objects0=$(IntermediateDirectory)/fsmgpioctrl.c$(ObjectSuffix) 



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
	@echo rebuilt > "/home/gusenkovs/FSMCoreFile/.build-release/libfsmgpio"

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/fsmgpioctrl.c$(ObjectSuffix): fsmgpioctrl.c $(IntermediateDirectory)/fsmgpioctrl.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/libfsmgpiio/fsmgpioctrl.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/fsmgpioctrl.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fsmgpioctrl.c$(DependSuffix): fsmgpioctrl.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/fsmgpioctrl.c$(ObjectSuffix) -MF$(IntermediateDirectory)/fsmgpioctrl.c$(DependSuffix) -MM "fsmgpioctrl.c"

$(IntermediateDirectory)/fsmgpioctrl.c$(PreprocessSuffix): fsmgpioctrl.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/fsmgpioctrl.c$(PreprocessSuffix) "fsmgpioctrl.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


