cd ../dependencies/Ogre/Build/bin/debug
copy /Y resources.cfg "../../../../../bin/resources.cfg"
cd ../../../../../assets/models
echo [General] >> ../../bin/resources.cfg
echo FileSystem=../assets/models >> ../../bin/resources.cfg
for %%f in (*.zip) do echo Zip=../assets/models/%%~nxf >> ../../bin/resources.cfg