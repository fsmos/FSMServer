##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=FSMConfig_Server
ConfigurationName      :=Release
WorkspacePath          :=/home/gusenkovs/FSMCoreFile
ProjectPath            :=/home/gusenkovs/FSMCoreFile/FSMConfig_Server
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=gusenkovs
Date                   :=28/08/18
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
OutputFile             :=
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="FSMConfig_Server.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -L/usr/local/lib -lprotobuf -pthread -lgrpc++ -lgrpc -lfsmcck
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)cpp 
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
CXXFLAGS :=   -std=c++11  -pthread -I/usr/local/include -O2 -Wall  $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/CCKConfigServiceImpl.cpp$(ObjectSuffix) $(IntermediateDirectory)/cpp_fsm_cckconfig_clientinfo.pb.cc$(ObjectSuffix) $(IntermediateDirectory)/cpp_fsm_cckconfig_MN.pb.cc$(ObjectSuffix) $(IntermediateDirectory)/cpp_fsm_cckconfig_MN401.pb.cc$(ObjectSuffix) $(IntermediateDirectory)/cpp_fsm_cckconfig_PO.pb.cc$(ObjectSuffix) $(IntermediateDirectory)/cpp_fsm_cckconfig_service.grpc.pb.cc$(ObjectSuffix) $(IntermediateDirectory)/cpp_fsm_cckconfig_service.pb.cc$(ObjectSuffix) $(IntermediateDirectory)/cpp_fsm_cckconfig_VirtPO.pb.cc$(ObjectSuffix) $(IntermediateDirectory)/cpp_nanopb.pb.cc$(ObjectSuffix) \
	



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
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/FSMConfig_Server/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/CCKConfigServiceImpl.cpp$(ObjectSuffix): CCKConfigServiceImpl.cpp $(IntermediateDirectory)/CCKConfigServiceImpl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/FSMConfig_Server/CCKConfigServiceImpl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CCKConfigServiceImpl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CCKConfigServiceImpl.cpp$(DependSuffix): CCKConfigServiceImpl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CCKConfigServiceImpl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CCKConfigServiceImpl.cpp$(DependSuffix) -MM CCKConfigServiceImpl.cpp

$(IntermediateDirectory)/CCKConfigServiceImpl.cpp$(PreprocessSuffix): CCKConfigServiceImpl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CCKConfigServiceImpl.cpp$(PreprocessSuffix) CCKConfigServiceImpl.cpp

