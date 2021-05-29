add_library(jsp
        Lexer.cpp
        Cursor.cpp ../test/Doctest.h)

add_compile_options(jsp PRIVATE -Wall)