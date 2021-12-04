# La ruta de tu instalación de clang o g++
CXX =  /usr/bin/g++ -std=c++14

pvc_game.exe: 
	$(CXX) -I. -I../map/ -I../dot_H/ -I../skyline/decision_tree/ -I../skyline/skyline_H  pvc_game.C -o pvc_game.exe
	
clean:
	$(RM) *~ *.o pvc_game.exe 
