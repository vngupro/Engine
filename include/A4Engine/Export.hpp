#pragma once

#ifdef _WIN32

// Sur Windows, les symboles s'exportent avec l'attribut dllexport mais doivent s'importer avec dllimport
// On utilise donc un define lors de la compilation du moteur (qui ne sera pas pr�sent � son utilisation) pour les distinguer

#ifdef A4ENGINE_BUILD
#define A4ENGINE_API __declspec(dllexport)
#else
#define A4ENGINE_API __declspec(dllimport)
#endif

#else

// Sur les autres syst�mes, rendre le symbole visible suffit � l'import comme � l'export

#define A4ENGINE_API __attribute__((visibility("default")))

#endif