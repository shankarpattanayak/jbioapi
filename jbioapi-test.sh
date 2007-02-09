echo "Running JBioAPI test program."
test -a Test.class || 'echo "Test program not compiled. Run `./configure && make`" && exit'
java -Djava.security.auth.login.config=jbioapi.jaas.config -Djava.library.path=src/.libs/ Test
