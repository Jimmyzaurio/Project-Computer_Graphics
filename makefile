FUENTES = coordinates.c list.c R3Coord.c vector.c matrix.c colors.c attenuation.c line.c project.c
LIBS = coordinates.o list.o R3Coord.o vector.o matrix.o colors.o attenuation.o line.o project.o

all: $(LIBS)
	@gcc $(LIBS) main.c -o main -lm
	#Es necesario tener instalado converter
	#de lo contrario ejecutar sudo apt-get install imagemagick
	#
	#./main es el ejecutable

$(LIBS) : $(FUENTES)
	@gcc -c $(FUENTES) -lm

clean:
	rm $(LIBS) *.f  main *.ppm
