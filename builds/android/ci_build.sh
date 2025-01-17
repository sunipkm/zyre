#!/usr/bin/env bash
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################

export NDK_VERSION=android-ndk-r24
export ANDROID_NDK_ROOT="/tmp/${NDK_VERSION}"

case $(uname | tr '[:upper:]' '[:lower:]') in
  linux*)
    HOST_PLATFORM=linux
    ;;
  darwin*)
    HOST_PLATFORM=darwin
    ;;
  *)
    echo "Unsupported platform"
    exit 1
    ;;
esac

if [ ! -d "${ANDROID_NDK_ROOT}" ]; then
    export FILENAME=$NDK_VERSION-$HOST_PLATFORM.zip

    (cd '/tmp' \
        && wget http://dl.google.com/android/repository/$FILENAME -O $FILENAME &> /dev/null \
        && unzip -q $FILENAME) || exit 1
    unset FILENAME
fi

rm -rf /tmp/tmp-deps
mkdir -p /tmp/tmp-deps

export LIBZMQ_ROOT="/tmp/tmp-deps/libzmq"
git clone --quiet --depth 1 https://github.com/zeromq/libzmq.git $LIBZMQ_ROOT

export CZMQ_ROOT="/tmp/tmp-deps/czmq"
git clone --quiet --depth 1 https://github.com/zeromq/czmq.git $CZMQ_ROOT

./build.sh "arm"
./build.sh "arm64"
./build.sh "x86"
./build.sh "x86_64"

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
