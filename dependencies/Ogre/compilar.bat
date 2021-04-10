REM Si no hay dlls compilados en Build, compilar
if not exist ../../bin/OgreMain.dll goto foo
if not exist ../../bin/OgreMain_d.dll goto foo
if not exist ../../bin/zlib.dll goto foo
goto afterfoo
:foo
rmdir /S /Q Build 
mkdir Build
cd Build
cmake ../Src
cmake --build . --config release 
cmake --build . --config debug
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
copy /Y OgreMain_d.dll "../../../../../bin/OgreMain_d.dll"
cd ../release
copy /Y OgreMain.dll "../../../../../bin/OgreMain.dll"
copy /Y zlib.dll "../../../../../bin/zlib.dll"
echo DLLSDONE