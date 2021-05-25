REM THIS BATCH FILE HAS TO BE CALLED BY A X64 NATIVE TOOLS COMMAND PROMPT

cd dependencies

REM OGRE
echo CHECKOGRE
cd Ogre
if not exist ../../bin/Codec_STBI.dll goto ogro
if not exist ../../bin/Codec_STBI_d.dll goto ogro
if not exist ../../bin/OgreMain.dll goto ogro
if not exist ../../bin/OgreMain_d.dll goto ogro
if not exist ../../bin/OgreMeshLodGenerator.dll goto ogro
if not exist ../../bin/OgreMeshLodGenerator_d.dll goto ogro
if not exist ../../bin/OgrePaging.dll goto ogro
if not exist ../../bin/OgrePaging_d.dll goto ogro
if not exist ../../bin/OgreProperty.dll goto ogro
if not exist ../../bin/OgreProperty_d.dll goto ogro
if not exist ../../bin/OgreRTShaderSystem.dll goto ogro
if not exist ../../bin/OgreRTShaderSystem_d.dll goto ogro
if not exist ../../bin/Plugin_ParticleFX.dll goto
if not exist ../../bin/Plugin_ParticleFX_d.dll goto ogro
if not exist ../../bin/plugins.cfg goto ogro
if not exist ../../bin/RenderSystem_Direct3D11.dll goto ogro
if not exist ../../bin/RenderSystem_Direct3D11_d.dll goto ogro
if not exist ../../bin/RenderSystem_GL.dll goto ogro
if not exist ../../bin/RenderSystem_GL_d.dll goto ogro
if not exist ../../bin/resources.cfg goto ogro
if not exist ../../bin/SDL2.dll goto ogro
if not exist ../../bin/zlib.dll goto ogro
goto afterogro
:ogro
echo MAKEOGRE
rmdir /S /Q Build 
mkdir Build
cd Build
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe -DOGRE_BUILD_COMPONENT_OVERLAY=FALSE -DOGRE_BUILD_RENDERSYSTEM_D3D9=FALSE -DOGRE_BUILD_RENDERSYSTEM_D3D11=FALSE -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS=FALSE -DOGRE_BUILD_RENDERSYSTEM_GL=TRUE -DOGRE_BUILD_RENDERSYSTEM_GLES2=FALSE -DOGRE_BUILD_PLUGIN_ASSIMP=FALSE -DOGRE_BUILD_PLUGIN_BSP=FALSE -DOGRE_BUILD_PLUGIN_OCTREE=FALSE -DOGRE_BUILD_PLUGIN_DOT_SCENE=FALSE -DOGRE_BUILD_PLUGIN_PCZ=FALSE -DOGRE_BUILD_COMPONENT_TERRAIN=FALSE -DOGRE_BUILD_COMPONENT_VOLUME=FALSE -DOGRE_BUILD_COMPONENT_BITES=FALSE -DOGRE_BUILD_COMPONENT_PYTHON=FALSE -DOGRE_BUILD_COMPONENT_JAVA=FALSE -DOGRE_BUILD_COMPONENT_CSHARP=FALSE -DOGRE_INSTALL_CMAKE=FALSE -DOGRE_INSTALL_SAMPLES=FALSE -DOGRE_INSTALL_DOCS=FALSE -DOGRE_INSTALL_PDB=FALSE -DOGRE_INSTALL_VSPROPS=TRUE -DOGRE_BUILD_TOOLS=FALSE ../Src
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe --build . --config release 
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe --build . --config debug
cd ..
echo CMADEOGRE
cd ../..
IF not exist bin (
mkdir bin 
echo BINDONE
)
cd dependencies/Ogre/Build/bin/debug
copy /Y Codec_STBI_d.dll "../../../../../bin/Codec_STBI_d.dll"
copy /Y OgreMain_d.dll "../../../../../bin/OgreMain_d.dll"
copy /Y OgreMeshLodGenerator_d.dll "../../../../../bin/OgreMeshLodGenerator_d.dll"
copy /Y OgrePaging_d.dll "../../../../../bin/OgrePaging_d.dll"
copy /Y OgreProperty_d.dll "../../../../../bin/OgreProperty_d.dll"
copy /Y OgreRTShaderSystem_d.dll "../../../../../bin/OgreRTShaderSystem_d.dll"
copy /Y Plugin_ParticleFX_d.dll "../../../../../bin/Plugin_ParticleFX_d.dll"
copy /Y RenderSystem_GL_d.dll "../../../../../bin/RenderSystem_GL_d.dll"
copy /Y plugins.cfg "../../../../../bin/plugins.cfg"
copy /Y resources.cfg "../../../../../bin/resources.cfg"
cd ../release
copy /Y Codec_STBI.dll "../../../../../bin/Codec_STBI.dll"
copy /Y OgreMain.dll "../../../../../bin/OgreMain.dll"
copy /Y OgreMeshLodGenerator.dll "../../../../../bin/OgreMeshLodGenerator.dll"
copy /Y OgrePaging.dll "../../../../../bin/OgrePaging.dll"
copy /Y OgreProperty.dll "../../../../../bin/OgreProperty.dll"
copy /Y OgreRTShaderSystem.dll "../../../../../bin/OgreRTShaderSystem.dll"
copy /Y Plugin_ParticleFX.dll "../../../../../bin/Plugin_ParticleFX.dll"
copy /Y RenderSystem_GL.dll "../../../../../bin/RenderSystem_GL.dll"
copy /Y SDL2.dll "../../../../../bin/SDL2.dll"
copy /Y zlib.dll "../../../../../bin/zlib.dll"
cd ../../../
:afterogro
echo DOGRE

