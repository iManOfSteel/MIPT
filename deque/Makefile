tests: clean main
	./main
clean:
	rm -f main *.o

start_tests.o:
	g++  -Wall -Wextra -std=c++14 -fexceptions -frtti -c *.cpp

main: *.o /Users/let4ik/Documents/tools/googletest-release-1.8.0/googletest/libgtest.a
	g++ -Wall -Wextra -std=c++14 -lpthread -fexceptions -frtti $^ -o $@
