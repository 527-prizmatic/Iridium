#ifndef IRIDIUM_LIBRARIES_HPP_
#define IRIDIUM_LIBRARIES_HPP_

#pragma GCC diagnostic ignored "-Wunused-parameter"

// C++ core and STL features
#include <memory>
#include <type_traits>
#include <functional>
#include <map>
#include <any>
#include <list>
#include <fstream>
#include <string>
#include <string_view>

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

// GSL
#include <gsl/gsl>

// JSON
#include "nlohmann/json.hpp"

// Base-level Iridium components
#include "log.hpp"
#include "math.hpp"
#include "vector.hpp"
#include "random.hpp"
#include "colors.hpp"
#include "time.hpp"
#include "exceptions.hpp"

namespace ir {
	namespace render {
		class Model;
	}

	using TextureHandle = uint32_t;
	using SoundHandle = uint32_t;
	using MusicHandle = uint32_t;
	using ModelHandle = uint32_t;

	using TextureAsset = sf::Texture;
	using SoundAsset = sf::SoundBuffer;
	using MusicAsset = sf::Music;
	using ModelAsset = render::Model;
}

#endif // IRIDIUM_LIBRARIES_HPP_