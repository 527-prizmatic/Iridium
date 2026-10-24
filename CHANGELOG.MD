# v0.2.1
- Began doing a changelog
- Introduced safe pointers, and the `ir::SafePointer` and `ir::LazyPointer` classes. They serve as replacements for `std::unique_ptr`, enforcing memory validity (the latter lazily initializes resources if called while invalid)
- Introduced class `ir::ApplicationState` for storing and keeping data across states
- Added functions to `ir::AssetManager` to delete assets
- Optimized `ir::render::ModelRenderer` rendering pipeline:
  - Now caches vertex data when unchanged for long enough (defined as 3 rendering calls)
  - Gave meaning to rendering modes: `WIREFRAME` mode disables rendering of `POINT` and `TRIANGLE` primitive types
- Reworked `ir::Application` and `ir::ApplicationWindow` internals to use the new safe pointers
- Minor tweaks to vector manipulation functions, to handle edge cases more efficiently