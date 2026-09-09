include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(HVAC_default_library_list )

# Handle files with suffix s, for group default-XC32
if(HVAC_default_default_XC32_FILE_TYPE_assemble)
add_library(HVAC_default_default_XC32_assemble OBJECT ${HVAC_default_default_XC32_FILE_TYPE_assemble})
    HVAC_default_default_XC32_assemble_rule(HVAC_default_default_XC32_assemble)
    list(APPEND HVAC_default_library_list "$<TARGET_OBJECTS:HVAC_default_default_XC32_assemble>")

endif()

# Handle files with suffix S, for group default-XC32
if(HVAC_default_default_XC32_FILE_TYPE_assembleWithPreprocess)
add_library(HVAC_default_default_XC32_assembleWithPreprocess OBJECT ${HVAC_default_default_XC32_FILE_TYPE_assembleWithPreprocess})
    HVAC_default_default_XC32_assembleWithPreprocess_rule(HVAC_default_default_XC32_assembleWithPreprocess)
    list(APPEND HVAC_default_library_list "$<TARGET_OBJECTS:HVAC_default_default_XC32_assembleWithPreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC32
if(HVAC_default_default_XC32_FILE_TYPE_compile)
add_library(HVAC_default_default_XC32_compile OBJECT ${HVAC_default_default_XC32_FILE_TYPE_compile})
    HVAC_default_default_XC32_compile_rule(HVAC_default_default_XC32_compile)
    list(APPEND HVAC_default_library_list "$<TARGET_OBJECTS:HVAC_default_default_XC32_compile>")

endif()

# Handle files with suffix cpp, for group default-XC32
if(HVAC_default_default_XC32_FILE_TYPE_compile_cpp)
add_library(HVAC_default_default_XC32_compile_cpp OBJECT ${HVAC_default_default_XC32_FILE_TYPE_compile_cpp})
    HVAC_default_default_XC32_compile_cpp_rule(HVAC_default_default_XC32_compile_cpp)
    list(APPEND HVAC_default_library_list "$<TARGET_OBJECTS:HVAC_default_default_XC32_compile_cpp>")

endif()

# Handle files with suffix [cC], for group default-XC32
if(HVAC_default_default_XC32_FILE_TYPE_dependentObject)
add_library(HVAC_default_default_XC32_dependentObject OBJECT ${HVAC_default_default_XC32_FILE_TYPE_dependentObject})
    HVAC_default_default_XC32_dependentObject_rule(HVAC_default_default_XC32_dependentObject)
    list(APPEND HVAC_default_library_list "$<TARGET_OBJECTS:HVAC_default_default_XC32_dependentObject>")

endif()


# Main target for this project
add_executable(HVAC_default_image_B3hQTBcl ${HVAC_default_library_list})

set_target_properties(HVAC_default_image_B3hQTBcl PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    RUNTIME_OUTPUT_DIRECTORY "${HVAC_default_output_dir}")
target_link_libraries(HVAC_default_image_B3hQTBcl PRIVATE ${HVAC_default_default_XC32_FILE_TYPE_link})
# Add the link options from the rule file.
HVAC_default_link_rule( HVAC_default_image_B3hQTBcl)

# Add bin2hex target for converting built file to a .hex file.
string(REGEX REPLACE [.]elf$ .hex HVAC_default_image_name_hex ${HVAC_default_image_name})
add_custom_target(HVAC_default_Bin2Hex ALL
    COMMAND ${MP_BIN2HEX} \"${HVAC_default_output_dir}/${HVAC_default_image_name}\"
    BYPRODUCTS ${HVAC_default_output_dir}/${HVAC_default_image_name_hex}
    COMMENT "Convert built file to .hex")
add_dependencies(HVAC_default_Bin2Hex HVAC_default_image_B3hQTBcl)




