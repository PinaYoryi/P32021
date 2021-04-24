#pragma once
#include <map>
#include <string>

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

protected:
	static ResourceManager* _singleton;

	//Diccionarios que relacionan nombres usables de resources con sus direcciones.
	std::map<std::string, std::string> _audio, _textures;
	std::string texturesPath = "..\\assets\\textures";
	std::string audioPath = "..\\assets\\audio";

	/// <summary>
	/// Carga todas las texturas que se encuentren en la carpeta "assets/textures" y las guarda en su diccionario.
	/// Las direcciones se relacionan con el nombre del archivo en cuestion sin extension.
	/// </summary>
	void loadTextures();

	/// <summary>
	/// Carga todas los audios que se encuentren en la carpeta "assets/audio" y las guarda en su diccionario.
	/// Las direcciones se relacionan con el nombre del archivo en cuestion sin extension.
	/// </summary>
	void loadAudio();

	ResourceManager() {}
};