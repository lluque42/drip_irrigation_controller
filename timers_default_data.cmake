#Maybe some defines for frequency: everyday, every2days...
# Maybe also allow a null value for time and an arbitrary frequency in hours

add_compile_definitions(DRIP_WATER_TIME_OF_DAY="09:50:00")
add_compile_definitions(DRIP_WATER_EVERY_X_DAYS="2")	# "0" for no timed-on
add_compile_definitions(DRIP_WATER_DURATION_SEC="3")

add_compile_definitions(DRIP_LIGHTS_TIME_OF_DAY="09:50:30")
add_compile_definitions(DRIP_LIGHTS_EVERY_X_DAYS="4")	# "0" for no timed-on
add_compile_definitions(DRIP_LIGHTS_DURATION_SEC="5")
