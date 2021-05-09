REM CEGUI
REM Si no hay libs compilados en build, compilar
echo COMPROBATION
if not exist build/dependencies/lib goto foo
goto afterfoo
:foo
echo STARTMAKE
rmdir /S /Q build
mkdir build
cd build
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe -DCEGUI_BUILD_DEVIL=TRUE^
 -DCEGUI_BUILD_CORONA=FALSE^
 -DCEGUI_BUILD_DEVIL=TRUE^
 -DCEGUI_BUILD_EFFECTS11=FALSE^
 -DCEGUI_BUILD_EXPAT=TRUE^
 -DCEGUI_BUILD_FREETYPE2=TRUE^
 -DCEGUI_BUILD_FREEIMAGE=TRUE^
 -DCEGUI_BUILD_GLEW=TRUE^
 -DCEGUI_BUILD_GLFW=TRUE^
 -DCEGUI_BUILD_GLM=TRUE^
 -DCEGUI_BUILD_LUA=TRUE^
 -DCEGUI_BUILD_MINIZIP=FALSE^
 -DCEGUI_BUILD_PCRE=TRUE^
 -DCEGUI_BUILD_TINYXML=FALSE^
 -DCEGUI_BUILD_TOLUAPP=FALSE^
 -DCEGUI_BUILD_XERCES=FALSE^
 -DCEGUI_BUILD_ZLIB=FALSE^
 -DCEGUI_BUILD_SILLY=TRUE ../src
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe --build . --config release 
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe --build . --config debug
cd ..
echo CMADE
:afterfoo
REM Aqui no hay que copiar nada


