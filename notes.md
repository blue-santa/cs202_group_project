# OBSOLETE
# Instructions to build MeTA in the build directory (in root of project)

# set up submodules
git submodule update --init --recursive

# set up a build directory
mkdir build
cd build
cp ../submodules/meta/config.toml .

# Might need to use sudo for many of these # configure and build the project
cmake ../submodules/meta/. -DCMAKE_BUILD_TYPE=Release
make

# When building MeTA, execute this command in the build directory (might need to use sudo)
sed -i 's/xlocale/locale/' deps/icu-58.2/src/ExternalICU/source/i18n/digitlst.cpp

# Try make again
make
