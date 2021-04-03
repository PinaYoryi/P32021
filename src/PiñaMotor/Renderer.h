#pragma once
#include "Component.h"
//#include "OgreSceneNode.h"
class Renderer : public Component {
public:
	Renderer() {
		_visible = true;
	}
	/// <summary>
	/// inicializa el componente con los valores pasador por parametro
	/// </summary>
	bool init(const std::map<std::string, std::string>& mapa) override;
	/// <summary>
	/// Hace visible a la entidad
	/// </summary>
	void setVisible(bool visible);

	/// <summary>
	/// Devuelve si es o no visible la entidad
	/// </summary>
	bool isVisible();

	/// <summary>
	/// Pone el material que se le pasa por nombre
	/// 
	/// </summary>
	void setMaterial(std::string name);
private:
	
	bool _visible;
};