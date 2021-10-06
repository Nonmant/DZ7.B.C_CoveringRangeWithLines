#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<"1\n"
                  "-1 0\n"
                  "-5 -3\n"
                  "2 5\n"
                  "0 0\n";
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();
    
    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    REQUIRE(buffer.str() == "No solution\n");
}

TEST_CASE("test 2", ""){
    std::stringstream input, output;
    input<<"1\n"
           "-1 0\n"
           "0 1\n"
           "0 0";
    parseFile(input,output);
    REQUIRE(output.str() == "1\n"
                            "0 1\n");
}

TEST_CASE("test all", ""){
    std::stringstream input, output;
    input<<"8\n"
           "-2 -1\n"
           "-1 0\n"
           "-3 5\n"
           "-1 1\n"
           "4 8\n"
           "5 7\n"
           "7 10\n"
           "10 12\n"
           "0 0";
    parseFile(input,output);
    REQUIRE(output.str() == "2\n"
                            "-3 5\n"
                            "4 8\n");
}

TEST_CASE("one, overlap", ""){
    std::stringstream input, output;
    input<<"1\n"
           "-1 2\n"
           "0 0";
    parseFile(input,output);
    REQUIRE(output.str() == "1\n"
                            "-1 2\n");
}

TEST_CASE("switch in the middle", ""){
    std::stringstream input, output;
    input<<"3\n"
           "-1 1\n"
           "1 4\n"
           "2 5\n"
           "0 0";
    parseFile(input,output);
    REQUIRE(output.str() == "2\n"
                            "-1 1\n"
                            "1 4\n");
}

TEST_CASE("gap in the middle", ""){
    std::stringstream input, output;
    input<<"4\n"
           "-1 2\n"
           "1 2\n"
           "3 5\n"
           "0 0";
    parseFile(input,output);
    REQUIRE(output.str() == "No solution\n");
}

TEST_CASE("overlap and another line with the same end", ""){
    std::stringstream input, output;
    input<<"2\n"
           "-1 3\n"
           "1 3\n"
           "0 0";
    parseFile(input,output);
    REQUIRE(output.str() == "1\n"
                            "-1 3\n");
}

TEST_CASE("overlap and another line with the same end, reverse order", ""){
    std::stringstream input, output;
    input<<"2\n"
           "1 3\n"
           "-1 3\n"
           "0 0";
    parseFile(input,output);
    REQUIRE(output.str() == "1\n"
                            "-1 3\n");
}

TEST_CASE("switch in the middle another line with the same end", ""){
    std::stringstream input, output;
    input<<"3\n"
           "-1 2\n"
           "1 2\n"
           "2 4\n"
           "0 0";
    parseFile(input,output);
    REQUIRE(output.str() == "2\n"
                            "-1 2\n"
                            "2 4\n"
                            );
}

TEST_CASE("switch in the middle, another line end more than range", ""){
    std::stringstream input, output;
    input<<"2\n"
           "0 1\n"
           "1 3\n"
           "0 0";
    parseFile(input,output);
    REQUIRE(output.str() == "2\n"
                            "0 1\n"
                            "1 3\n"
                            );
}

TEST_CASE("Gap at the start", ""){
    std::stringstream input, output;
    input<<"3\n"
           "2 3\n"
           "1 2\n"
           "0 0";
    parseFile(input,output);
    REQUIRE(output.str() == "No solution\n"
                            );
}

TEST_CASE("Gap at the end", ""){
    std::stringstream input, output;
    input<<"2\n"
           "0 1\n"
           "0 0";
    parseFile(input,output);
    REQUIRE(output.str() == "No solution\n"
                           );
}

TEST_CASE("Overlap and 2 smaller", ""){
    std::stringstream input, output;
    input<<"2\n"
           "0 1\n"
           "1 2\n"
           "-1 3\n"
           "0 0";
    parseFile(input,output);
    REQUIRE(output.str() == "1\n"
                            "-1 3\n"
                           );
}
