PROJECTNAME=machineVirtuelle
PRJSRC= $(wildcard *.cpp)
INC= -I ../Librairie
LIBS= -L ../Librairie -lProject
OPTLEVEL=s
####### Cible (Target) #######
#Nom des cibles par defaut
TRG=$(PROJECTNAME).out
include ../Makefile.commun
# Implementation de la cible
$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBS)