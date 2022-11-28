cmake_minimum_required(VERSION 3.23)
project(Calculator)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        Calculator
        main.cpp

        include/lib/Array/Array.h
        include/lib/Array/array_iterator.h
        include/lib/CharacterSet.h
        include/lib/StringManager.h
        include/lib/Dictionary.h
        include/Ace.h
        include/Literals/Parser.h
        include/Expression/Parser.h
        include/Expression/Node.h
        include/Lexer/Parser.h
        include/Lexer/Token.h
        include/Interpretator/Interpretator.h src/Interpretator/Interpretator.cpp
        include/SourceManager/SourceManager.h
        include/lib/FileManager.h
        include/Calculator/Calculator.h

        src/lib/CharacterSet.cpp
        src/Ace.cpp
        src/Literals/Parser.cpp
        src/Expression/Parser.cpp
        src/Lexer/Parser.cpp
        src/Lexer/Token.cpp
        src/SourceManager/SourceManager.cpp
        src/Calculator/Calculator.cpp
        src/lib/FileManager.cpp
)

add_executable(
        Calculator_tests
        Calculator_tests/main.cpp

        Calculator_tests/Calculator_tests.h
        include/lib/Array/Array.h
        include/lib/Array/array_iterator.h
        include/lib/CharacterSet.h
        include/lib/StringManager.h
        include/lib/Dictionary.h
        include/Ace.h
        include/Literals/Parser.h
        include/Expression/Parser.h
        include/Expression/Node.h
        include/Lexer/Parser.h
        include/Lexer/Token.h
        include/Interpretator/Interpretator.h src/Interpretator/Interpretator.cpp
        include/SourceManager/SourceManager.h
        include/lib/FileManager.h
        include/Calculator/Calculator.h

        src/lib/CharacterSet.cpp
        src/Ace.cpp
        src/Literals/Parser.cpp
        src/Expression/Parser.cpp
        src/Lexer/Parser.cpp
        src/Lexer/Token.cpp
        src/SourceManager/SourceManager.cpp
        src/Calculator/Calculator.cpp
        src/lib/FileManager.cpp
)