search_engine.o : search_engine.c search_engine.h
	gcc -c -w -Wall search_engine.c

test.o : Test/test.c Test/test.h Tools/data_handler.h
	gcc -c -w -Wall Test/test.c

data_handler.o : Tools/data_handler.c Tools/data_handler.h
	gcc -c -w -Wall Tools/data_handler.c

main.o : main.c Test/test.h Test/minunit.h search_engine.h Data/constant.h 
	gcc -c -w -Wall main.c

SearchEngine.exe : main.o search_engine.o test.o data_handler.o
	gcc main.o test.o search_engine.o data_handler.o -o SearchEngine.exe
	

