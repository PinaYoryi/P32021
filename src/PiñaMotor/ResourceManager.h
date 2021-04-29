#pragma once
#include <map>
#include <string>
#include <filesystem>

static const std::string RESOURCES_PATH = "..\\assets\\resources";

class ResourceManager {
public:
	~ResourceManager() {
	}

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

protected:
	static ResourceManager* _singleton;
	std::map<std::string, std::string> _audio, _textures;

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