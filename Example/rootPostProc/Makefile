postprocroot : postprocroot.cc
	g++ `root-config --cflags` -o postprocroot postprocroot.cc `root-config --libs`
	g++ `root-config --cflags` -o postprocroot_wDead postprocroot_wDead.cc `root-config --libs`
clean :
	rm -f postprocroot_wDead
	rm -f postprocroot

