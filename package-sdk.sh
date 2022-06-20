#!/bin/bash

arch=x86_64-linux-gnu
package_name=neuron-sdk

function usage() {
    echo "Usage: $0 "
    echo "-n package name [default: ${package_name}]"
    echo "-p target platform compiler prefix (opts: x86_64-linux-gnu, arm-linux-gnueabihf, aarch64-linux-gnu, ...)[default: x86_64-linux-gnu]"
}

while getopts "p:n:h-:" OPT; do
    case ${OPT} in
    p)
        arch=$OPTARG
        ;;
    n)
        package_name=$OPTARG
        ;;
    h)
        usage
        exit 0
        ;;
    \?)
        usage
        exit 1
        ;;
    esac
done

rm -rf ${package_name}/*

mkdir -p $package_name/include/neuron/
mkdir -p $package_name/lib
mkdir -p $package_name/config
mkdir -p $package_name/plugins/schema

cp neuron.conf ${package_name}/
cp cmake/neuron-config.cmake ${package_name}/
cp -r include/* ${package_name}/include/
cp build/libneuron-base.so ${package_name}/lib
cp -r ft/Keyword ${package_name}/ft/
cp ft/api_http.resource ${package_name}/ft/
cp ft/api_mqtt.resource ${package_name}/ft/
cp ft/common.resource ${package_name}/ft/
cp ft/error.resource ${package_name}/ft/
cp ft/requirements.txt ${package_name}/ft/

cp zlog/src/libzlog.so.1.2 ${package_name}/lib

tar czf ${package_name}-${arch}.tar.gz ${package_name}/
ls ${package_name}
rm -rf ${package_name}

echo "${package_name}-${arch}.tar.gz"
