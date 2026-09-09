set(DEPENDENT_MP_BIN2HEXHVAC_default_B3hQTBcl "c:/Program Files/Microchip/xc32/v6.00/bin/xc32-bin2hex.exe")
set(DEPENDENT_DEPENDENT_TARGET_ELFHVAC_default_B3hQTBcl ${CMAKE_CURRENT_LIST_DIR}/../../../../out/HVAC/default.elf)
set(DEPENDENT_TARGET_DIRHVAC_default_B3hQTBcl ${CMAKE_CURRENT_LIST_DIR}/../../../../out/HVAC)
set(DEPENDENT_BYPRODUCTSHVAC_default_B3hQTBcl ${DEPENDENT_TARGET_DIRHVAC_default_B3hQTBcl}/${sourceFileNameHVAC_default_B3hQTBcl}.c)
add_custom_command(
    OUTPUT ${DEPENDENT_TARGET_DIRHVAC_default_B3hQTBcl}/${sourceFileNameHVAC_default_B3hQTBcl}.c
    COMMAND ${DEPENDENT_MP_BIN2HEXHVAC_default_B3hQTBcl} --image ${DEPENDENT_DEPENDENT_TARGET_ELFHVAC_default_B3hQTBcl} --image-generated-c ${sourceFileNameHVAC_default_B3hQTBcl}.c --image-generated-h ${sourceFileNameHVAC_default_B3hQTBcl}.h --image-copy-mode ${modeHVAC_default_B3hQTBcl} --image-offset ${addressHVAC_default_B3hQTBcl} 
    WORKING_DIRECTORY ${DEPENDENT_TARGET_DIRHVAC_default_B3hQTBcl}
    DEPENDS ${DEPENDENT_DEPENDENT_TARGET_ELFHVAC_default_B3hQTBcl})
add_custom_target(
    dependent_produced_source_artifactHVAC_default_B3hQTBcl 
    DEPENDS ${DEPENDENT_TARGET_DIRHVAC_default_B3hQTBcl}/${sourceFileNameHVAC_default_B3hQTBcl}.c
    )
