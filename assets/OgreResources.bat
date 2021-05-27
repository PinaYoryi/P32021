cd ../dependencies/Ogre/Build/bin/debug
copy /Y resources.cfg "../../../../../bin/resources.cfg"
cd ../../../../../assets
echo [General] >> ../bin/resources.cfg
echo FileSystem=%CD%/resources >> ../bin/resources.cfg
for /r %CD% %%f in (*.zip) do echo Zip=%%~pnxf >> ../bin/resources.cfg