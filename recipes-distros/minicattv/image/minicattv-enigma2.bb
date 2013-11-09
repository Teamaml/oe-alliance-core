DESCRIPTION = "Merge machine and distro options to create a enigma2 machine task/package"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/LICENSE;md5=3f40d7994397109285ec7b81fdeb3b58 \
                    file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

PV = "1.0"
PR = "r6"

inherit packagegroup

DEPENDS = "enigma2-pliplugins minicattv-feeds"

RRECOMMENDS_${PN} = "\
    minicattv-version-info \
    enigma2-plugin-drivers-usbserial \
    enigma2-plugin-extensions-ppanel \
    enigma2-plugin-pli-softcamsetup \
    enigma2-plugin-extensions-imdb \
    enigma2-plugin-extensions-autotimer \
    enigma2-plugin-extensions-epgsearch \
    enigma2-plugin-extensions-graphmultiepg \
    enigma2-plugin-extensions-cutlisteditor \
    enigma2-plugin-extensions-mediaplayer \
    enigma2-plugin-extensions-dvdplayer \
    enigma2-plugin-extensions-epgrefresh \
    enigma2-plugin-extensions-enhancedmoviecenter \
    enigma2-plugin-systemplugins-videomode \
    enigma2-plugin-systemplugins-videotune \
    enigma2-plugin-systemplugins-autoresolution \
    enigma2-plugin-systemplugins-softwaremanager \
    enigma2-plugin-systemplugins-hotplug \
    enigma2-plugin-systemplugins-skinselector \
    ${@base_contains("MACHINE_FEATURES", "3dtv", "enigma2-plugin-systemplugins-osd3dsetup" , "", d)} \
    "
