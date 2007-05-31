SOURCE = bioapif.c
FUNCTIONS = bioapi_dummy_addini.c
ERROR_HEADERS = bioapi_dummy_addini_err.h

all: $(SOURCE) $(FUNCTIONS) $(ERROR_HEADERS)

install: $(FUNCTIONS) $(ERROR_HEADERS)
	cp $^ ..

clean:
	rm -f $(SOURCE)
	rm -f $(ERROR_HEADERS)
	rm -f $(FUNCTIONS)

bioapi_dummy_addini.c: bioapif.c

bioapif.c: ../../../include/src/bioapif.h
	perl update_funcs.pl $<

.SUFFIXES: .h .htp .c .ctp

.ctp.c:
	perl template_proc.pl $<

.htp.h:
	perl template_proc.pl $<
