#ifndef I2C_HPP
#define I2C_HPP
#include <stdint.h>

#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

namespace husb238a {

// Function to set the ESP-IDF I2C device handle (called from C wrapper)
void HUSB238A_I2C_set_device_handle(i2c_master_dev_handle_t handle);

/**
 * @brief Connection to an I2C device.
 *
 * This class contains methods required to read/write to an I2C device.
 */
class I2C {
 public:
  /**
   * Instantiates an I2C connection to an address.
   * @param addr Slave address
   */
  explicit I2C();

  /**
   * Tests whether the slave can acknowledge I2C requests from us.
   * @return true if the slave can acknowledge, false otherwise
   */
  bool can_ack() const;

  /**
   * Reads a register
   * @param reg_addr Register address
   * @param length Length of bytes to read. Defaults to 1.
   * @return -1 if error, otherwise the value of the register
   */
  int read_register(uint8_t reg_addr, uint8_t length = 1) const;

  /**
   * Writes to a register
   * @param reg_addr Register address
   * @param reg_value Value to write
   * @return 0 if success, otherwise error code (Error Code meaning depends on
   * implementation)
   */
  int write_register(uint8_t reg_addr, uint8_t reg_value) const;
};

}  // namespace husb238a

#endif  // I2C_HPP
