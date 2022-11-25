#pragma once

#include <ostream>

// Pas de macro d'export pour les templates (leur code n'�tant pas compil� dans la dll)
template<typename T>
struct Vector4
{
	Vector4() = default; // valeur non-initialis�e
	explicit Vector4(T V); //< explicit permet d'�viter les conversions implicites, sans �a on aurait pu �crire Vector4 x = 42, ou passer un entier � une fonction attendant un Vector4
	Vector4(T X, T Y, T Z, T W);

	Vector4 operator+(const Vector4& vec) const;
	Vector4 operator-(const Vector4& vec) const;
	Vector4 operator*(const Vector4& vec) const;
	Vector4 operator*(T value) const;
	Vector4 operator/(const Vector4& vec) const;
	Vector4 operator/(T value) const;

	Vector4& operator+=(const Vector4& vec);
	Vector4& operator-=(const Vector4& vec);
	Vector4& operator*=(const Vector4& vec);
	Vector4& operator*=(T value);
	Vector4& operator/=(const Vector4& vec);
	Vector4& operator/=(T value);

	T x, y, z, w;
};

template<typename T> Vector4<T> operator*(T value, const Vector4<T>& vec);
template<typename T> Vector4<T> operator/(T value, const Vector4<T>& vec);

// Op�rateur de flux, permet d'�crire un Vector4 directement dans std::cout (ou autre flux de sortie)
template<typename T> std::ostream& operator<<(std::ostream& os, const Vector4<T>& vec);

// On peut utiliser using pour faire un alias plus facile � �crire
using Vector4f = Vector4<float>;
using Vector4i = Vector4<int>;

// Il est relativement courant de s�parer le code template dans un fichier annexe, pour clarifier les headers
// cela peut se faire en incluant un autre fichier (rappel, #include = copier-coller)
#include <A4Engine/Vector4.inl>
