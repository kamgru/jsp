add_library(jsp
        ../include/jsp.h
        Scanner.cpp
        Cursor.cpp
        Parser.cpp JObject.cpp JArray.cpp)

add_compile_options(jsp PRIVATE -Wall)