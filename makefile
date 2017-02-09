#  $@ 	target name
#  $< 	name of the first dependancy
#  $^ 	dependancy list
#  $? 	La liste des dépendances plus récentes que la cible
#  $* 	Le nom du fichier sans suffixe

.PHONY: clean, mrproper

# Compilation
CC=gcc
JNI= -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux
CFLAGS= $(JNI) -c -w -Wall -g -std=gnu99 $(<) -o $(@)
EXEC=release/SearchEngine.exe

# Directories
M=src/Kernel/
V=src/Console/
C=src/Controller/
R=release/
DESC=$(M)Descriptor/
TOOL=$(M)Tools/
SEARCH=$(M)Search/
TEST=$(M)Test/
DATA=$(M)Data/

# Code files
igen=index_generator
gen=descriptor_generator
tgen=text_descriptor_generator
imgen=image_descriptor_generator
sgen=sound_descriptor_generator

dm=data_manager
tf=text_finder
if=image_finder
sf=sound_finder

dh=data_handler
map=hash_map
mm=map_of_map
re=report
th=text_handler

t=test


# Exec file
all: $(EXEC)


clean:
	rm -rf $(R)*.o

mrproper: clean
	rm -rf $(EXEC)


$(EXEC): $(R)$(gen).o $(R)$(igen).o $(R)$(tgen).o $(R)$(imgen).o $(R)$(sgen).o $(R)$(dm).o $(R)$(tf).o $(R)$(if).o $(R)$(sf).o $(R)$(dh).o $(R)$(mm).o $(R)$(map).o $(R)$(re).o $(R)$(t).o $(R)main.o $(R)gui.o $(R)functions.o
	$(CC)   $^ -lm -o $@ 


#####################
# Descriptor Module #
#####################

$(R)$(gen).o : $(DESC)$(gen).c $(DESC)$(gen).h
	$(CC) $(CFLAGS)

$(R)$(tgen).o : $(DESC)$(tgen).c $(DESC)$(tgen).h $(DESC)$(gen).h 
	$(CC) $(CFLAGS)

$(R)$(imgen).o : $(DESC)$(imgen).c $(DESC)$(imgen).h $(DESC)$(gen).h
	$(CC) $(CFLAGS)

$(R)$(sgen).o : $(DESC)$(sgen).c $(DESC)$(sgen).h $(DESC)$(gen).h
	$(CC) $(CFLAGS)

$(R)$(igen).o : $(DESC)$(igen).c $(DESC)$(igen).h
	$(CC) $(CFLAGS) 


#################
# Search Module #
#################

$(R)$(dm).o : $(SEARCH)$(dm).c $(SEARCH)$(dm).h $(TOOL)report.h $(TOOL)$(dh).h $(SEARCH)$(tf).h $(SEARCH)$(if).h $(SEARCH)$(sf).h
	$(CC) $(CFLAGS)

$(R)$(tf).o : $(SEARCH)$(tf).c $(SEARCH)$(tf).h $(TOOL)$(dh).h
	$(CC) $(CFLAGS)

$(R)$(if).o : $(SEARCH)$(if).c $(SEARCH)$(if).h $(TOOL)$(dh).h
	$(CC) $(CFLAGS)

$(R)$(sf).o : $(SEARCH)$(sf).c $(SEARCH)$(sf).h $(TOOL)$(dh).h
	$(CC) $(CFLAGS)


################
# Tools Module #
################

$(R)$(dh).o : $(TOOL)$(dh).c $(TOOL)$(dh).h
	$(CC) $(CFLAGS)

$(R)$(map).o : $(TOOL)$(map).c $(TOOL)$(map).h
	$(CC) $(CFLAGS)

$(R)$(mm).o : $(TOOL)$(mm).c $(TOOL)$(dh).h $(TOOL)$(mm).h $(TOOL)$(map).h
	$(CC) $(CFLAGS)

$(R)$(re).o : $(TOOL)$(re).c $(TOOL)$(re).h
	$(CC) $(CFLAGS) 


###############
# Test Module #
###############

$(R)$(t).o : $(TEST)$(t).c $(TEST)$(t).h $(TOOL)$(dh).h
	$(CC) $(CFLAGS)




########
# View #
########

$(R)gui.o : $(V)/gui.c $(V)/gui.h
	$(CC) $(CFLAGS)

$(R)main.o : $(V)main.c $(TEST)$(t).h $(TEST)minunit.h $(DATA)constant.h $(V)gui.h
	
	$(CC) $(CFLAGS)


##############
# Controller #
##############

$(R)functions.o : $(C)functions.c $(C)functions.h $(DATA)constant.h $(TOOL)$(re).h $(TOOL)$(dh).h $(SEARCH)$(dm).h $(SEARCH)$(tf).h $(SEARCH)$(if).h $(SEARCH)$(sf).h
	$(CC) -fPIC $(CFLAGS)
	
libkernel.so : $(R)functions.o
	$(CC) -shared -o libkernel.so $(R)functions.o
	
	
