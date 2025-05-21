# Nome dell'eseguibile
TARGET = programma

# Compilatore
CC = gcc

# Opzioni di compilazione
CFLAGS = -Wall -g

# File sorgente
SRCS = main.c lista.c attivita_studio.c

# File oggetto (derivati dai sorgenti)
OBJS = $(SRCS:.c=.o)

# Regola di default per costruire il programma
all: $(TARGET)

# Regola per costruire l'eseguibile
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regola per compilare i file .c in .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Pulisce i file generati
clean:
	rm -f $(OBJS) $(TARGET)

# Pulisce i file temporanei di backup
mrproper: clean
	rm -f *~ *.bak
