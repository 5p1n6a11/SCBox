# hook

## kernel

### References

https://kernhack.hatenablog.com/entry/2014/12/05/000346

## user

## Tips

ausyscall x86_64 --dump | awk '{print $2}' | sed 's/[^ ]\+/\t"&",/g'

### References

https://itchyny.hatenablog.com/entry/2017/07/31/090000

https://blog.ssrf.in/post/follow-system-call-with-ptrace/
