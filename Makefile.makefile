all:
	g++ curl.cpp -o curl -lcurl
	g++ text.cpp -o text
clean:
	rm -rf *.o curl
