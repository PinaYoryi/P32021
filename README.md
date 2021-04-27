# Pina Yoryi

Piña Motor es un motor de videojuegos en tres dimensiones multipropósito, que utiliza el motor gráfico de Ogre, el motor físico de Bullet y el motor de audio de FMOD

## Comenzando 🚀

Existe una única instancia de Input en el motor, utilizando el patrón de Singleton.

**E/S**: Detectamos la entrada de tanto teclado como ratón mediante SDL. 

**LECTURA ARCHIVOS**: Utilizamos LUA para la lectura de los archivos: mapas, audio, etc para posteriormente pasar los datos al núcleo del motor.

**GRÁFICOS**: Usamos Ogre para renderizar los gráficos generados e imágenes. 

**ENTIDADES:** Unidad Objeto Motor. Tienen una lista de componentes que les dan comportamiento (y un componente forzado: Transform); interacción con el loop del juego, que hacen que itere por todos los componentes que tenga añadidos llamando a sus respectivos métodos.

**COMPONENTES**: El motor está estructurado en entidades y componentes. Las entidades son objetos sin función que lo que hacen es llamar a su lista de componentes.
Los componentes son clases con funciones que se asignan a las entidades.
Tienen una interfaz compuesta por: Start(), Update(), FixedUpdate(), TriggerStart(), TriggerEnd(), TriggerStay(), CollisionStart(), CollisionEnd(), CollisionStay() que son virtuales y visibles al programador, y Render() que es visible solo para el motor. Tienen un puntero a la Entidad a la que pertenecen. 
Los componentes heredan de una clase base Componente sin funcionalidad que sirve como interfaz para los métodos. No pueden haber dos instancias del mismo componente en una entidad, pero sí dos componentes que heredan uno de otro.

**TRANSFORM**: Manejo de posición, rotación y escala de las entidades. Tiene métodos para mover, rotar y escalar. Las entidades comienzan con este componente incluido al crearlas. Asociado al Parent.

**UITRANSFORM**: Componente exclusivo de Transform 2D utilizado para incluir entidades en la interfaz de usuario. Hereda todas las funcionalidades descritas y sirve para que se coloque desde ese punto relativo de la pantalla. Los atributos tienen como unidades los píxeles de la pantalla o, en caso del ancla, están normalizadas, de forma que (0,0) está en la esquina inferior izquierda.

**RIGIDBODY**: Determina si la Entidad es afectada por la físicas (Bullet): velocidades y aceleraciones (fuerzas, graviedad y fricción); dependiente de Transform.

**RENDERER**: Comunica con Ogre y renderiza mallas y texturas; actualizado frame a frame. Dependiente de Transform. 

**COLISIÓN**: Interfaz del sistema de colisiones de Bullet. Si intersección: se hacen llamadas a los métodos de colisión o activador en ambas entidades. Depende de Transform. 

