# Nom de la cible du projet
TRG=librobot.a

# Fichiers sources
SRC=$(wildcard *.cpp)

# Insertion du makefile commun
include ./../Makefile_common

# Implementation de la cible
$(TRG): $(OBJDEPS)
	$(LINKER) $(LIBFLAGS) $(TRG) $(OBJDEPS)