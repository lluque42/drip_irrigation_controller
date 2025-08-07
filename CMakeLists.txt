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
# set(WIFI_SSID "Your Network")
# set(WIFI_PASSWORD "Your Password")
include(wlan_setup_data.cmake)

# Standard cmake mandatory
cmake_minimum_required(VERSION 3.10)

# Copied from ~/pico/pico-sdk/external/pico_sdk_import.cmake
# This and the existence of the PICO_SDK_PATH shell variable
# is what will connect our project to the SDK when building
include(pico_sdk_import.cmake)

project(drip_irrigation_controller)

# This refer to the language standard both for C and C++
# whose features are required to build this target.
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(drip main.c)

pico_add_extra_outputs(drip)

target_link_libraries(drip pico_stdlib)
