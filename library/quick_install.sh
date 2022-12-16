#!/usr/bin/env bash

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
    DIR=$(cd -P "$(dirname "$SOURCE")" >/dev/null 2>&1 && pwd)
    SOURCE=$(readlink "$SOURCE")
    [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
PWD="$(cd -P "$(dirname "$SOURCE")" >/dev/null 2>&1 && pwd)"
# Thanks StackOverflow for this hack

InstallTarget="$PWD/../src/arithmetic_lib"
LibLocation="$PWD/ntl-11.5.1"
TarLocation=$LibLocation.tar.gz
nbThread=16

if [ -d $InstallTarget ]; then
    echo "Already Installed"
else
    mkdir $LibLocation && tar -xzf $TarLocation -C $PWD
    mkdir $InstallTarget

    cd $LibLocation/src
    ./configure PREFIX=$InstallTarget NTL_GMP_LIP=off
    make -j$nbThread
    # make check -j"$nbThread"
    make install -j$nbThread
    rm -rf $LibLocation

    if sed -i 's/NTL/./g' $InstallTarget/include/NTL/ALL_FEATURES.h; then
        sed -i 's/</"/g' $InstallTarget/include/NTL/ALL_FEATURES.h
        sed -i 's/>/"/g' $InstallTarget/include/NTL/ALL_FEATURES.h
    else
        echo "Using gsed"
        gsed -i 's/NTL/./g' $InstallTarget/include/NTL/ALL_FEATURES.h
        gsed -i 's/</"/g' $InstallTarget/include/NTL/ALL_FEATURES.h
        gsed -i 's/>/"/g' $InstallTarget/include/NTL/ALL_FEATURES.h
    fi
       echo "Everything is installed"
fi
