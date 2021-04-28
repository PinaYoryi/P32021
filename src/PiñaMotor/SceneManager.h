#pragma once

#include "Entity.h"
#include <vector>

class SceneManager {
public:
	~SceneManager();

	/// <summary>
	/// Devuelve una instancia de la clase. La crea si no existe.
	/// </summary>
	static SceneManager* GetInstance();

	/// <summary>
	/// Inicializa la clase Input con los parametros dados si no se ha inicializado antes.
	/// Devuelve true si se inicializa por primera vez y false si ya hab�a sido inicializada.
	/// Todo: Implementar los parametros a inicializar.
	/// </summary>
	static bool Init();

	/// <summary>
	/// Añade una entidad a la lista. Si existe devuelve false, sino, true y la añade.
	/// </summary>
	/// <param name="permanent">Se mantiene entre escenas o no</param>
	bool addEntity(Entity* ent, bool permanent = false);

	/// <summary>
	/// Elimina una entidad de la lista y la destruye. Si no existe devuelve false, sino, true y la elimina.
	/// </summary>
	/// <param name="permanent">Se mantiene entre escenas o no</param>
	bool removeEntity(Entity* ent, bool permanent = false);

	/// <summary>
	/// Devuelve una lista con todas las entidades creadas.
	/// </summary>
	std::vector<Entity*> getEntities();

	bool loadScene();

	/// <summary>
	/// Elimina las entidades en las listas.
	/// </summary>
	/// <param name="all">True para eliminar tambien las permanentes, false para lo contrario</param>
	void deleteEntities(bool all = false);

protected:
	static SceneManager* _singleton;

	std::vector<Entity*> _entities;
	std::vector<Entity*> _permanentEntities;

	SceneManager() {};
};