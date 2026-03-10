# idf_component_register(SRCS "lantern.c" INCLUDE_DIRS ".")

idf_component_register(SRC_DIRS "."
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES neopixel)

