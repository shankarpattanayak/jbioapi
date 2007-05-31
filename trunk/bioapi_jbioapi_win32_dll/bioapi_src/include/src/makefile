GENERATORS = bioapicoref.h bioapif.h
SOURCES = bioapi_api.htp bioapi_spi.htp bioapi_typecast.htp
OUTPUTS = $(SOURCES:.htp=.h)

headers: $(OUTPUTS)

clean:
	rm -f $(OUTPUTS)

.SUFFIXES: .htp .h

.htp.h:
	perl hproc.pl $<
	cp $@ ..

