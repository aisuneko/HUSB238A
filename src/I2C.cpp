/*
 * I2C.cpp - ESP-IDF implementation for HUSB238A
 */

#include "I2C.hpp"

#include "driver/i2c_master.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace husb238a {

static const char* TAG = "HUSB238A_I2C";
static i2c_master_dev_handle_t g_dev_handle = nullptr;

// Global setter for device handle (called from C wrapper)
void HUSB238A_I2C_set_device_handle(i2c_master_dev_handle_t handle) {
  g_dev_handle = handle;
  ESP_LOGI(TAG, "I2C device handle set");
}

I2C::I2C() {}

bool I2C::can_ack() const {
  if (!g_dev_handle) {
    ESP_LOGW(TAG, "Device handle not set");
    return false;
  }

  // Try to read a byte to check if device acknowledges
  uint8_t dummy;
  esp_err_t ret =
      i2c_master_receive(g_dev_handle, &dummy, 1, pdMS_TO_TICKS(100));

  return ret == ESP_OK;
}

int I2C::read_register(uint8_t reg_addr, uint8_t length) const {
  if (!g_dev_handle) {
    ESP_LOGW(TAG, "Device handle not set");
    return -1;
  }

  if (length != 1) {
    ESP_LOGW(TAG, "Only single byte reads supported, got length=%d", length);
    return -1;
  }

  uint8_t data = 0;
  esp_err_t ret = i2c_master_transmit_receive(g_dev_handle, &reg_addr, 1, &data,
                                              1, pdMS_TO_TICKS(100));

  if (ret != ESP_OK) {
    ESP_LOGD(TAG, "Failed to read register 0x%02X: %s", reg_addr,
             esp_err_to_name(ret));
    return -1;
  }

  return data;
}

int I2C::write_register(uint8_t reg_addr, uint8_t reg_value) const {
  if (!g_dev_handle) {
    ESP_LOGW(TAG, "Device handle not set");
    return -1;
  }

  uint8_t write_buf[2] = {reg_addr, reg_value};
  esp_err_t ret =
      i2c_master_transmit(g_dev_handle, write_buf, 2, pdMS_TO_TICKS(100));

  if (ret != ESP_OK) {
    ESP_LOGD(TAG, "Failed to write register 0x%02X: %s", reg_addr,
             esp_err_to_name(ret));
    return -1;
  }

  return 0;
}

}  // namespace husb238a
