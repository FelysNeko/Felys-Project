CC = clang
BUILD = build
OUTPUT = felys

SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,$(BUILD)/%.o,$(SOURCES))

all: dir $(OUTPUT)

dir:
ifneq ($(wildcard $(BUILD)), $(BUILD))
	mkdir -p $(BUILD)
endif

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^ 

$(OBJECTS): $(BUILD)/%.o: %.c
	$(CC) -o $@ -c $< 

clean:
	rm -rf $(BUILD) $(OUTPUT)