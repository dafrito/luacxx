# Standard Library Types

Luacxx includes built-in support for a small set of standard-library types.

Most of these conversions work by copying values between C++ and Lua rather
than exposing live container views into Lua.

This guide summarizes how each supported type is represented, whether the
conversion copies, and how strict the readback path is.

## General Rule

For the built-in standard-library container and value types:

- pushing to Lua usually creates a fresh Lua value
- storing from Lua usually rebuilds or replaces the C++ object
- conversions are recursive, so element types still need their own Luacxx conversions

That means most standard-library values behave like value transfers, not shared
mutable objects.

## `std::string`

Lua representation:

- Lua string

Copy behavior:

- pushing copies string bytes into a Lua string
- reading copies bytes back into a C++ `std::string`

Strictness:

- retrieval uses Lua string conversion rules through `lua_tolstring`
- `std::string` is the main owned string type for reading from Lua

Related headers:

- [`include/luacxx/convert/string.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/string.hpp)
- [`include/luacxx/convert/const_char_p.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/const_char_p.hpp) for push-only C string and `std::string_view` inputs

## `std::vector<T>`

Lua representation:

- array-style Lua table with integer keys `1..n`

Copy behavior:

- pushing iterates the vector and pushes each element into a new Lua table
- storing resizes and replaces the destination vector's contents

Strictness:

- source must be a Lua table
- length comes from `lua_rawlen`
- it is intended for dense array-like tables

Related header:

- [`include/luacxx/convert/vector.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/vector.hpp)

## `std::array<T, N>`

Lua representation:

- array-style Lua table

Copy behavior:

- pushing copies each element into a new Lua table
- storing overwrites the existing fixed-size array

Strictness:

- source must be a Lua table
- table length must match `N` exactly
- extra or missing elements are rejected

Related header:

- [`include/luacxx/convert/array.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/array.hpp)

## `std::tuple<Ts...>`

Lua representation:

- array-style Lua table

Copy behavior:

- pushing copies each tuple element into a new Lua table
- storing rewrites the destination tuple element-by-element

Strictness:

- source must be a Lua table
- table length must exactly match tuple arity
- extra or missing values are rejected

Related header:

- [`include/luacxx/convert/tuple.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/tuple.hpp)

## `std::optional<T>`

Lua representation:

- contained value if engaged
- `nil` if empty

Copy behavior:

- pushing an engaged optional pushes its contained value
- pushing an empty optional pushes `nil`
- storing from `nil` resets the destination
- storing from a value rebuilds the contained `T`

Strictness:

- `nil` is accepted and maps to `std::nullopt`
- otherwise conversion follows the rules for `T`

Related header:

- [`include/luacxx/convert/optional.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/optional.hpp)

## `std::map<K, V>`

Lua representation:

- Lua table with arbitrary keys

Copy behavior:

- pushing creates a fresh Lua table and inserts copied key/value pairs
- storing clears the destination map and rebuilds it from the Lua table

Strictness:

- source must be a Lua table
- key and value conversion must succeed for each entry
- iteration order in Lua is not preserved or relied on

Related header:

- [`include/luacxx/convert/map.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/map.hpp)

## `std::unordered_map<K, V>`

Lua representation:

- Lua table with arbitrary keys

Copy behavior:

- pushing creates a fresh Lua table and inserts copied key/value pairs
- storing clears and rebuilds the destination unordered map

Strictness:

- source must be a Lua table
- key and value conversion must succeed for each entry
- ordering is inherently not part of the contract

Related header:

- [`include/luacxx/convert/unordered_map.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/unordered_map.hpp)

## `std::shared_ptr<T>`

Lua representation:

- userdata using `T`'s metatable behavior

Copy behavior:

- this is the main exception to the “copy values” rule
- pushing a `shared_ptr<T>` preserves shared ownership of the same underlying object
- getting it back returns another `shared_ptr<T>` to that same object

Strictness:

- type behavior comes from `Metatable<T>`
- this is not treated as a plain `void*`
- it is for shared ownership, not value copying

Related header:

- [`include/luacxx/convert/shared_ptr.hpp`](/Users/aaronfaanes/Documents/luacxx/include/luacxx/convert/shared_ptr.hpp)

## Push-Only String Inputs

Luacxx also accepts a few string-like inputs mainly for pushing values into
Lua:

- `const char*`
- `char*`
- `std::string_view`

These are convenience input types, not the main owned readback types.

If you want to read a string back from Lua safely, prefer `std::string`.

## Rule Of Thumb

- Use `std::string` for owned string data.
- Expect most standard-library containers to round-trip by copying.
- Expect `std::array` and `std::tuple` to be strict about exact size.
- Expect `std::optional` to use `nil` as empty.
- Use `std::shared_ptr<T>` only when shared ownership is the intended model.

## Related Docs

- [Conversion Templates](conversion-templates.md)
- [Binding a Primitive Type](binding-a-primitive-type.md)
- [Binding a Class](binding-a-class.md)
- [Working With shared_ptr](working-with-shared-ptr.md)
