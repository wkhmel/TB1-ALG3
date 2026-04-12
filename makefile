# makefile ArvoreB

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -std=c99
LDLIBS  = -lm
MAIN    = arvoremain
ENTREGA = $(MAIN)

# lista de arquivos de cabeçalho 
HDR = arvoreB.h fila.h

# lista de arquivos-objeto
OBJ = fila.o arvoreB.o

# construir os arquivos-objeto 
$(MAIN).o: $(MAIN).c $(HDR)

# construir os TADs
fila.o: fila.c fila.h
arvoreB.o: arvoreB.c arvoreB.h

# executar
run: $(MAIN)
	./$(MAIN)

# testar no Valgrind
valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)

# gerar arquivo TGZ para entregar
tgz: clean
	-mkdir -p /tmp/$(USER)/$(ENTREGA)
	chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h makefile /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

# limpar arquivos temporários
clean:
	rm -f *~ $(OBJ) $(MAIN) /tmp/$(USER)/$(ENTREGA) $(ENTREGA).tgz
