//
// Created by emrey on 21.04.2022.
//

#ifndef THEBALL_VEC2_HPP
#define THEBALL_VEC2_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

namespace ph {

class Vec2 {
public:
	float x;
	float y;

	Vec2() = default;

	Vec2(float x, float y);

	explicit Vec2(const sf::Vector2f& other);

	Vec2& zero();

	[[nodiscard]] constexpr float dot(const Vec2& b) const;

	[[nodiscard]] inline Vec2 crossX(float value) const;

	[[nodiscard]] inline Vec2 crossY(float value) const;

	[[nodiscard]] float cross(const Vec2& v) const;

	[[nodiscard]] float distance(const Vec2& a) const;

	[[nodiscard]] float distanceSquared(const Vec2& a) const;

	[[nodiscard]] float length() const;

	[[nodiscard]] float lengthSquared() const;

	[[nodiscard]] Vec2 normal(const Vec2& v) const;

	void rotate(Vec2& origin, float radians);

	[[nodiscard]] sf::Vector2f convert() const;

	Vec2 operator-() const;

	Vec2 operator-(float v) const;

	Vec2 operator-(const Vec2& v) const;

	Vec2 operator+(float v) const;

	Vec2 operator+(const Vec2& v) const;

	Vec2 operator*(float v) const;

	Vec2 operator*(const Vec2& v) const;

	Vec2 operator/(float v) const;

	Vec2 operator/(const Vec2& v) const;

	Vec2& operator+=(float v);

	Vec2& operator+=(const Vec2& v);

	Vec2& operator-=(float v);

	Vec2& operator-=(const Vec2& v);

	Vec2& operator*=(float v);

	Vec2& operator*=(const Vec2& v);

	Vec2& operator/=(float v);

	Vec2& operator/=(const Vec2& v);

	bool operator==(const Vec2& v) const;

	bool operator!=(const Vec2& v) const;
};

}

#endif //THEBALL_VEC2_HPP
