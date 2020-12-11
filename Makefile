seccomp1: seccomp1.c
	gcc -Wall $< -o $@

seccomp2: seccomp2.c
	gcc -Wall $< -o $@ -lseccomp

01-nothing: 01-nothing.c
	gcc $< -o $@ && ./$@; echo "Status: $$?"

02-bpf-only-dup-sudo: 02-bpf-only-dup-sudo.c
	gcc $< -o $@ -lseccomp && sudo ./$@; echo "Status: $$?"

03-bpf-only-dup: 03-bpf-only-dup.c
	gcc $< -o $@ -lseccomp && ./$@; echo "Status: $$?"

clean:
	rm -f seccomp1
	rm -f seccomp2
	rm -f 01-nothing
	rm -f 02-bpf-only-dup-sudo
	rm -f 03-bpf-only-dup
