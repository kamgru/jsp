add_library(jsp
        Scanner.cpp
        Cursor.cpp ../test/Doctest.h)

add_compile_options(jsp PRIVATE -Wall)