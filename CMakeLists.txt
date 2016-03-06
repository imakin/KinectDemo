add_executable(makin makin.c process.c)
target_link_libraries(makin freenect)
install(TARGETS makin
        DESTINATION howdoimakethisdestionationaffectsomething)
