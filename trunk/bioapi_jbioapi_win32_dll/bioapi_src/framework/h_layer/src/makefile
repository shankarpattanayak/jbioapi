OUTPUT = bioapi_api.c

all: $(TEMPLATES) $(OUTPUT) install clean

install: $(OUTPUT)
	cp $^ ..

clean:
	rm -f $(OUTPUT)

bioapi_api.c: ../bioapi_api.c func.txt ../../../include/bioapi_api.h
	perl service_gen.pl -c../bioapi_api.c -f func.txt -s BIOAPI -o bioapi_api.c
