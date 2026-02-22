#include "luacxx/global.hpp"
#include "luacxx/convert/callable.hpp"

lua::reference lua::global::operator()() const {
  return lua::call<lua::reference>(*this);
}
