.PHONY: clean, mrproper

all: descriptor_generator.o index_generator.o data_finder.o report.o search_engine.o test.o data_handler.o main.o 
	gcc main.o report.o index_generator.o descriptor_generator.o data_finder.o test.o search_engine.o data_handler.o -o SearchEngine.exe
descriptor_generator.o : Descriptor/descriptor_generator.c Descriptor/descriptor_generator.h
	gcc -c -w -Wall Descriptor/descriptor_generator.c

index_generator.o : Descriptor/index_generator.c Descriptor/index_generator.h
	gcc -c -w -Wall Descriptor/index_generator.c

data_finder.o : Search/data_finder.c Search/data_finder.h Tools/report.h Tools/data_handler.h
	gcc -c -w -Wall Search/data_finder.c

report.o : Tools/report.c Tools/report.h
	gcc -c -w -Wall Tools/report.c

search_engine.o : search_engine.c search_engine.h Tools/report.h Search/data_finder.h Descriptor/index_generator.h Descriptor/descriptor_generator.h
	gcc -c -w -Wall search_engine.c

test.o : Test/test.c Test/test.h Tools/data_handler.h
	gcc -c -w -Wall Test/test.c

data_handler.o : Tools/data_handler.c Tools/data_handler.h
	gcc -c -w -Wall Tools/data_handler.c

main.o : main.c Test/test.h Test/minunit.h search_engine.h Data/constant.h 
	gcc -c -w -Wall main.c
	
clean:
	rm -rf *.o

mrproper: clean
	rm -rf *.exe
