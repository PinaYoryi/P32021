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
	/// Devuelve la dirección de la textura con el nombre name.
	/// Si no lanza excepción.
	/// </summary>
	std::string texture(std::string name);

	/// <summary>
	/// Devuelve la dirección de la audio con el nombre name.
	/// Si no lanza excepción.
	/// </summary>
	std::string audio(std::string name);
	std::map<std::string, std::string> _audio, _textures;

protected:
	static ResourceManager* _singleton;

	//Diccionarios que relacionan nombres usables de resources con sus direcciones.

	/// <summary>
	/// Mira de forma recursiva las carpetas en la dirección RESOURCES_PATH.
	/// Cuando encuentra archivos llama a loadAsset para intentar añadirlos al manager.
	/// </summary>
	void searchDir(std::filesystem::path path);

	/// <summary>
	/// Comprueba los tipos de un archivo dado con direccion path y si el tipo es soportado lo añade al manager.
	/// </summary>
	void loadAsset(std::filesystem::path path, size_t end, size_t pathLenght);

	ResourceManager() {}
};