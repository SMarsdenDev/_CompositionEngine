# Macros ========================================

# Targets ========================================

build : 
	msbuild -m 
	
run :
	$(MAKE) build 
	x64\Debug\_CompositionEngine.exe

stage :
	-rmdir /s /q .vs
	-rmdir /q /s x64
	git add .
	git status