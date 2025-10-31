# CMakeList.txt: arquivo de projeto de CMake de nível superior, fazer configuração global
# e possibilita incluir subprojetos aqui.

cmake_minimum_required (VERSION 3.8)

# Habilite a Recarga Dinâmica para compiladores MSVC, se houver suporte.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Projeto primário.

project ("algoritmos_avancados")

# Inclua subprojetos, se desejar.

# add_subdirectory ("algoritmos_avancados")

# Executáveis.
add_executable(algoritmos_avancados_novato "algoritmos_avancados_novato.c")
add_executable(algoritmos_avancados_aventureiro "algoritmos_avancados_aventureiro.c")
add_executable(algoritmos_avancados_mestre "algoritmos_avancados_mestre.c")

# Configuração de Warnings, etc.
foreach(target algoritmos_avancados_novato algoritmos_avancados_aventureiro algoritmos_avancados_mestre)
    if(MSVC)
        target_compile_options(${target} PRIVATE
            /W3          # Warning level 3
            /wd4996      # Desabilita warning de funções deprecated
            /WX-         # Não trata warnings como erros            
        )
    else()
        target_compile_options(${target} PRIVATE
            -Wall
            -Wextra
            -Wno-unused-parameter
            -Wno-unused-variable
            -Werror       # Warnings como erros
        )
    endif()
endforeach()

