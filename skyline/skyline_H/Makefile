# La ruta de tu instalación de clang o g++
CXX =  /usr/bin/g++ -std=c++14

skyline_test.exe: 
	$(CXX) -I. -I../../map/ -I../../dot_H/ -I../decision_tree skyline_test.C -o skyline_test.exe

clean:
	$(RM) *~ *.o 
