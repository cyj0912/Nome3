set(USER "$ENV{USERNAME}")
if (NOT USER)
    set(USER "$ENV{USER}")
endif()

if(WIN32)
    list(APPEND CMAKE_PROGRAM_PATH "D:/Tools")
    list(APPEND CMAKE_PROGRAM_PATH "C:/Users/${USER}/Downloads")
else()
    list(APPEND CMAKE_PREFIX_PATH /usr/local)
    list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/qt)
    list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/flex)
    list(APPEND CMAKE_PREFIX_PATH /usr/local/opt/bison)
    list(APPEND CMAKE_PROGRAM_PATH /usr/local/opt/antlr)

    list(APPEND CMAKE_PREFIX_PATH /Users/${USER}/homebrew)
    list(APPEND CMAKE_PREFIX_PATH /Users/${USER}/homebrew/opt/qt)
    list(APPEND CMAKE_PREFIX_PATH /Users/${USER}/homebrew/opt/flex)
    list(APPEND CMAKE_PREFIX_PATH /Users/${USER}/homebrew/opt/bison)
    list(APPEND CMAKE_PROGRAM_PATH /Users/${USER}/homebrew/opt/antlr)
    
    # For antlr on ubuntu
    list(APPEND CMAKE_PROGRAM_PATH /usr/share/java)
endif()

message(STATUS "Using CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message(STATUS "Using CMAKE_PROGRAM_PATH: ${CMAKE_PROGRAM_PATH}")
