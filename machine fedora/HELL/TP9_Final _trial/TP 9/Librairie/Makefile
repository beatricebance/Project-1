
PROJECTNAME= libProject
PRJSRC= $(wildcard *.cpp)
INC=
LIBS=
OPTLEVEL=s
####### Cible (Target) #######
#Nom des cibles par defaut
TRG=$(PROJECTNAME).a
include ../Makefile.commun
# Implementation de la cible
$(TRG): $(OBJDEPS)
	ar crs $(TRG) $(OBJDEPS)