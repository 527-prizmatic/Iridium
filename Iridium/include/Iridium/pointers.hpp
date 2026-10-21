#ifndef IRIDIUM_POINTERS_HPP_
#define IRIDIUM_POINTERS_HPP_

namespace ir {
	/// @brief Base class for all Iridium safe pointers.
	///
	/// Safe pointers are an extension of the `std::unique_ptr` class which perform automatic
	/// validity checks upon dereferencing. Derivatives of the `ir::SafePointer` class can be created to specify
	/// different behaviors upon dereferencing an invalid pointer. The base class simply throws `ir::Exceptions::InvalidSafePtr`.
	/// @tparam T Type of the stored resource
	template <typename T>
	class SafePointer {
	public:
		using Type_ = T; ///< Stored resource type

		/// @brief Default constructor
		SafePointer() {
			ptr_.reset();
		}
		
		/// @brief In-place constructor
		template <typename... Args>
		SafePointer(Args... args) {
			ptr_ = std::make_unique<Type_>(args...);
		}

		/// @brief Initializes a resource with a construction argument list
		template <typename... Args>
		T* create(Args... args) {
			ptr_ = std::make_unique<Type_>(args...);
			return ptr_.get();
		}

		/// @brief Initializes a resource with a construction argument list
		template <typename U, typename... Args>
		requires std::is_base_of<T, U>::value
		U* create(Args... args) {
			ptr_ = std::make_unique<Type_>(args...);
			return ptr_.get();
		}

		/// @brief Constructs with a copy of a resource
		SafePointer(const Type_& other) {
			ptr_ = std::make_unique<Type_>(other);
		}

		/// @brief Constructs by acquiring ownership of a moved resource
		SafePointer(Type_&& other) {
			ptr_ = std::make_unique<Type_>(std::move(other));
		}

		/// @brief Copy constructor (deleted)
		SafePointer(const ir::SafePointer<Type_>& other) = delete;
		/// @brief Copy assignment operator (deleted)
		inline bool operator=(const ir::SafePointer<Type_>& other) = delete;
		
		/// @brief Move constructor
		SafePointer(ir::SafePointer<Type_>&& other) {
			ptr_ = std::move(other.ptr_);
			other.ptr_.reset();
		}

		/// @brief Move assignment operator
		inline bool operator=(ir::SafePointer<Type_>&& other) {
			ptr_ = std::move(other.ptr_);
			other.ptr_.reset();
		}

		/// @brief Member-of-pointer operator
		inline Type_* operator->() {
			check();
			return ptr_.get();
		}

		/// @brief Member-of-pointer operator
		inline Type_* operator->() const {
			check();
			return ptr_.get();
		}

		/// @brief Indirection operator
		inline Type_* operator*() {
			check();
			return ptr_.get();
		}

		/// @brief Indirection operator
		inline Type_* operator*() const {
			check();
			return ptr_.get();
		}

		/// @brief Whether the resource has been initialized
		inline operator bool() const noexcept {
			return static_cast<bool>(ptr_);
		}

		inline T& value() {
			check();
			return *ptr_.get();
		}

		inline T& value() const {
			check();
			return *ptr_.get();
		}

		inline T* address() {
			return &(*ptr_.get());
		}

		inline T* address() const {
			return &(*ptr_.get());
		}

		/// @brief Destroys stored resource.
		inline void reset() noexcept {
			ptr_.reset();
		}

		/// @brief Releases resource ownership.
		inline Type_* release() noexcept {
			return ptr_.release();
		}

	protected:
		mutable std::unique_ptr<Type_> ptr_;

		void check() const {
			if (ptr_ == nullptr) {
				if (!handleInvalid()) {
					throw ir::Exceptions::InvalidSafePtr {};
				}
			}
		}

		/// @brief Function to execute upon attempting to dereference an invalid pointer
		/// @return Whether the dereferencing operation can continue safely (false throws `ir::Exceptions::InvalidSafePtr`)
		inline virtual bool handleInvalid() const {
			LOG_ERROR("Attempted to dereference invalid safe pointer");
			return false;
		}
	};
	
	/// @brief A derivative of `ir::SafePointer` which lazily initializes its resource upon dereferencing.
	///
	/// Safe pointers are an extension of the `std::unique_ptr` class which perform automatic
	/// validity checks upon dereferencing. Derivatives of the `ir::SafePointer` class can be created to specify
	/// different behaviors upon dereferencing an invalid pointer. The base class simply throws `ir::Exceptions::InvalidSafePtr`.
	/// @attention The resource is built with a zero-argument constructor. Pay attention to whether T has one available.
	/// @tparam T Type of the stored resource
	template <typename T>
	class LazyPointer : public SafePointer<T> {
	public:
		LazyPointer() : SafePointer<T>() {}
		
		template <typename... Args>
		LazyPointer(Args... args) : SafePointer<T>(args...) {}
	
	protected:
		inline virtual bool handleInvalid() const override {
			LOG_WARN("Attempted to dereference invalid lazy pointer. Initializing with default values");
			SafePointer<T>::ptr_ = std::make_unique<T>();
			return SafePointer<T>::ptr_ != nullptr;
		}
	};
}

#endif // IRIDIUM_POINTERS_HPP_