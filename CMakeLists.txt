# IMPORTANT: For this to work, this requirements must be meet:
#	* The PICO_SDK_PATH exists and points to the root directory
#	of the C/C++ SDK (cloned from a Raspberry Pi repository).
#	* The "pico_sdk_import.cmake" file is in the same directory
#	as this file. This file is standard from Raspberry Pi and
#	may be copied from the $PICO_SDK_PATH/external path.
#

# This works. I'm doing this instead of running cmake
# like: "cmake .. -DPICO_BOARD=pico_w". The same will be done
# below to avoid writing everytime the WLAN options
set(PICO_BOARD pico_w)

# Here I'll include the SSID and passphrase for the network
# Similar to what was done above with the board, to avoid passing
# -DWIFI_SSID="Your Network" -DWIFI_PASSWORD="Your Password"
# everytime. But for security reasons the declaration of the
# variables is done in another file which won't be pushed to
# the repository.
#
# The "wlan_setup_data.cmake" file must be created in the same
# directory as this file and its content should be:
# NOOOOOO	set(WIFI_SSID "Your Network")
# NOOOOOO	set(WIFI_PASSWORD "Your Password")
# The above won't pass them as macro definitions to the compiler.
# Instead this should do the trick:
# add_compile_definitions(WIFI_SSID=Your_Network)
# add_compile_definitions(WIFI_PASSWORD=Your_Password)
include(wlan_setup_data.cmake)


# File with the default timers parameters.
include(timers_default_data.cmake)

string(TIMESTAMP BUILD_TIME "%Y:%m:%d:%w:%H:%M:%S")
add_compile_definitions(DRIP_BUILD_TIME=\"${BUILD_TIME}\")

# WARNING!!! Statments order MATTERS!!!

# Standard cmake mandatory
cmake_minimum_required(VERSION 3.10)

# Copied from ~/pico/pico-sdk/external/pico_sdk_import.cmake
# This and the existence of the PICO_SDK_PATH shell variable
# is what will connect our project to the SDK when building
include(pico_sdk_import.cmake)

# CMake mandatory: the name of the project.
project(drip_irrigation_controller)

# This refer to the language standard both for C and C++
# whose features are required to build this target.
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# No idea what this does exactly...
# "It sets up the build environment, including toolchain configuration,
# and prepares the SDK for use by your project."
# "[It] acts as a bridge between your project and the Raspberry Pi Pico
# SDK, ensuring that everything is set up correctly for building
# your code"
pico_sdk_init()

# This tells the source files that must be compiled to build
# the binary (called 'drip' here).
# Placing header files here makes no difference but some IDEs
# do it to list all the files of the project.
add_executable(drip
	src/main.c
	src/drip_conf_load_settings.c
	src/drip_conf_set_next_timeofday_alarm.c
	src/drip_conf_enforce_settings.c
	src/drip_conf_print_settings.c
	src/drip_wifi_init.c
	src/drip_wifi_set_ip4_addr.c
	src/drip_wifi_print_pbufchain.c
	src/drip_wifi_recv_callback.c
	src/drip_wifi_udp_server_init.c
	src/drip_io_init.c
	src/drip_rtc_init.c
	src/drip_rtc_datetime_print.c
	src/drip_rtc_str2datetime.c
	src/drip_exe_client_request.c
	src/drip_exe_water_timed_on.c
	src/drip_exe_lights_timed_on.c
	src/drip_time_utils.c
)

message("[lluque CMakeLists] Some information:")
message(STATUS "CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "BUILD_TIME: ${BUILD_TIME}")

# HERE THE COMPONENT SPECIFIC CMAKE FUNCTIONS

# So far to get USB serial for debugging purposes
pico_enable_stdio_usb(drip ENABLED)

# Enabled by default (I think), not used.
#pico_enable_stdio_uart(drip DISABLED)

# This tells the compiler to look for headers in the same directory
# the CMakeLists.txt is.
target_include_directories(drip PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/include)


# HERE THE COMPONENT SPECIFIC CMAKE FUNCTIONS







# This builds more output files: uf2, assembler, etc.
# Without it only a .elf is compiled.
pico_add_extra_outputs(drip)

# This links to the resulting binary (e.g. drip) the indicated
# libraries (e.g. pico_stdlib)
# The pico_stdlib library agregates:
#   * hardware_divider
#   * hardware_gpio
#   * hardware_uart
#   * pico_runtime
#   * pico_platform
#   * pico_stdio
#   * pico_time
#   * pico_util
# The cyw43 so far is to use the pico_w on-board LED which is controlled
# by the wifi chip.
target_link_libraries(drip
	pico_stdlib
	hardware_rtc
	pico_cyw43_arch_lwip_poll)		# The traditional polling option
#pico_cyw43_arch_lwip_threadsafe_background)	# With interrupts
