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
	/// </summary>
	static bool Init();

	/// <summary>
	/// Añade una entidad a la lista. Si existe devuelve false, sino, true y la añade.
	/// </summary>

	bool addEntity(Entity* ent);

	/// <summary>
	/// Añade una entidad a la lista de entidades a eliminar. Si existe devuelve false, sino, true y la añade.
	/// </summary>
	bool addEntityToRemove(Entity* ent);


	/// <summary>
	/// Añade una entidad a la lista. Si existe devuelve false, sino, true y la añade.
	/// </summary>
	bool loadComponents();

	/// <summary>
	/// Devuelve una entidad dado su id, si no la encuentra devuelve nullptr. Busca en la lista de la escena y/o en la lista de entidades permanentes
	/// </summary>
	Entity* getEntityByID(int id);

	/// <summary>
	/// Elimina una entidad de la lista y la destruye.
	/// </summary>
	void removeEntities();

	/// <summary>
	/// Devuelve una lista con todas las entidades creadas.
	/// </summary>
	std::vector<Entity*> getEntities();

	/// <summary>
	/// Avisa al manager de que se va a cargar una escana
	/// </summary>
	void newScene(std::string sceneName);

	/// <summary>
	/// Carga las entidades que hay en el vector de entidades a cargar en el vector de entidades a usar
	/// </summary>
	void loadEntities();

	/// <summary>
	/// Pausa las entidades no permanentes
	/// </summary>
	void pauseScene();

	/// <summary>
	/// Reanuda las entidades pausadas, las no pausadas las elimina
	/// </summary>
	void continueScene();

	/// <summary>
	/// Elimina las entidades en las listas.
	/// </summary>
	void deleteEntities();

protected:
	static SceneManager* _singleton;

	bool _newScene = false;
	std::string _sceneName;

	std::vector<Entity*> _entities;
	std::vector<Entity*> _entitiesToRemove;
	std::vector<Entity*> _entitiesToLoad;
	SceneManager() {};
};