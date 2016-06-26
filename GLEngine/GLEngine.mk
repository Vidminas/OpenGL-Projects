##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=GLEngine
ConfigurationName      :=Debug
WorkspacePath          := "/Users/vidminas/GitHub/GLEngine"
ProjectPath            := "/Users/vidminas/GitHub/GLEngine"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Vidminas
Date                   :=03/04/2016
CodeLitePath           :="/Users/vidminas/Library/Application Support/codelite"
LinkerName             :=/usr/bin/clang++
SharedObjectLinkerName :=/usr/bin/clang++ -dynamiclib -fPIC
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="GLEngine.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lglfw3d -lGLEWd -framework OpenGL -framework Cocoa -framework Carbon -framework CoreVideo -framework IOKit
IncludePath            := $(IncludeSwitch)/usr/local/include/  $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                :=$(LibraryPathSwitch)/usr/local/lib/  $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/clang++
CC       := /usr/bin/clang
CXXFLAGS :=  -g -O0 -Wall -std=c++0x $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/Applications/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/shaderFactory.cpp$(ObjectSuffix) $(IntermediateDirectory)/shader.cpp$(ObjectSuffix) $(IntermediateDirectory)/GLEngine.cpp$(ObjectSuffix) $(IntermediateDirectory)/geometry2D.cpp$(ObjectSuffix) 



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
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/vidminas/GitHub/GLEngine/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/shaderFactory.cpp$(ObjectSuffix): shaderFactory.cpp $(IntermediateDirectory)/shaderFactory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/vidminas/GitHub/GLEngine/shaderFactory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/shaderFactory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shaderFactory.cpp$(DependSuffix): shaderFactory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shaderFactory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/shaderFactory.cpp$(DependSuffix) -MM "shaderFactory.cpp"

$(IntermediateDirectory)/shaderFactory.cpp$(PreprocessSuffix): shaderFactory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shaderFactory.cpp$(PreprocessSuffix) "shaderFactory.cpp"

$(IntermediateDirectory)/shader.cpp$(ObjectSuffix): shader.cpp $(IntermediateDirectory)/shader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/vidminas/GitHub/GLEngine/shader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/shader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shader.cpp$(DependSuffix): shader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/shader.cpp$(DependSuffix) -MM "shader.cpp"

$(IntermediateDirectory)/shader.cpp$(PreprocessSuffix): shader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shader.cpp$(PreprocessSuffix) "shader.cpp"

$(IntermediateDirectory)/GLEngine.cpp$(ObjectSuffix): GLEngine.cpp $(IntermediateDirectory)/GLEngine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/vidminas/GitHub/GLEngine/GLEngine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GLEngine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GLEngine.cpp$(DependSuffix): GLEngine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GLEngine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GLEngine.cpp$(DependSuffix) -MM "GLEngine.cpp"

$(IntermediateDirectory)/GLEngine.cpp$(PreprocessSuffix): GLEngine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GLEngine.cpp$(PreprocessSuffix) "GLEngine.cpp"

$(IntermediateDirectory)/geometry2D.cpp$(ObjectSuffix): geometry2D.cpp $(IntermediateDirectory)/geometry2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/vidminas/GitHub/GLEngine/geometry2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/geometry2D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/geometry2D.cpp$(DependSuffix): geometry2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/geometry2D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/geometry2D.cpp$(DependSuffix) -MM "geometry2D.cpp"

$(IntermediateDirectory)/geometry2D.cpp$(PreprocessSuffix): geometry2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/geometry2D.cpp$(PreprocessSuffix) "geometry2D.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