REM BULLET
echo CHECKBULLET
cd ../Bullet
if not exist build/lib goto bala
goto afterbala
:bala
echo MAKEBULLET
rmdir /S /Q build 
mkdir build
cd build
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe -DUSE_MSVC_RUNTIME_LIBRARY_DLL=ON -DBUILD_BULLET2_DEMOS=OFF -DBUILD_CLSOCKET=OFF -DBUILD_CPU_DEMOS=OFF -DBUILD_ENET=OFF -DBUILD_UNIT_TESTS=OFF -DENABLE_VHACD=OFF -DINSTALL_LIBS=OFF -DUSE_GLUT=OFF -DUSE_GRAPHICAL_BENCHMARK=OFF -DBUILD_OPENGL3_DEMOS=OFF ../src
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe --build . --config release 
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe --build . --config debug
cd ../
echo CMADEBULLET
:afterbala
echo DONEBULLET

REM LUA
echo CHECKLUA
cd ../Lua
if not exist ../../bin/lua54.dll goto lula
goto afterlula
:lula
cd lib
copy /Y lua54.dll "../../../bin/lua54.dll"
cd ../
:afterlula
echo DONELUA

REM FMOD
echo CHECKFMOD
cd ../FMOD
if not exist ../../bin/fmodL64.dll goto sound
goto aftersound
:sound
cd lib
copy /Y fmodL64.dll "../../../bin/fmodL64.dll"
cd ../
:aftersound
echo FMODONE

REM CEGUI
echo CHECKCEGUIDEPENDENCIES
cd ../CeguiDependencies
if not exist build/dependencies/lib goto ceguidepen
if not exist ../../bin/glew.dll goto ceguidepen
if not exist ../../bin/glew_d.dll goto ceguidepen
if not exist ../../bin/glfw.dll goto ceguidepen
if not exist ../../bin/glfw_d.dll goto ceguidepen
if not exist ../../bin/jpeg.dll goto ceguidepen
if not exist ../../bin/jpeg_d.dll goto ceguidepen
if not exist ../../bin/libexpat.dll goto ceguidepen
if not exist ../../bin/libexpat_d.dll goto ceguidepen
if not exist ../../bin/libpng.dll goto ceguidepen
if not exist ../../bin/libpng_d.dll goto ceguidepen
if not exist ../../bin/pcre.dll goto ceguidepen
if not exist ../../bin/pcre_d.dll goto ceguidepen
if not exist ../../bin/SILLY.dll goto ceguidepen
if not exist ../../bin/SILLY_d.dll goto ceguidepen
goto afterceguidepen
:ceguidepen
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
cd dependencies/bin
copy /Y freetype.dll "../../../../../bin/freetype.dll"
copy /Y freetype_d.dll "../../../../../bin/freetype_d.dll"
copy /Y glew.dll "../../../../../bin/glew.dll"
copy /Y glew_d.dll "../../../../../bin/glew_d.dll"
copy /Y glfw.dll "../../../../../bin/glfw.dll"
copy /Y glfw_d.dll "../../../../../bin/glfw_d.dll"
copy /Y jpeg.dll "../../../../../bin/jpeg.dll"
copy /Y jpeg_d.dll "../../../../../bin/jpeg_d.dll"
copy /Y libexpat.dll "../../../../../bin/libexpat.dll"
copy /Y libexpat_d.dll "../../../../../bin/libexpat_d.dll"
copy /Y libpng.dll "../../../../../bin/libpng.dll"
copy /Y libpng_d.dll "../../../../../bin/libpng_d.dll"
copy /Y pcre.dll "../../../../../bin/pcre.dll"
copy /Y pcre_d.dll "../../../../../bin/pcre_d.dll"
copy /Y SILLY.dll "../../../../../bin/SILLY.dll"
copy /Y SILLY_d.dll "../../../../../bin/SILLY_d.dll"
cd ../../..
:afterceguidepen

