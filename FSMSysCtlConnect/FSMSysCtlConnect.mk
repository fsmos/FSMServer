##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=FSMSysCtlConnect
ConfigurationName      :=Debug
WorkspacePath          :=/home/gusenkovs/FSMCoreFile
ProjectPath            :=/home/gusenkovs/FSMCoreFile/FSMSysCtlConnect
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=gusenkovs
Date                   :=23/06/16
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
OutputFile             :=$(IntermediateDirectory)/libFSMSysCtl.so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="FSMSysCtlConnect.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)/home/gusenkovs/FSMCoreFile/FSMHeader/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g -fPIC $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/FSMSysCtl.c$(ObjectSuffix) 



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
	@$(MakeDirCommand) "/home/gusenkovs/FSMCoreFile/.build-debug"
	@echo rebuilt > "/home/gusenkovs/FSMCoreFile/.build-debug/FSMSysCtlConnect"

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/FSMSysCtl.c$(ObjectSuffix): FSMSysCtl.c $(IntermediateDirectory)/FSMSysCtl.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/FSMSysCtlConnect/FSMSysCtl.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FSMSysCtl.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FSMSysCtl.c$(DependSuffix): FSMSysCtl.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FSMSysCtl.c$(ObjectSuffix) -MF$(IntermediateDirectory)/FSMSysCtl.c$(DependSuffix) -MM "FSMSysCtl.c"

$(IntermediateDirectory)/FSMSysCtl.c$(PreprocessSuffix): FSMSysCtl.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FSMSysCtl.c$(PreprocessSuffix) "FSMSysCtl.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


