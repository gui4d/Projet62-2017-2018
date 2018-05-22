CFLAGS=-W -Wall -O6 #compilation : creation de .o
LDFLAGS=-L/usr/lib/arm-linux-gnueabihf -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lfreenect_sync #operation de linkage 

SlotTrack.exe: Collision.o CreationRelief.o FonctionsGenerales.o GestionEvent.o GestionInstruction.o GestionMenus.o GestionMusique.o GestionVoiture.o InitialisationEtFin.o JeuCerise.o JeuCourse.o JeuPriseFlag.o main.o Modelisation.o ObtenirCouleur.o traitement.o calibrage.o matrice.o acquisition.o
	gcc $^ -o SlotTrack.exe $(CFLAGS) $(LDFLAGS) -lm

%.o: %.c 
	gcc -c $^ $(CFLAGS) -lm

clean:
	rm -rf *.o
