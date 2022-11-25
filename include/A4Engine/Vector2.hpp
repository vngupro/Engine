#pragma once

#include <ostream>

// Pas de macro d'export pour les templates (leur code n'�tant pas compil� dans la dll)
template<typename T>
struct Vector2
{
	Vector2() = default; // valeur non-initialis�e
	explicit Vector2(T V); //< explicit permet d'�viter les conversions implicites, sans �a on aurait pu �crire Vector2 x = 42, ou passer un entier � une fonction attendant un Vector2
	Vector2(T X, T Y);

	Vector2 operator+(const Vector2& vec) const;
	Vector2 operator-(const Vector2& vec) const;
	Vector2 operator*(const Vector2& vec) const;
	Vector2 operator*(T value) const;
	Vector2 operator/(const Vector2& vec) const;
	Vector2 operator/(T value) const;

	Vector2& operator+=(const Vector2& vec);
	Vector2& operator-=(const Vector2& vec);
	Vector2& operator*=(const Vector2& vec);
	Vector2& operator*=(T value);
	Vector2& operator/=(const Vector2& vec);
	Vector2& operator/=(T value);

	static Vector2 Rotate(const Vector2& vec, float degrees);

	T x, y;
};

template<typename T> Vector2<T> operator*(T value, const Vector2<T>& vec);
template<typename T> Vector2<T> operator/(T value, const Vector2<T>& vec);

// Op�rateur de flux, permet d'�crire un Vector2 directement dans std::cout (ou autre flux de sortie)
template<typename T> std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec);

// On peut utiliser using pour faire un alias plus facile � �crire
using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;

// Il est relativement courant de s�parer le code template dans un fichier annexe, pour clarifier les headers
// cela peut se faire en incluant un autre fichier (rappel, #include = copier-coller)
#include <A4Engine/Vector2.inl>
