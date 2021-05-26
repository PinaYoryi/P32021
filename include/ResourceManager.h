#pragma once
#include <map>
#include <string>
#include <filesystem>

static const std::string MOTOR_RESOURCES_PATH = "..\\assets\\resources";
static const std::string GAME_RESOURCES_PATH = "..\\..\\P32021\\assets\\resources";

class ResourceManager {
public:
	~ResourceManager() {}

	/// <summary>
	/// Devuelve una instancia de la clase. Nullptr si no esta inicializada.
	/// </summary>
	static ResourceManager* GetInstance();

	/// <summary>
	/// Inicializa la clase con los parametros dados.
	/// </summary>
	static ResourceManager* Init();

	/// <summary>
	/// Devuelve la direcci�n de la textura con el nombre name.
	/// Si no lanza excepci�n.
	/// </summary>
	std::string texture(std::string name);

	/// <summary>
	/// Devuelve la direcci�n de la audio con el nombre name.
	/// Si no lanza excepci�n.
	/// </summary>
	std::string audio(std::string name);

	/// <summary>
	/// Devuelve la direcci�n del audio con el nombre name.
	/// Si no lanza excepci�n.
	/// </summary>
	std::string scene(std::string name);

	/// <summary>
	/// Devuelve la direccion del prefab con el nombre name
	/// Si no lanza excepcion
	/// </summary>
	std::string prefab(std::string name);

protected:
	static ResourceManager* _singleton;
	std::map<std::string, std::string> _audio, _textures, _scenes, _prefabs;

	//Diccionarios que relacionan nombres usables de resources con sus direcciones.

	/// <summary>
	/// Mira de forma recursiva las carpetas en la direcci�n RESOURCES_PATH.
	/// Cuando encuentra archivos llama a loadAsset para intentar a�adirlos al manager.
	/// </summary>
	void searchDir(std::filesystem::path path);

	/// <summary>
	/// Comprueba los tipos de un archivo dado con direccion path y si el tipo es soportado lo a�ade al manager.
	/// </summary>
	void loadAsset(std::filesystem::path path, size_t end, size_t pathLenght);

	ResourceManager() {}
};