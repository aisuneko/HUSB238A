#include "HUSB238A.hpp"

namespace husb238a {
HUSB238A::HUSB238A(const uint8_t addr) : _i2c(I2C()) {}

HUSB238A::HUSB238A(const I2C i2c) : _i2c(i2c) {}

int HUSB238A::read_register_byte(const RegisterAddress addr) const {
  return _i2c.read_register(addr);
}

int HUSB238A::write_register_byte(const RegisterAddress addr,
                                  const uint8_t value) const {
  return _i2c.write_register(addr, value);
}
}  // namespace husb238a