echo CHECKCEGUI
cd ../Cegui/src
if not exist build/lib goto cegui
if not exist ../../../bin/CEGUIBase-0.dll goto cegui
if not exist ../../../bin/CEGUIBase-0_d.dll goto cegui
if not exist ../../../bin/CEGUIOgreRenderer-0.dll goto cegui
if not exist ../../../bin/CEGUIOgreRenderer-0_d.dll goto cegui
if not exist ../../../bin/CEGUIExpatParser_d.dll goto cegui
if not exist ../../../bin/CEGUIExpatParser.dll goto cegui
if not exist ../../../bin/CEGUICoreWindowRendererSet_d.dll goto cegui
if not exist ../../../bin/CEGUICoreWindowRendererSet.dll goto cegui
goto aftercegui
:cegui
set CeguiBuiltDependencies="%~dp0dependencies\CeguiDependencies\build\dependencies"
set OgreDependencies="%~dp0dependencies\Ogre\Build"
set OgreSrc="%~dp0dependencies\Ogre\Src"
echo STARTMAKE
rmdir /S /Q build 
mkdir build
cd build
..\..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe^
 -DCEGUI_SAMPLES_ENABLED=OFF^
 -DCEGUI_SAMPLES_ENABLE_COMMON_DIALOGUES_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_DEMO6=OFF^
 -DCEGUI_SAMPLES_ENABLE_DRAGDROP_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_EDITBOX_VALIDATION_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_EFFECTS_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_FONT_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_GAMEMENU_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_HELLO_WORLD_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_HUD_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_INVENTORY_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_LOOKNFEELOVERVIEW_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_MINESWEEPER_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_SCROLLABLEPANE_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_TABCONTROL_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_TEXT_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_TREE_DEMO=OFF^
 -DCEGUI_SAMPLES_ENABLE_WIDGET_DEMO=OFF^
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
cd ..

cd build/bin
copy /Y CEGUIBase-0.dll "../../../../../bin/CEGUIBase-0.dll"
copy /Y CEGUIBase-0_d.dll "../../../../../bin/CEGUIBase-0_d.dll"
copy /Y CEGUIOgreRenderer-0.dll "../../../../../bin/CEGUIOgreRenderer-0.dll"
copy /Y CEGUIOgreRenderer-0_d.dll "../../../../../bin/CEGUIOgreRenderer-0_d.dll"
copy /Y CEGUIExpatParser_d.dll "../../../../../bin/CEGUIExpatParser_d.dll"
copy /Y CEGUIExpatParser.dll "../../../../../bin/CEGUIExpatParser.dll"
copy /Y CEGUICoreWindowRendererSet_d.dll "../../../../../bin/CEGUICoreWindowRendererSet_d.dll"
copy /Y CEGUICoreWindowRendererSet.dll "../../../../../bin/CEGUICoreWindowRendererSet.dll"
cd ../..

:aftercegui
cd ..
echo CEGUIDONE

cd ../..
echo BUILD PROJECT
msbuild PinaMotor.sln -p:Configuration=Debug
msbuild PinaMotor.sln -p:Configuration=Release
echo BUILDING DONE