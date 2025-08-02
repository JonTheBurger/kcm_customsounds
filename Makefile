.PHONY: build
build:
	cmake -S. -Bbuild -DCMAKE_INSTALL_PREFIX=~/kde/usr && cmake --build build

preview:
	cmake --install build
	. build/prefix.sh && kcmshell6 kcm_customsounds
