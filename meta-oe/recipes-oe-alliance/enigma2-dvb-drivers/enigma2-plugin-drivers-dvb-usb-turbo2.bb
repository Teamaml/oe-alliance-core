SUMMARY = "USB DVB driver for Vuplus Tuner Turbo2"
PACKAGE_ARCH = "${MACHINE_ARCH}"

require conf/license/license-gplv2.inc

RRECOMMENDS:${PN} = " \
    kernel-module-dvb-usb \
    kernel-module-dvb-usb-v2 \
    ${DVB_CYPRESS}-cypress-firmware \
    vuplus-tuner-turbo2 \
    "

PV = "1.0"
PR = "r0"

ALLOW_EMPTY:${PN} = "1"
