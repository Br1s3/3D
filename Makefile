CC = gcc
RM = rm -rfv
EXEC +=		\
3DSquare_Zfix	\
3DSquare 	\
SecondTry

CFLAGS +=	\
-Wall		\
-Wextra 	\
-g3

RAYFLAGS +=	\
-lraylib	\
-lGL		\
-lm		\
-lpthread	\
-ldl		\
-lrt		\
-lX11


.PHONY: all

all: $(EXEC)

%: %.c libgraph.h
	$(CC) $< -o $@ $(CFLAGS) $(RAYFLAGS)

.PHONY: clean

clean:
	$(RM) $(EXEC)
