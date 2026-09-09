# The following variables contains the files used by the different stages of the build process.
set(HVAC_default_default_XC32_FILE_TYPE_assemble)
set_source_files_properties(${HVAC_default_default_XC32_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${HVAC_default_default_XC32_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(HVAC_default_default_XC32_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${HVAC_default_default_XC32_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${HVAC_default_default_XC32_FILE_TYPE_assembleWithPreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(HVAC_default_default_XC32_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/config/default/exceptions.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/config/default/initialization.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/config/default/interrupts.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/config/default/libc_syscalls.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/config/default/peripheral/clock/plib_clock.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/config/default/peripheral/evsys/plib_evsys.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/config/default/peripheral/nvic/plib_nvic.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/config/default/peripheral/port/plib_port.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/config/default/peripheral/tc/plib_tc0.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/config/default/startup_xc32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/config/default/stdio/xc32_monitor.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/segment_pins.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/seven_seg.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/switch.c")
set_source_files_properties(${HVAC_default_default_XC32_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(HVAC_default_default_XC32_FILE_TYPE_compile_cpp)
set_source_files_properties(${HVAC_default_default_XC32_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(HVAC_default_default_XC32_FILE_TYPE_link)

# The linker script used for the build.
set(HVAC_default_LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/../../../config.mcc/src/config/default/PIC32CM6408PL10032.ld")
set(HVAC_default_image_name "default.elf")
set(HVAC_default_image_base_name "default")

# The output directory of the final image.
set(HVAC_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/HVAC")

# The full path to the final image.
set(HVAC_default_full_path_to_image ${HVAC_default_output_dir}/${HVAC_default_image_name})
