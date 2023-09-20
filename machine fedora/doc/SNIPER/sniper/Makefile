# Nom de la cible du projet
TRG=sniper

# Fichiers sources
SRC=$(wildcard *.cpp)

# Chemin vers la librairie
LIBDIR=./../librairie/

# Inclusions additionnels (ex: -I/path/to/mydir)
INC=-I$(LIBDIR)

# Libraires a lier (ex: mylib)
LIBS=-lm $(LIBDIR)library.a

# Insertion du makefile commun
include ./../Makefile_common

# Implementation de la cible
$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) $(INC) $(LIBS)