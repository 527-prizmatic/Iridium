#include "vector.hpp"

namespace ir {
	const ir::Vector ir::Vector::kZero = ir::Vector{ 0.f, 0.f };
	const ir::Vector ir::Vector::kUnit = ir::Vector{ 1.f, 0.f };

	Vector::Vector() {
		x = 0.f;
		y = 0.f;
	}

	Vector::Vector(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vector::Vector(const ir::Vector& other) {
		x = other.x;
		y = other.y;
	}

	ir::Vector& Vector::operator=(const ir::Vector& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	bool Vector::isZero() const {
		return abs(x) <= std::numeric_limits<float>::epsilon()
			&& abs(y) <= std::numeric_limits<float>::epsilon();
	}

	ir::Vector Vector::polar(float radius, float angle) {
		Expects(radius >= 0.f);
		return ir::Vector(radius, angle).polToRec();
	}
	
	float Vector::magnitude() const {
		float mag2 { magnitudeSquare() };
		if (ir::math::isZero(mag2 - 1.f)) { ///< Special case for unit vectors
			return mag2;
		}
		return std::sqrtf(mag2);
	}

	float Vector::magnitudeSquare() const {
		return x * x + y * y;
	}
	
	float Vector::angle(ir::Vector reference) const {
		if (isZero()) {
			return 0.f;
		}
		if (*this == reference) { ///< Special case if both vectors are equal
			return 0.f;
		}
		return std::atan2(y, x) - std::atan2(reference.y, reference.x);
	}
	
	float Vector::distance(ir::Vector other) const {
		return (*this - other).magnitude();
	}
	
	ir::Vector Vector::normalize() const {
		if (isZero()) { ///< Special case for zero vectors
			return kUnit;
		}
		if (ir::math::isZero(this->magnitudeSquare() - 1.f)) { ///< Special case for unit vectors
			return *this;
		}
		return *this / magnitude();
	}
	
	ir::Vector Vector::clampMagnitude(float max) const {
		Expects(max >= 0.f);

		float mag { magnitude() };
		if (mag > max) {
			return *this / mag * max;
		}
		return *this;
	}
	
	ir::Vector Vector::clampMagnitude(float min, float max) const {
		Expects(max >= min);
		Expects(min >= 0.f);

		float mag2 { magnitudeSquare() };
		if (mag2 < min * min) {
			return *this / magnitude() * min;
		}
		if (mag2 > max * max) {
			return *this / magnitude() * max;
		}

		return *this;
	}
	
	ir::Vector Vector::recToPol() const {
		return ir::Vector{ magnitude(), angle() };
	}
	
	ir::Vector Vector::polToRec() const {
		return ir::Vector{ x * std::cosf(y), x * std::sinf(y) };
	}
	
	ir::Vector Vector::rotate(float angle) const {
		if (ir::math::isZero(angle) || isZero()) { ///< Special case if any argument is zero
			return *this;
		}

		if (angle == ir::math::pi) { ///< Special case for pi
			return -*this;
		}
		
		if (angle == ir::math::pi * .5f) { ///< Special case for pi/2
			return ir::Vector { -this->y, this->x };
		}
		
		if (angle == ir::math::pi * -.5f) { ///< Special case for -pi/2
			return ir::Vector { this->y, -this->x };
		}

		ir::Vector v { recToPol() };
		v.y += angle;
		return v.polToRec();
	}
	
	ir::Vector Vector::rotate(float angle, ir::Vector reference) const {
		return reference + (*this - reference).rotate(angle);
	}
	
	ir::Vector Vector::mirror(ir::Vector axis) const {
		if (isZero() || axis.isZero()) {
			return *this;
		}
		float currentAngle { angle(axis) };
		if (ir::math::isZero(currentAngle)) {
			return *this;
		}
		return rotate(currentAngle * 2.f);
	}
	
	ir::Vector Vector::mirrorX() const {
		return ir::Vector{ -x, y };
	}
	
	ir::Vector Vector::mirrorY() const {
		return ir::Vector{ x, -y };
	}
	
	ir::Vector Vector::negate() const {
		return ir::Vector{ -x, -y };
	}

	float Vector::dot(const ir::Vector a, const ir::Vector b) {
		return a.x * b.x + a.y * b.y;
	}

	float Vector::dot(const ir::Vector other) const {
		return x * other.x + y * other.y;
	}
}