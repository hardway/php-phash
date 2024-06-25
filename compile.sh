#/bin/sh

pecl-gen -f --dir="." pHash.xml && \
	phpize && \
	cp patch/* ./ && \
	./configure && \
	make &&
	sudo make install