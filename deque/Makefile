
clean:
	rm -f main.o main

start_tests.o:
	g++  -Wall -Wextra -std=c++14 -fexceptions -frtti -c start_tests.cpp

test_cases_1.o:
	g++  -Wall -Wextra -std=c++14 -fexceptions -frtti -c test_cases_1.cpp

main: start_tests.o test_cases_1.o /Users/let4ik/Documents/tools/googletest-release-1.8.0/googletest/libgtest.a
	g++ -Wall -Wextra -std=c++14 -lpthread -fexceptions -frtti $^ -o $@

tests: clean main
	./main