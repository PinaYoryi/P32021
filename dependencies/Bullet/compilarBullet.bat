REM BULLET
REM Si no hay libs compilados en build, compilar
echo COMPROBATION
if not exist build/lib goto foo
goto afterfoo
:foo
echo STARTMAKE
rmdir /S /Q build 
mkdir build
cd build
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe -DBUILD_BULLET2_DEMOS=OFF -DBUILD_CLSOCKET=OFF -DBUILD_CPU_DEMOS=OFF -DBUILD_ENET=OFF -DBUILD_UNIT_TESTS=OFF -DBUILD_OPENGL3_DEMOS=OFF -DENABLE_VHACD=OFF -DINSTALL_LIBS=OFF -DUSE_GLUT=OFF -DUSE_GRAPHICAL_BENCHMARK=OFF ../src
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe --build . --config release 
..\..\Cmake\cmake-3.20.0-rc2-windows-x86_64\bin\cmake.exe --build . --config debug
cd ..
echo CMADE
:afterfoo
REM Aqui no hay que copiar nada