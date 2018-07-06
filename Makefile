CC = gcc
CFLAGS = -Wall -std=c99 -O3


EXE = atkin

LIBS =

HDRS = src/sieve.h src/atkin.h
SRCS = src/sieve.c src/atkin.c src/main.c
OBJS = $(SRCS:.c=.o)


.PHONY += all

all: clean $(EXE)


.PHONY += debug

debug: CFLAGS += -O0
debug: CFLAGS += -g -ggdb -DDEBUG
debug: all


$(EXE): $(HDRS) $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

$(OBJS): $(HDRS) $(SRCS) Makefile


.PHONY += test

test: all requirements.txt
	virtualenv -p python3 .venv \
		&& . .venv/bin/activate \
		&& pip install -r requirements.txt \
		&& pytest test \
		&& deactivate \
		&& $(RM) -r .venv


.PHONY += clean

clean:
	$(RM) $(OBJS) $(EXE)
