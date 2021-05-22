#include "SkyBox.h"
#include "OgreMotor.h"

SkyBox::SkyBox() {

}

SkyBox::~SkyBox()
{
	
}

bool SkyBox::init(const std::map<std::string, std::string>& mapa) {
	if (mapa.find("enable") == mapa.end() || mapa.find("planenormal") == mapa.end() || mapa.find("planepos") == mapa.end() || mapa.find("materialname") == mapa.end() ||
		mapa.find("scale") == mapa.end() || mapa.find("tiling") == mapa.end() || mapa.find("drawfirst") == mapa.end() || mapa.find("bow") == mapa.end() 
		|| mapa.find("xsegments") == mapa.end() || mapa.find("ysegments") == mapa.end()) return false;
	
	bool enable = true;
	if (mapa.at("enable") == "false") enable = false;
	
	Ogre::Plane plane;
	std::string splane = mapa.at("planepos");
	plane.d = std::stof(splane);
	splane = mapa.at("planenormal");
	if (splane == "Z") plane.normal = Ogre::Vector3::UNIT_Z;
	else if (splane == "-Z") plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Z;
	else if (splane == "Y") plane.normal = Ogre::Vector3::UNIT_Y;
	else if (splane == "-Y") plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
	else if (splane == "X") plane.normal = Ogre::Vector3::UNIT_X;
	else if (splane == "-X") plane.normal = Ogre::Vector3::NEGATIVE_UNIT_X;
	else plane.normal = Ogre::Vector3::UNIT_Z;	

	std::string materialname = mapa.at("materialname");

	float scale= std::stof(mapa.at("scale"));

	float tiling = std::stof(mapa.at("tiling"));

	bool drawfirst = true;
	if(mapa.at("drawfirst") == "false") drawfirst=false;

	float bow = std::stof(mapa.at("bow"));
	int xsegments = std::stoi(mapa.at("xsegments"));
	int ysegments = std::stoi(mapa.at("ysegments"));

	OgreMotor::GetInstance()->getSceneManager()->setSkyPlane(enable, plane, materialname, scale, tiling, drawfirst, bow, xsegments, ysegments);

	return true;
}

