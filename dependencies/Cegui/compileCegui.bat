REM CEGUI
REM Si no hay libs compilados en build, compilar
echo COMPROBATION
cd src
if not exist build/lib goto foo
goto afterfoo
:foo
set CeguiBuiltDependencies="%~dp0..\CeguiDependencies\build\dependencies"
set OgreDependencies="%~dp0..\Ogre\Build"
set OgreSrc="%~dp0..\Ogre\Src"
echo STARTMAKE
rmdir /S /Q build 
mkdir build
cd build
..\..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe^
 -DCEGUI_BUILD_RENDERER_DIRECT3D10:BOOL=OFF^
 -DCEGUI_BUILD_RENDERER_DIRECT3D11:BOOL=OFF^
 -DCEGUI_BUILD_RENDERER_DIRECT3D9:BOOL=OFF^
 -DCEGUI_BUILD_RENDERER_DIRECTFB:BOOL=OFF^
 -DCEGUI_BUILD_RENDERER_IRRLICHT:BOOL=OFF^
 -DCEGUI_BUILD_RENDERER_NULL:BOOL=OFF^
 -DCEGUI_BUILD_RENDERER_OGRE:BOOL=ON^
 -DCEGUI_BUILD_RENDERER_OPENGL:BOOL=OFF^
 -DCEGUI_BUILD_RENDERER_OPENGL3:BOOL=OFF^
 -DCEGUI_BUILD_RENDERER_OPENGLES:BOOL=OFF^
 -DCMAKE_PREFIX_PATH:PATH=%CeguiBuiltDependencies%^
 -DOGRE_H_BUILD_SETTINGS_PATH:PATH=%OgreDependencies%/include^
 -DOGRE_H_PATH:PATH=%OgreSrc%/OgreMain/include^
 -DOGRE_LIB:FILEPATH=%OgreDependencies%/lib/Release/OgreMain.lib^
 -DOGRE_LIB_DBG:FILEPATH=%OgreDependencies%/lib/Debug/OgreMain_d.lib ..

cd ../replacements
copy /Y Config.h "../build/cegui/include/CEGUI/Config.h"

cd ../build
..\..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe --build . --config release 
..\..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe --build . --config debug

cd ../replacements
copy /Y Texture.cpp "../cegui/src/RendererModules/Ogre/Texture.cpp"
cd ..\..
echo CMADE
:afterfoo
REM Aqui no hay que copiar nada


