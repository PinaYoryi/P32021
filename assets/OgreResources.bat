cd ../dependencies/Ogre/Build/bin/debug
copy /Y resources.cfg "../../../../../bin/resources.cfg"
cd ../../../../../assets/OgreResources
echo [General] >> ../../bin/resources.cfg
echo FileSystem=../assets/OgreResources >> ../../bin/resources.cfg
for %%f in (*.zip) do echo Zip=../assets/OgreResources/%%~nxf >> ../../bin/resources.cfg