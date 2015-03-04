#!/bin/bash

set -e

ESDK=${EPIPHANY_HOME}
ELIBS=${ESDK}/tools/host/lib:${LD_LIBRARY_PATH}
EHDF=${EPIPHANY_HDF}

cd bin

sudo -E LD_LIBRARY_PATH=${ELIBS} EPIPHANY_HDF=${EHDF} ./runerl.escript
#sudo -E LD_LIBRARY_PATH=${ELIBS} EPIPHANY_HDF=${EHDF} erl -pz ../../../ebin -pz ../../../priv

