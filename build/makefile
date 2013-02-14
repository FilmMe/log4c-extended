#
# Copyright (C) 2013 FilmMe Group Oy
# makefile for log4c_extended DEB build
#

PRODUCT="log4c-extended"
VER="1.2.1"
ARCH=`dpkg --print-architecture`
ROOT=$(PRODUCT)_$(VER)_$(ARCH)

all:
	# create control files
	mkdir $(ROOT)
	mkdir $(ROOT)/DEBIAN
	cat src/control  | sed s/#VER#/$(VER)/ | sed s/#ARCH#/$(ARCH)/ > $(ROOT)/DEBIAN/control
	cp src/postinst $(ROOT)/DEBIAN/postinst
	# copy content
	./cp2 "../src/log4c/.libs/liblog4c.so" $(ROOT)/usr/local/lib/
	# make deb package
	dpkg-deb --build $(ROOT)
	# remove temp directory
	rm -R $(ROOT)

clean:
	# remove temp directories
	rm -R -f $(PRODUCT)_*_$(ARCH)/
	# remove deb packages
	rm -f $(PRODUCT)_*_$(ARCH).deb

