REM Si no hay dlls compilados en Build, compilar
if not exist ../../bin/Codec_STBI.dll goto foo
if not exist ../../bin/Codec_STBI_d.dll goto foo
if not exist ../../bin/OgreMain.dll goto foo
if not exist ../../bin/OgreMain_d.dll goto foo
if not exist ../../bin/OgreMeshLodGenerator.dll goto foo
if not exist ../../bin/OgreMeshLodGenerator_d.dll goto foo
if not exist ../../bin/OgreOverlay.dll goto foo
if not exist ../../bin/OgreOverlay_d.dll goto foo
if not exist ../../bin/OgrePaging.dll goto foo
if not exist ../../bin/OgrePaging_d.dll goto foo
if not exist ../../bin/OgreProperty.dll goto foo
if not exist ../../bin/OgreProperty_d.dll goto foo
if not exist ../../bin/Plugin_ParticleFX.dll goto
if not exist ../../bin/Plugin_ParticleFX_d.dll goto foo
if not exist ../../bin/plugins.cfg goto foo
if not exist ../../bin/RenderSystem_Direct3D11.dll goto foo
if not exist ../../bin/RenderSystem_Direct3D11_d.dll goto foo
if not exist ../../bin/resources.cfg goto foo
if not exist ../../bin/SDL2.dll goto foo
if not exist ../../bin/zlib.dll goto foo
goto afterfoo
:foo
echo STARTMAKE
rmdir /S /Q Build 
mkdir Build
cd Build
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe -DOGRE_BUILD_RENDERSYSTEM_D3D9=FALSE -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS=FALSE -DOGRE_BUILD_RENDERSYSTEM_GL=FALSE -DOGRE_BUILD_RENDERSYSTEM_GLES2=FALSE -DOGRE_BUILD_PLUGIN_ASSIMP=FALSE -DOGRE_BUILD_PLUGIN_BSP=FALSE -DOGRE_BUILD_PLUGIN_OCTREE=FALSE -DOGRE_BUILD_PLUGIN_DOT_SCENE=FALSE -DOGRE_BUILD_PLUGIN_PCZ=FALSE -DOGRE_BUILD_COMPONENT_TERRAIN=FALSE -DOGRE_BUILD_COMPONENT_VOLUME=FALSE -DOGRE_BUILD_COMPONENT_BITES=FALSE -DOGRE_BUILD_COMPONENT_PYTHON=FALSE -DOGRE_BUILD_COMPONENT_JAVA=FALSE -DOGRE_BUILD_COMPONENT_CSHARP=FALSE -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM=FALSE -DOGRE_BUILD_RTSHADERSYSTEM_SHADERS=FALSE -DOGRE_INSTALL_CMAKE=FALSE -DOGRE_INSTALL_SAMPLES=FALSE -DOGRE_INSTALL_DOCS=FALSE -DOGRE_INSTALL_PDB=FALSE -DOGRE_INSTALL_VSPROPS=TRUE -DOGRE_BUILD_TOOLS=FALSE ../Src
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe --build . --config release 
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe --build . --config debug
cd ..
echo CMADE
:afterfoo
REM Hacer bin si no existe ya
cd ../..
IF not exist bin (
mkdir bin 
echo BINDONE
)
REM Copiar los dlls pertinentes
cd dependencies/Ogre/Build/bin/debug
copy /Y Codec_STBI_d.dll "../../../../../bin/Codec_STBI_d.dll"
copy /Y OgreMain_d.dll "../../../../../bin/OgreMain_d.dll"
copy /Y OgreMeshLodGenerator_d.dll "../../../../../bin/OgreMeshLodGenerator_d.dll"
copy /Y OgreOverlay_d.dll "../../../../../bin/OgreOverlay_d.dll"
copy /Y OgrePaging_d.dll "../../../../../bin/OgrePaging_d.dll"
copy /Y OgreProperty_d.dll "../../../../../bin/OgreProperty_d.dll"
copy /Y Plugin_ParticleFX_d.dll "../../../../../bin/Plugin_ParticleFX_d.dll"
copy /Y RenderSystem_Direct3D11_d.dll "../../../../../bin/RenderSystem_Direct3D11_d.dll"
copy /Y plugins.cfg "../../../../../bin/plugins.cfg"
copy /Y resources.cfg "../../../../../bin/resources.cfg"
cd ../release
copy /Y Codec_STBI.dll "../../../../../bin/Codec_STBI.dll"
copy /Y OgreMain.dll "../../../../../bin/OgreMain.dll"
copy /Y OgreMeshLodGenerator.dll "../../../../../bin/OgreMeshLodGenerator.dll"
copy /Y OgreOverlay.dll "../../../../../bin/OgreOverlay.dll"
copy /Y OgrePaging.dll "../../../../../bin/OgrePaging.dll"
copy /Y OgreProperty.dll "../../../../../bin/OgreProperty.dll"
copy /Y Plugin_ParticleFX.dll "../../../../../bin/Plugin_ParticleFX.dll"
copy /Y RenderSystem_Direct3D11.dll "../../../../../bin/RenderSystem_Direct3D11.dll"
copy /Y SDL2.dll "../../../../../bin/SDL2.dll"
copy /Y zlib.dll "../../../../../bin/zlib.dll"
echo COPYDONE