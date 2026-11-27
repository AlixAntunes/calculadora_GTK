CC      = gcc
CFLAGS  = $(shell pkg-config --cflags gtk+-3.0) -MMD -MP
LDFLAGS = $(shell pkg-config --libs gtk+-3.0) -lm

TARGET  = calc
OBJS    = calc.o tinyexpr.o

.PHONY  = all clean

all: calc

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(TARGET)
