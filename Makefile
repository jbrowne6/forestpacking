all: packer packI

packer: packer.cpp
	g++ -std=c++11 -Wall -Wextra -O3 -g -Werror packer.cpp -o packer
packI: packerInterleaved.cpp
	g++ -std=c++11 -Wall -Wextra -O3 -g -Werror packerInterleaved.cpp -o packI
