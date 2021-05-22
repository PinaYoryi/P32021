#pragma once
#include <iostream>

// TODO: Macros
class Transform;
class Renderer;
class Camera;
class Animation;
class Rigidbody;
class Light;
class AudioSource;
class AudioListener;
class BasicAI;
class SkyBox;

//TODO: Comentar
template<typename ...Ts>
struct TypeList {
	constexpr static std::size_t size = sizeof...(Ts);
};


template<typename, typename>
struct IndexOf;


template<typename T, typename ...Ts>
struct IndexOf<T, TypeList<T, Ts...>> : std::integral_constant<std::size_t, 0> {

};

template<typename T, typename TOther, typename ...Ts>
struct IndexOf<T, TypeList<TOther, Ts...>> : std::integral_constant<std::size_t, 1 + IndexOf<T, TypeList<Ts...>>()> {

};

using ComponentsList = TypeList<Transform, Renderer, Animation, Camera, Rigidbody, Light, AudioSource, AudioListener, BasicAI, SkyBox>;
constexpr std::size_t numOfComponents = ComponentsList::size;

template<typename T, typename TList>
constexpr std::size_t indexOf = IndexOf<T, TList>();