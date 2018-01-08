all: packer packI

packer: packer.cpp forest.h
	g++ -std=c++11 -Wall -Wextra -O3 -g -Werror packer.cpp forest.cpp -o packer
packI: packerInterleaved.cpp forest.h
	g++ -std=c++11 -Wall -Wextra -O3 -g -Werror packerInterleaved.cpp -o packI
