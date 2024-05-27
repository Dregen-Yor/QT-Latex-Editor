function (kate_add_plugin name)
kcoreaddons_add_plugin(${name} INSTALL_NAMESPACE "kf6/ktexteditor")
endfunction()

add_subdirectory(lspclient)