#!/bin/bash

IMGEXT=".bin"
ASTDIR="./assets"
TMPDIR="./tmp"
TOOLS="./tools"

BIN2C="${TOOLS}/bin2c/bin2c"
ZX0="${TOOLS}/zx0/zx0"

mkdir -p ${TOOLS}

if [ ! -f ${BIN2C} ]; then
  DIR=$(dirname ${BIN2C})
  git clone https://github.com/JeremyAgost/bin2c.git ${DIR}
  gcc ${DIR}/bin2c.c -o ${BIN2C}
fi

if [ ! -f ${ZX0} ]; then
  DIR=$(dirname ${ZX0})
  git clone https://github.com/einar-saukas/ZX0.git ${DIR}
  CFLAGS="-ox -ob -ol+ -onatx -oh -zp8 -g0 -oe -ot -Wall -xc -s -floop-optimize -fno-stack-check"
  gcc ${CFLAGS} ${DIR}/src/zx0.c ${DIR}/src/optimize.c ${DIR}/src/compress.c ${DIR}/src/memory.c -o ${ZX0}
fi

mkdir -p ${TMPDIR}

find ${ASSETDIR} -name "*${IMGEXT}"|while read IMG; do
  BN=$(basename ${IMG} ${IMGEXT})
  dd if=${IMG} of=${TMPDIR}/${BN}.img bs=4096 count=1
  dd if=${IMG} of=${TMPDIR}/${BN}.atr bs=512  count=1 skip=12
  ${ZX0} -f ${TMPDIR}/${BN}.img
  ${ZX0} -f ${TMPDIR}/${BN}.atr
  ${BIN2C} -m -o ${BN}_img.h -n ${BN}_img ${TMPDIR}/${BN}.img.zx0
  ${BIN2C} -m -o ${BN}_atr.h -n ${BN}_atr ${TMPDIR}/${BN}.atr.zx0
done
