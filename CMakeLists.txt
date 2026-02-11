idf_component_register(
    SRCS
        "src/HUSB238A.cpp"
        "src/I2C.cpp"
    INCLUDE_DIRS "src"
    REQUIRES driver esp_timer
)

# Enable C++17 for the component
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++17)
