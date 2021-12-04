# La ruta de tu instalación de clang o g++
CXX =  /usr/bin/g++ -std=c++14

main.exe: d_tree_node.H main.C
	$(CXX) -I. -I../../map/ -I../../dot_H/ main.C -o main.exe

clean:
	$(RM) *~ *.o main.exe