**IA**: La tenencia de este componente dota a la entidad de la IA básica del motor. Depende de Transform, Rigidbody. Tiene atributos para la velocidad de rotación, de movimiento, aceleración angular y lineal.
CÁMARA
Se encarga de mostrar el mundo que se va a renderizar. Depende de Transform. La posición (0,0) de la cámara se corresponde con la posición de arriba a la izquierda de la pantalla. Se puede modificar su viewport y su resolución.
TEXTO
Renderiza cualquier cadena de caracteres que quieras en la posición que quieras. Forma parte de la interfaz de usuario. Se puede modificar su fuente, tamaño, color tanto de los caracteres como del resaltado y alineación (izquierda, central o derecha).
IMAGEN
Renderiza una imagen en la posición que se quiera. Se puede modificar su tamaño y posición. Acepta diversos formatos como .png y .jpg.
ANIMACIÓN
Se encarga de realizar las animaciones que se quiera. Se da la opción de transicionar entre diferentes animaciones que previamente se han creado, realizarse en bucle o una sola vez, elegir la animación por defecto y parar de animar.
DROPDOWN 
Depende de Transform y Renderer. Detecta eventos de teclado o ratón y abre una lista con las opciones que contiene, cada elemento es pulsable y al hacerlo, la opción pulsada se mantiene en el dropdown y se cierra la lista. Emite eventos de pulsación al abrir la lista, cerrarla y pulsar una de las opciones de la lista.
BOTÓN 
Forma parte de la interfaz de usuario. Depende de UITransform y Renderer. Detecta eventos de teclado o ratón. Una vez pulsado otras otras entidades reaccionan y hacen lo que les corresponde. 
SISTEMA DE PARTÍCULAS
Se da la opción de crear un sistema de partícula a partir de un archivo .particle, para ello hay que darle un nombre al sistema de partículas y el nombre donde coger todos los parámetros. Se puede activar o desactivar.
AUDIO SOURCE
Carga un archivo de audio y, utilizando FMOD, lo reproduce según diferentes atributos: espacial o global (que se emita desde un punto o se oiga en cualquier lugar), volumen de reproducción, si se loopea el audio… (incluyendo todas las opciones de reproducción que tiene disponible FMOD). Tiene métodos de acceso y modificación de sus atributos, de Play(), Pause(), Stop(), Unpause(). El archivo de audio se mantiene cargado mientras este componente siga cargado.
AUDIO LISTENER
Utiliza la posición de Transform para averiguar si debe escuchar o no los diferentes sonidos que se crean en sus posiciones. Los sonidos globales los escucha siempre que estén reproduciendo. Siguen las propiedades del sonido a la hora de disiparse.
LIGHT
Utiliza las luces de Ogre para crear una propia, utilizando la posición de Transform. Permite seleccionar el tipo de luz: direccional, de punto, foco…, la intensidad, color, sombras que genera.


### Pre-requisitos 📋

_Que cosas necesitas para instalar el software y como instalarlas_

```
Da un ejemplo
```

### Instalación 🔧

_Una serie de ejemplos paso a paso que te dice lo que debes ejecutar para tener un entorno de desarrollo ejecutandose_

_Dí cómo será ese paso_

```
Da un ejemplo
```

_Y repite_

```
hasta finalizar
```

_Finaliza con un ejemplo de cómo obtener datos del sistema o como usarlos para una pequeña demo_

## Ejecutando las pruebas ⚙️

_Explica como ejecutar las pruebas automatizadas para este sistema_

### Analice las pruebas end-to-end 🔩

_Explica que verifican estas pruebas y por qué_

```
Da un ejemplo
```

### Y las pruebas de estilo de codificación ⌨️

_Explica que verifican estas pruebas y por qué_

```
Da un ejemplo
```

## Despliegue 📦

_Agrega notas adicionales sobre como hacer deploy_

## Construido con 🛠️

_Menciona las herramientas que utilizaste para crear tu proyecto_

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - El framework web usado
* [Maven](https://maven.apache.org/) - Manejador de dependencias
* [ROME](https://rometools.github.io/rome/) - Usado para generar RSS

## Contribuyendo 🖇️

Por favor lee el [CONTRIBUTING.md](https://gist.github.com/villanuevand/xxxxxx) para detalles de nuestro código de conducta, y el proceso para enviarnos pull requests.

## Wiki 📖

Puedes encontrar mucho más de cómo utilizar este proyecto en nuestra [Wiki](https://github.com/tu/proyecto/wiki)

## Versionado 📌

Usamos [SemVer](http://semver.org/) para el versionado. Para todas las versiones disponibles, mira los [tags en este repositorio](https://github.com/tu/proyecto/tags).

## Autores ✒️

_Menciona a todos aquellos que ayudaron a levantar el proyecto desde sus inicios_

* **Andrés Villanueva** - *Trabajo Inicial* - [villanuevand](https://github.com/villanuevand)
* **Fulanito Detal** - *Documentación* - [fulanitodetal](#fulanito-de-tal)

También puedes mirar la lista de todos los [contribuyentes](https://github.com/your/project/contributors) quíenes han participado en este proyecto. 

## Licencia 📄

Este proyecto está bajo la Licencia (Tu Licencia) - mira el archivo [LICENSE.md](LICENSE.md) para detalles

