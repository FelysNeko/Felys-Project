cc = clang
extension = c
build = build
output = felys

source = $(wildcard *.$(extension))
objects = $(patsubst %.$(extension),$(build)/%.o,$(source))

all: dir $(output)

dir:
ifneq ($(wildcard $(build)), $(build))
	mkdir -p $(build)
endif

$(output): $(objects)
	$(cc) -o $@ $^ 

$(objects): $(build)/%.o: %.$(extension)
	$(cc) -o $@ -c $< 

clean:
	rm -rf $(build) $(output)
