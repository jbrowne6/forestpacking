all: packer packI

packer: packer.cpp forest.*
	g++ -std=c++11 -Wall -Wextra -O3 -g -Werror packer.cpp forest.cpp -o packer
packI: packerInterleaved.cpp forest.*
	g++ -std=c++11 -Wall -Wextra -O3 -g -Werror packerInterleaved.cpp forest.cpp -o packI
