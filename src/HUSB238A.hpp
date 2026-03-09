#ifndef HUSB238A_HPP
#define HUSB238A_HPP

#include <reg/RegisterAddresses.hpp>

#include "I2C.hpp"

namespace husb238a {

class HUSB238A {
 public:
  /**
   * Instantiate to access an instance of HUSB238A.
   * @param addr I2C address of the HUSB238A
   */
  explicit HUSB238A(uint8_t addr);

  explicit HUSB238A(I2C i2c);

  /* General purpose access for any registers */
  int read_register_byte(RegisterAddress addr) const;
  int write_register_byte(RegisterAddress addr, uint8_t value) const;

 private:
  I2C _i2c;  // I2C device
};
}  // namespace husb238a

#endif  // HUSB238A_HPP
