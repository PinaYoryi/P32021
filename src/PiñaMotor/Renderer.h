#pragma once
#include "Component.h"
#include "OgreSceneNode.h"
static int name = 0;

class Renderer : public Component {
public:
	Renderer() {
		_visible = true;
	}
	/// <summary>
	/// Inicializa el componente con los valores pasador por parametro
	/// utiliza setMesh para poner su mesh y setMaterial para poner su material
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
	/// el nombre tiene que estar creado en un .material del proyecto   
	/// no hace falta poner .material al final del nombre   
	/// </summary>
	void setMaterial(std::string name);


	/// <summary>
	/// Devuelve el nombre del material que esta usando   
	/// </summary>
	const std::string getMaterialName();

	/// <summary>
	/// Devuelve el nombre de la mesh que esta usando   
	/// </summary>
	const std::string getMeshName();

	/// <summary>
	/// Devuelve una referencia de la mesh que esta usando   
	/// </summary>
	const Ogre::MeshPtr getMesh();

	/// <summary>
	/// Devuelve un puntero del nodo de ogre 
	/// </summary>
	Ogre::SceneNode* getNode() const;

	/// <summary>
	 /// Devuelve un puntero de la entidad de de ogre 
	 /// </summary>
	Ogre::Entity* getOgreEntity() {
		return _ogreEntity;
	}
	
protected:
	/// <summary>
	/// Se encarga de renderizar   
	/// </summary>
	void render() override;

	bool _visible;
	std::string _material="";
	std::string _meshName="";
	Ogre::SceneNode* _ogreNode=nullptr;//nodo de ogre 
	Ogre::Entity* _ogreEntity=nullptr;//entidad de ogre

	/// <summary>
	/// Crea una nueva entidad con la mesh que se le pasa por parametro
	/// el nombre tiene que ser un .mesh creado previamente  
	/// es necesario poner .mesh al final del nombre
	/// </summary>
	void setMesh(std::string name);

	/// <summary>
	/// Crea una nueva entidad con este mesh
	/// </summary>
	void  setMesh(Ogre::MeshPtr mesh);

};