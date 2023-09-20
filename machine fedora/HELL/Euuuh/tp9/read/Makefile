########       AVR Project Makefile       ########
#####                                        #####
#####      Makefile produit et ecrit par     #####
#####   Simon Barrette & Jerome Collin pour  #####
#####           INF1900 - 2016               #####
#####                                        #####
#####         Inspire de Pat Deegan -        #####
#####  Psychogenic Inc (www.psychogenic.com) #####
##################################################

# Ce Makefile vous permet de compiler des projets
# pour les microcontroleurs Atmel AVR sur 
# Linux ou Unix, en utilisant l'outil AVR-GCC. 
# Ce Makefile supporte C & C++

include ../Makefile_commun

#####      Details specifique a la cible       #####

# Nom de votre projet
# (utilisez un seul mot, exemple: 'monprojet')
PROJECTNAME=exec

# Fichiers sources
# Utilisez le suffixe .cpp pour les fichiers C++
# Listez tous les fichiers a compiler, separes par
# un espace. exemple: 'tp1.c tp2.cpp':
PRJSRC=interpret.cpp

# Inclusions additionnels (ex: -I/path/to/mydir)
INC= -I $(LIBDIR)

# Libraires a lier (ex: -lmylib)
LIBS= -l complete -L $(LIBDIR)

####################################################
#####         Configuration terminee           #####
#####                                          #####
#####  Le reste de cette section contient les  #####
##### details d'implementation vous permettant #####
##### de mieux comprendre le fonctionnement de ##### 
#####   ce Makefile en vue de sa modification  #####
####################################################


####### Options de compilation #######
## Les Options de compilation utilisees sont dans le makefile commun 

####### variables #######
## Les variables utilisees sont dans le makefile commun 

####### Cible (Target) #######

#Nom des cibles 
TRG=$(PROJECTNAME).out
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex

####### Creation des commandes du Makefile ####### 


# Make all permet simplement de compiler le projet
#
all: $(TRG)

# Implementation de la cible
$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBS)

# Make debug créera l'exécutable en mode debug 
# contrairement à all qui le fera en mode release
debug: CXXFLAGS += -DDEBUG -g
debug: CFLAGS += -DDEBUG -g
debug: $(TRG)

# Make install permet de compiler le projet puis
# d'ecrire le programme en memoire flash dans votre
# microcontroleur. Celui-ci doit etre branche par cable USB
install: $(HEXROMTRG)				
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID)   \
	-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)

#Make clean permet d'effacer tout les fichiers generes
# lors de la compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d

# Pour plus d'information sur cette section, consulter:
# http://bit.ly/2580FU8


# Pour plus d'information sur les phony target, consulter:
# http://bit.ly/1WBQe61

# De plus, pour mieux comprendre les makefiles et 
# leur fonctionnement, consulter la documentation de GNU Make:
# http://bit.ly/23Vpk8s

# Finalement, ce tutoriel en ligne constitut une bonne 
# introduction au Makefile:
# http://bit.ly/1XvxsN3

#####                    EOF                   #####
