CC = gcc
RM = rm -rfv

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

all: FirstTry SecondTry ThirdTry

%: %.c
	$(CC) $< -o $@ $(CFLAGS) $(RAYFLAGS)

.PHONY: clean

clean:
	$(RM) main
