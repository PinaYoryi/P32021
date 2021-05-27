cd ../dependencies/Ogre/Build/bin/debug
copy /Y resources.cfg "../../../../../bin/resources.cfg"
cd ../../../../../bin/resources
echo [General] >> ../resources.cfg
echo FileSystem=%CD% >> ../resources.cfg
for /r %CD% %%f in (*.zip) do echo Zip=%%~pnxf >> ../resources.cfg