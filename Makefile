export QML_DISABLE_DISK_CACHE=1
export QT_LOGGING_RULES=kcm.customsounds.debug=true

.DEFAULT_GOAL := build

.PHONY: clean
clean:
	rm -rf build

.PHONY: format
format:
	cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=build/instal && cmake --build build --target clang-format

.PHONY: build
build:
	cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=build/install && cmake --build build

.PHONY: preview
preview:
	cmake --install build
	. build/prefix.sh && kcmshell6 kcm_customsounds

.PHONY: install
install:
	cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release && cmake --build build/release && sudo cmake --install build/release

.PHONY: uninstall
uninstall:
	sudo xargs rm < build/release/install_manifest.txt
