seccomp1: seccomp1.c
	gcc -Wall seccomp1.c -o seccomp1

seccomp2: seccomp2.c
	gcc -Wall seccomp2.c -o seccomp2 -lseccomp

clean:
	rm -f seccomp1
	rm -f seccomp2
