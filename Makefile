export QML_DISABLE_DISK_CACHE=1
export QT_LOGGING_RULES="kcm.customsounds.debug=true"

clean:
	rm -rf build
	rm -rf ~/kde/usr/lib64/plugins/plasma/kcms/systemsettings/kcm_customsounds.so

.PHONY: build
build:
	cmake -S. -Bbuild -DCMAKE_INSTALL_PREFIX=~/kde/usr && cmake --build build

preview:
	cmake --install build
	. build/prefix.sh && kcmshell6 kcm_customsounds
