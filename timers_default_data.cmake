#Maybe some defines for frequency: everyday, every2days...
# Maybe also allow a null value for time and an arbitrary frequency in hours

add_compile_definitions(DRIP_WATER_TIME_OF_DAY="22:0:0")
add_compile_definitions(DRIP_WATER_EVERY_X_DAYS="2")	# "0" for no timed-on
add_compile_definitions(DRIP_WATER_DURATION_SEC="120")

add_compile_definitions(DRIP_LIGHTS_TIME_OF_DAY="23:0:0")
add_compile_definitions(DRIP_LIGHTS_EVERY_X_DAYS="1")	# "0" for no timed-on
add_compile_definitions(DRIP_LIGHTS_DURATION_SEC="18000")
