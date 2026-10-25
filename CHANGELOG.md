# Changelog

## 5.0.0

This release contains source and behavior changes that require review when
upgrading from 4.0.0. It keeps C++20, CMake 3.24+, and Lua 5.2+ as the minimum
requirements.

### Migration from 4.0.0

- Read Lua strings as `std::string` using `luacxx/convert/string.hpp`.
  `Get<const char*>` and `Store<const char*>` are no longer provided. C strings
  and `std::string_view` remain supported as push-time inputs through
  `luacxx/convert/const_char_p.hpp`. The old `luacxx/convert/char_p.hpp` header
  has been removed. Use the Lua C API directly when a borrowed string pointer
  is required, respecting Lua's ownership and lifetime rules.
- `std::string` conversions preserve embedded NUL bytes.
- `void*` retrieval accepts only light userdata. Retrieve full userdata through
  its declared C++ type instead of treating it as an untyped pointer.
- Storing a Lua array into an existing `std::vector` replaces its contents
  instead of appending to them.
- The incomplete `luacxx/std/vector.hpp` userdata wrapper has been removed.
  Use `luacxx/convert/vector.hpp` for Lua-table conversions, or define an
  explicit binding when a userdata-backed container is needed.
- Use `LUACXX_ALLOW_MISSING_METATABLES` for the optional fallback-metatable
  policy. The older `LUACXX_AUTO_METATABLE` name remains a compatibility alias;
  explicit metatables are still required by default.
- Autotools support and the bundled third-party demo bindings have been
  removed. Build and consume the core library through CMake or its installed
  pkg-config file.
- Loading failures now consistently use `lua::error`, including file-open,
  stream-read, and Lua compilation memory errors. It derives from
  `std::runtime_error`, so existing base-class catches still work; catch
  `lua::error` first when using its Lua-specific diagnostics.

### Added

- Conversions for `std::array`, `std::map`, `std::unordered_map`,
  `std::optional`, and `std::tuple`.
- Expanded guides and API reference documentation, including string ownership,
  type safety, userdata lifetimes, callables, and the Lua stack.
- A multi-file counter example demonstrating an explicit class binding.

### Fixed

- Make stack iterators copy-assignable across Lua states and stack positions,
  fixing a compile error reported by GCC when including `luacxx/range.hpp`.
- Define `lua::memory_address` in the namespace declared by its public header,
  fixing downstream linking.
- Handle short streams, shebang-prefixed Lua source, and stream I/O failures
  more consistently when loading Lua code.
- Correct class-binding examples, documentation links, and reference guidance.

## 4.0.0

Initial tagged CMake release.
