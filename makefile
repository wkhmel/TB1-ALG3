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

all: $(MAIN)

# construir os arquivos-objeto 
$(MAIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJ) $(LDLIBS)

# construir os TADs
fila.o: fila.c fila.h
arvoreB.o: arvoreB.c arvoreB.h

# executar
run: $(MAIN)
	./$(MAIN)

# testar no Valgrind
valgrind: $(MAIN)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(MAIN)

# gerar arquivo TGZ para entregar
tgz: clean
	mkdir -p /tmp/$(USER)/$(ENTREGA)
	chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h Makefile /tmp/$(USER)/$(ENTREGA) 2>/dev/null || cp *.c *.h makefile /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

# Limpar arquivos temporários
clean:
	rm -f $(OBJ) $(MAIN) $(ENTREGA).tgz *~
