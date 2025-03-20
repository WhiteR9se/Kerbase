all:
	g++ -Wall -Wextra -O2 -g server.cpp -o server
	g++ -Wall -Wextra -O2 -g client.cpp -o client
clean:
	rm -rf server
	rm -rf client
