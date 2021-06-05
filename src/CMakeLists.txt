add_library(jsp
        Scanner.cpp
        Cursor.cpp
        Parser.cpp
        JObject.cpp
        JArray.cpp)

add_compile_options(jsp PRIVATE -Wall)