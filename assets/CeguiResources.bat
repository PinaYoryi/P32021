REM Este bat no se llama automaticamente
REM Este bat sirve para poder debuggear el motor con los resources de cegui

cd ..
echo [animations] >> bin/resources.cfg
echo FileSystem=%CD%/bin/resources/gui/animations >> bin/resources.cfg
echo [fonts] >> bin/resources.cfg
echo FileSystem=%CD%/bin/resources/gui/fonts >> bin/resources.cfg
echo [imagesets] >> bin/resources.cfg
echo FileSystem=%CD%/bin/resources/gui/imagesets >> bin/resources.cfg
echo [layouts] >> bin/resources.cfg
echo FileSystem=%CD%/bin/resources/gui/layouts >> bin/resources.cfg
echo [looknfeel] >> bin/resources.cfg
echo FileSystem=%CD%/bin/resources/gui/looknfeel >> bin/resources.cfg
echo [luaScripts] >> bin/resources.cfg
echo FileSystem=%CD%/bin/resources/gui/lua_scripts >> bin/resources.cfg
echo [schemes] >> bin/resources.cfg
echo FileSystem=%CD%/bin/resources/gui/schemes >> bin/resources.cfg
echo [xmlSchemas] >> bin/resources.cfg
echo FileSystem=%CD%/bin/resources/gui/xml_schemas >> bin/resources.cfg
cd assets/