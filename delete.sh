rm test csvreader.o yolo.xml

g++ -c csvreader.cpp

g++ -o test csvreader.o tinyxml2.o

./test

nano yolo.xml
