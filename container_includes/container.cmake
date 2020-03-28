function(command_library lib_name)
    add_library(infrared.commands.${lib_name} MODULE ${ARGN})
    set_target_properties(infrared.commands.${lib_name} PROPERTIES PREFIX "")
    set_target_properties(infrared.commands.${lib_name} PROPERTIES OUTPUT_NAME "commands.${lib_name}")
    set_target_properties(infrared.commands.${lib_name} PROPERTIES SUFFIX ".dll")
endfunction()