$(IntermediateDirectory)/cpp_fsm_cckconfig_clientinfo.pb.cc$(ObjectSuffix): cpp/fsm_cckconfig_clientinfo.pb.cc $(IntermediateDirectory)/cpp_fsm_cckconfig_clientinfo.pb.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/FSMConfig_Server/cpp/fsm_cckconfig_clientinfo.pb.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpp_fsm_cckconfig_clientinfo.pb.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpp_fsm_cckconfig_clientinfo.pb.cc$(DependSuffix): cpp/fsm_cckconfig_clientinfo.pb.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpp_fsm_cckconfig_clientinfo.pb.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/cpp_fsm_cckconfig_clientinfo.pb.cc$(DependSuffix) -MM cpp/fsm_cckconfig_clientinfo.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_clientinfo.pb.cc$(PreprocessSuffix): cpp/fsm_cckconfig_clientinfo.pb.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpp_fsm_cckconfig_clientinfo.pb.cc$(PreprocessSuffix) cpp/fsm_cckconfig_clientinfo.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_MN.pb.cc$(ObjectSuffix): cpp/fsm_cckconfig_MN.pb.cc $(IntermediateDirectory)/cpp_fsm_cckconfig_MN.pb.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/FSMConfig_Server/cpp/fsm_cckconfig_MN.pb.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpp_fsm_cckconfig_MN.pb.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpp_fsm_cckconfig_MN.pb.cc$(DependSuffix): cpp/fsm_cckconfig_MN.pb.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpp_fsm_cckconfig_MN.pb.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/cpp_fsm_cckconfig_MN.pb.cc$(DependSuffix) -MM cpp/fsm_cckconfig_MN.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_MN.pb.cc$(PreprocessSuffix): cpp/fsm_cckconfig_MN.pb.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpp_fsm_cckconfig_MN.pb.cc$(PreprocessSuffix) cpp/fsm_cckconfig_MN.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_MN401.pb.cc$(ObjectSuffix): cpp/fsm_cckconfig_MN401.pb.cc $(IntermediateDirectory)/cpp_fsm_cckconfig_MN401.pb.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/FSMConfig_Server/cpp/fsm_cckconfig_MN401.pb.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpp_fsm_cckconfig_MN401.pb.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpp_fsm_cckconfig_MN401.pb.cc$(DependSuffix): cpp/fsm_cckconfig_MN401.pb.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpp_fsm_cckconfig_MN401.pb.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/cpp_fsm_cckconfig_MN401.pb.cc$(DependSuffix) -MM cpp/fsm_cckconfig_MN401.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_MN401.pb.cc$(PreprocessSuffix): cpp/fsm_cckconfig_MN401.pb.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpp_fsm_cckconfig_MN401.pb.cc$(PreprocessSuffix) cpp/fsm_cckconfig_MN401.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_PO.pb.cc$(ObjectSuffix): cpp/fsm_cckconfig_PO.pb.cc $(IntermediateDirectory)/cpp_fsm_cckconfig_PO.pb.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/FSMConfig_Server/cpp/fsm_cckconfig_PO.pb.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpp_fsm_cckconfig_PO.pb.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpp_fsm_cckconfig_PO.pb.cc$(DependSuffix): cpp/fsm_cckconfig_PO.pb.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpp_fsm_cckconfig_PO.pb.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/cpp_fsm_cckconfig_PO.pb.cc$(DependSuffix) -MM cpp/fsm_cckconfig_PO.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_PO.pb.cc$(PreprocessSuffix): cpp/fsm_cckconfig_PO.pb.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpp_fsm_cckconfig_PO.pb.cc$(PreprocessSuffix) cpp/fsm_cckconfig_PO.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_service.grpc.pb.cc$(ObjectSuffix): cpp/fsm_cckconfig_service.grpc.pb.cc $(IntermediateDirectory)/cpp_fsm_cckconfig_service.grpc.pb.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/FSMConfig_Server/cpp/fsm_cckconfig_service.grpc.pb.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpp_fsm_cckconfig_service.grpc.pb.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpp_fsm_cckconfig_service.grpc.pb.cc$(DependSuffix): cpp/fsm_cckconfig_service.grpc.pb.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpp_fsm_cckconfig_service.grpc.pb.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/cpp_fsm_cckconfig_service.grpc.pb.cc$(DependSuffix) -MM cpp/fsm_cckconfig_service.grpc.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_service.grpc.pb.cc$(PreprocessSuffix): cpp/fsm_cckconfig_service.grpc.pb.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpp_fsm_cckconfig_service.grpc.pb.cc$(PreprocessSuffix) cpp/fsm_cckconfig_service.grpc.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_service.pb.cc$(ObjectSuffix): cpp/fsm_cckconfig_service.pb.cc $(IntermediateDirectory)/cpp_fsm_cckconfig_service.pb.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/FSMConfig_Server/cpp/fsm_cckconfig_service.pb.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpp_fsm_cckconfig_service.pb.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpp_fsm_cckconfig_service.pb.cc$(DependSuffix): cpp/fsm_cckconfig_service.pb.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpp_fsm_cckconfig_service.pb.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/cpp_fsm_cckconfig_service.pb.cc$(DependSuffix) -MM cpp/fsm_cckconfig_service.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_service.pb.cc$(PreprocessSuffix): cpp/fsm_cckconfig_service.pb.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpp_fsm_cckconfig_service.pb.cc$(PreprocessSuffix) cpp/fsm_cckconfig_service.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_VirtPO.pb.cc$(ObjectSuffix): cpp/fsm_cckconfig_VirtPO.pb.cc $(IntermediateDirectory)/cpp_fsm_cckconfig_VirtPO.pb.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/FSMConfig_Server/cpp/fsm_cckconfig_VirtPO.pb.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpp_fsm_cckconfig_VirtPO.pb.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpp_fsm_cckconfig_VirtPO.pb.cc$(DependSuffix): cpp/fsm_cckconfig_VirtPO.pb.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpp_fsm_cckconfig_VirtPO.pb.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/cpp_fsm_cckconfig_VirtPO.pb.cc$(DependSuffix) -MM cpp/fsm_cckconfig_VirtPO.pb.cc

$(IntermediateDirectory)/cpp_fsm_cckconfig_VirtPO.pb.cc$(PreprocessSuffix): cpp/fsm_cckconfig_VirtPO.pb.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpp_fsm_cckconfig_VirtPO.pb.cc$(PreprocessSuffix) cpp/fsm_cckconfig_VirtPO.pb.cc

$(IntermediateDirectory)/cpp_nanopb.pb.cc$(ObjectSuffix): cpp/nanopb.pb.cc $(IntermediateDirectory)/cpp_nanopb.pb.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/gusenkovs/FSMCoreFile/FSMConfig_Server/cpp/nanopb.pb.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpp_nanopb.pb.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpp_nanopb.pb.cc$(DependSuffix): cpp/nanopb.pb.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpp_nanopb.pb.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/cpp_nanopb.pb.cc$(DependSuffix) -MM cpp/nanopb.pb.cc

$(IntermediateDirectory)/cpp_nanopb.pb.cc$(PreprocessSuffix): cpp/nanopb.pb.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpp_nanopb.pb.cc$(PreprocessSuffix) cpp/nanopb.pb.cc


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


