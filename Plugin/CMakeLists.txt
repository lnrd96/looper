add_subdirectory(Looper)

# Option to enable or disable logging
option(ENABLE_LOGGING "Enable logging functionality" ON)

# Variable to specify log directory. If not specified, default to some directory.
set(LOG_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/Logfiles" CACHE STRING "Directory to store log files" FORCE)

