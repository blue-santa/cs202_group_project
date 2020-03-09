# When building MeTA, execute this command in the build directory (might need to use sudo)
sed -i 's/xlocale/locale/' deps/icu-58.2/src/ExternalICU/source/i18n/digitlst.cpp
