FILE(GLOB CSources *.c)

idf_component_register(SRCS ${CSources}
                    INCLUDE_DIRS ".")

