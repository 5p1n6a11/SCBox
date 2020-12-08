seccomp1: seccomp1.c
	gcc -Wall $< -o $@

seccomp2: seccomp2.c
	gcc -Wall $< -o $@ -lseccomp

clean:
	rm -f seccomp1
	rm -f seccomp2
