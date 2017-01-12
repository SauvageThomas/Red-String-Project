#  $@ 	target name
#  $< 	name of the first dependancy
#  $^ 	dependancy list
#  $? 	La liste des dépendances plus récentes que la cible
#  $* 	Le nom du fichier sans suffixe

.PHONY: clean, mrproper

CC=gcc
CFLAGS=-c -w -Wall -g -std=gnu99
LDFLAGS=
EXEC=SearchEngine.exe

all: $(EXEC)

SearchEngine.exe: hash_map.o descriptor_generator.o index_generator.o data_manager.o report.o search_engine.o test.o data_handler.o main.o text_finder.o image_finder.o sound_finder.o gui.o functions.o
	$(CC)   $^ -lm -o ../$@ 

descriptor_generator.o : Descriptor/descriptor_generator.c Descriptor/descriptor_generator.h
	$(CC) $(CFLAGS) $< 

index_generator.o : Descriptor/index_generator.c Descriptor/index_generator.h
	$(CC) $(CFLAGS) $< 

data_manager.o : Search/data_manager.c Search/data_manager.h Tools/report.h Tools/data_handler.h Search/text_finder.h Search/image_finder.h Search/sound_finder.h
	$(CC) $(CFLAGS) $< 

report.o : Tools/report.c Tools/report.h
	$(CC) $(CFLAGS) $< 

text_finder.o : Search/text_finder.c Search/text_finder.h Tools/data_handler.h
	$(CC) $(CFLAGS) $< 

image_finder.o : Search/image_finder.c Search/image_finder.h Tools/data_handler.h
	$(CC) $(CFLAGS) $< 

sound_finder.o : Search/sound_finder.c Search/sound_finder.h Tools/data_handler.h
	$(CC) $(CFLAGS) $< 

search_engine.o : search_engine.c search_engine.h Tools/report.h Search/data_manager.h Descriptor/index_generator.h Descriptor/descriptor_generator.h GUI/gui.h
	$(CC) $(CFLAGS) $< 

test.o : Test/test.c Test/test.h Tools/data_handler.h
	$(CC) $(CFLAGS) $< 

data_handler.o : Tools/data_handler.c Tools/data_handler.h
	$(CC) $(CFLAGS) $< 

gui.o : GUI/gui.c GUI/gui.h
	$(CC) $(CFLAGS) $< 

hash_map.o : Tools/hash_map.c Tools/hash_map.h
	$(CC) $(CFLAGS) $< 

functions.o : GUI/functions.c GUI/functions.h Data/constant.h Tools/report.h Tools/data_handler.h Search/data_manager.h Search/text_finder.h Search/image_finder.h Search/sound_finder.h
	$(CC) $(CFLAGS) $<

main.o : main.c Test/test.h Test/minunit.h search_engine.h Data/constant.h GUI/gui.h
	$(CC) $(CFLAGS) $<
	
clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
