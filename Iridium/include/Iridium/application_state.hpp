#ifndef IRIDIUM_APPSTATE_HPP_
#define IRIDIUM_APPSTATE_HPP_

#include "libraries.hpp"

#include <unordered_map>

namespace ir {
	class ApplicationState {
	public:
		/// @brief Saves a value into global application state. Thread-safe.
		///
		/// @param key Lookup key to save the value as
		/// @return Whether the operation was successful
		template <typename T>
		inline bool save(std::string key, T data) {
			std::lock_guard<std::mutex> lock { m_ };
			data_[key] = data;
			return data_.contains(key);
		}

		/// @brief Attempts to retrieve a saved value with the given key. Thread-safe.
		///
		/// To enforce type safety, the type of the stored data must be passed to this function, else it will fail.
		///
		/// @param key Lookup key 
		template <typename T>
		inline std::optional<T> loadValue(std::string key) {
			std::lock_guard<std::mutex> lock { m_ };

			if (data_.contains(key)) {
				if (typeid(T).name() == data_.at(key).type().name()) {
					return std::any_cast<T>(data_.at(key));
				}
				else {
					LOG_WARN(std::string("Attempted to retrieve global appstate key ") + key + " with invalid type");
				}
			}
			return {};
		}
	
		/// @brief Exposes a stored `std::any` container for direct value assignment.
		/// Not recommended for use 
		/// @param key Lookup key
		inline std::any& operator[](std::string key) {
			if (!data_.contains(key)) {
				data_[key] = 0; /// Add default value
			}
			return data_[key];
		}
		
		/// @brief Attempts to delete a saved value with the given key. Thread-safe.
		///
		/// Type information is gathered upon first saving data.
		/// To enforce type safety, the exact same type must be passed to this function, else it will fail.
		///
		/// @param key Lookup key
		/// @return Whether the value was successfully deleted
		template <typename T>
		inline bool erase(std::string key) {
			std::lock_guard<std::mutex> lock { m_ };

			if (data_.contains(key)) {
				if (typeid(T).name() == data_.at(key).type().name()) {
					data_.erase(key);
					return true;
				}
				else {
					LOG_WARN(std::string("Attempted to delete global appstate key ") + key + " with invalid type");
				}
			}
			return false;
		}

	private:
		std::unordered_map<std::string, std::any> data_;
		std::mutex m_;
	};
}

#endif // IRIDIUM_APPSTATE_HPP_