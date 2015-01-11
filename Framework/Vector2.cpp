#include "Vector2.hpp"
#include <SDL.h>

namespace sdl {
	Vector2i::Vector2i(i32_t cx, i32_t cy) : x(cx), y(cy) {

	}

	Vector2i::Vector2i(const Vector2f& vec) : Vector2i(static_cast<i32_t>(vec.x), static_cast<i32_t>(vec.y)) {

	}

	SDL_Point* Vector2i::copyInto(SDL_Point* point) const {
		if (point) {
			point->x = this->x;
			point->y = this->y;
		}

		return point;
	}

	Vector2i operator +(const Vector2i& lhs, const Vector2i& rhs) {
		return Vector2i(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	Vector2i operator -(const Vector2i& lhs, const Vector2i& rhs) {
		return Vector2i(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	Vector2i operator *(const Vector2i& lhs, const Vector2i& rhs) {
		return Vector2i(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	Vector2i operator /(const Vector2i& lhs, const Vector2i& rhs) {
		return Vector2i(lhs.x / rhs.x, lhs.y / rhs.y);
	}

	Vector2i operator %(const Vector2i& lhs, const Vector2i& rhs) {
		return Vector2i(lhs.x % rhs.x, lhs.y % rhs.y);
	}

	Vector2i operator +(const Vector2i& lhs, i32_t rhs) {
		return Vector2i(lhs.x + rhs, lhs.y + rhs);
	}

	Vector2i operator -(const Vector2i& lhs, i32_t rhs) {
		return Vector2i(lhs.x - rhs, lhs.y - rhs);
	}

	Vector2i operator *(const Vector2i& lhs, i32_t rhs) {
		return Vector2i(lhs.x * rhs, lhs.y * rhs);
	}

	Vector2i operator /(const Vector2i& lhs, i32_t rhs) {
		return Vector2i(lhs.x / rhs, lhs.y / rhs);
	}

	Vector2i operator %(const Vector2i& lhs, i32_t rhs) {
		return Vector2i(lhs.x % rhs, lhs.y % rhs);
	}

	Vector2i& operator +=(Vector2i& lhs, const Vector2i& rhs) {
		lhs.x += rhs.x;
		lhs.y += rhs.y;

		return lhs;
	}

	Vector2i& operator -=(Vector2i& lhs, const Vector2i& rhs) {
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;

		return lhs;
	}

	Vector2i& operator *=(Vector2i& lhs, const Vector2i& rhs) {
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;

		return lhs;
	}

	Vector2i& operator /=(Vector2i& lhs, const Vector2i& rhs) {
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;

		return lhs;
	}

	Vector2i& operator %=(Vector2i& lhs, const Vector2i& rhs) {
		lhs.x %= rhs.x;
		lhs.y %= rhs.y;

		return lhs;
	}

	bool operator ==(const Vector2i& lhs, const Vector2i& rhs) {
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	bool operator !=(const Vector2i& lhs, const Vector2i& rhs) {
		return !(lhs == rhs);
	}

	SDL_Point* TryCopyInto(const Vector2i* vec, SDL_Point* sdl_point) {
		if (vec)
			return vec->copyInto(sdl_point);
		return nullptr;
	}
}