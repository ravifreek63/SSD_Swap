all: main

main: PageBuffer.cpp SwapReader.cpp SwapWriter.cpp SwapManager.cpp SSDSwap.cpp Main.cpp  
	g++ -g -std=c++0x -o main PageBuffer.cpp SwapReader.cpp SwapWriter.cpp SwapManager.cpp SSDSwap.cpp  Main.cpp 
	
clean: 
	rm -f main

run:
	./main
