add_executable(makin 
				main.c 
				process.c
				util.c
				classes/landmark.c
				classes/ransac.c
				classes/state.c
			)
target_link_libraries(makin m) #link with math.h library
target_link_libraries(makin freenect)
install(TARGETS makin
        DESTINATION howdoimakethisdestionationaffectsomething)
