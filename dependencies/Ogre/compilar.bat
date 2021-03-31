rmdir /S /Q Build
mkdir Build
cd Build
cmake ../Src
cmake --build . --config release
cmake --build . --config debug
cd bin/debug
copy /Y OgreMain_d.dll "../../../../../bin/OgreMain_d.dll"
cd ../release
copy /Y OgreMain.dll "../../../../../bin/OgreMain.dll"
copy /Y zlib.dll "../../../../../bin/zlib.dll"