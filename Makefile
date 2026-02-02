CC = gcc
RM = rm -rfv

CFLAGS +=	\
-Wall		\
-Wextra

RAYFLAGS +=	\
-lraylib	\
-lGL		\
-lm		\
-lpthread	\
-ldl		\
-lrt		\
-lX11


.PHONY: all

all: FirstTry SecondTry

%: %.c
	$(CC) $< -o $@ $(CFLAGS) $(RAYFLAGS)

.PHONY: clean

clean:
	$(RM) main
