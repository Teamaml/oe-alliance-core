require gcc-configure-common.inc

LICENSE = "NCSA | MIT"

LIC_FILES_CHKSUM = "\
    file://libsanitizer/LICENSE.TXT;md5=0249c37748936faf5b1efd5789587909 \
"

EXTRA_OECONF_PATHS = "\
    --with-sysroot=/not/exist \
    --with-build-sysroot=${STAGING_DIR_TARGET} \
"

do_configure () {
    rm -rf ${B}/${TARGET_SYS}/libsanitizer/
    mkdir -p ${B}/${TARGET_SYS}/libsanitizer/
    cd ${B}/${TARGET_SYS}/libsanitizer/
    chmod a+x ${S}/libsanitizer/configure
    relpath=${@os.path.relpath("${S}/libsanitizer", "${B}/${TARGET_SYS}/libsanitizer")}
    $relpath/configure ${CONFIGUREOPTS} ${EXTRA_OECONF}
    # Easiest way to stop bad RPATHs getting into the library since we have a
    # broken libtool here
    sed -i -e 's/hardcode_into_libs=yes/hardcode_into_libs=no/' ${B}/${TARGET_SYS}/libsanitizer/libtool
    # Link to the sysroot's libstdc++ instead of one gcc thinks it just built
    sed -i -e '/LIBSTDCXX_RAW_CXX_\(CXXFLAGS\|LDFLAGS\)\s*=/d' ${B}/${TARGET_SYS}/libsanitizer/*/Makefile
}
EXTRACONFFUNCS += "extract_stashed_builddir"
do_configure[depends] += "${COMPILERDEP}"

do_compile () {
    cd ${B}/${TARGET_SYS}/libsanitizer/
    oe_runmake MULTIBUILDTOP=${B}/${TARGET_SYS}/libsanitizer/
}

do_install () {
    cd ${B}/${TARGET_SYS}/libsanitizer/
    oe_runmake 'DESTDIR=${D}' MULTIBUILDTOP=${B}/${TARGET_SYS}/libsanitizer/ install
    if [ -d ${D}${infodir} ]; then
        rmdir --ignore-fail-on-non-empty -p ${D}${infodir}
    fi
    chown -R root:root ${D}
}

INHIBIT_DEFAULT_DEPS = "1"
ALLOW_EMPTY:${PN} = "1"
DEPENDS = "gcc-runtime virtual/${TARGET_PREFIX}gcc"

BBCLASSEXTEND = "nativesdk"

PACKAGES = "${PN} ${PN}-dbg"
PACKAGES += "libasan libubsan liblsan libtsan"
PACKAGES += "libasan-dev libubsan-dev liblsan-dev libtsan-dev"
PACKAGES += "libasan-staticdev libubsan-staticdev liblsan-staticdev libtsan-staticdev"

RDEPENDS:libasan += "libstdc++"
RDEPENDS:libubsan += "libstdc++"
RDEPENDS:liblsan += "libstdc++"
RDEPENDS:libtsan += "libstdc++"
RDEPENDS:libasan-dev += "${PN}"
RDEPENDS:libubsan-dev += "${PN}"
RDEPENDS:liblsan-dev += "${PN}"
RDEPENDS:libtsan-dev += "${PN}"
RRECOMMENDS:${PN} += "libasan libubsan"
RRECOMMENDS:${PN}:append:x86-64 = " liblsan libtsan"
RRECOMMENDS:${PN}:append:x86 = " liblsan"

do_package_write_ipk[depends] += "virtual/${MLPREFIX}${TARGET_PREFIX}compilerlibs:do_packagedata"
do_package_write_deb[depends] += "virtual/${MLPREFIX}${TARGET_PREFIX}compilerlibs:do_packagedata"
do_package_write_rpm[depends] += "virtual/${MLPREFIX}${TARGET_PREFIX}compilerlibs:do_packagedata"

# MIPS, aarch64, and SPARC are broken.
COMPATIBLE_HOST = '(x86_64|i.86|powerpc|arm).*-linux'

FILES:libasan += "${libdir}/libasan.so.*"
FILES:libasan-dev += "\
    ${libdir}/libasan_preinit.o \
    ${libdir}/libasan.so \
    ${libdir}/libasan.la \
"
FILES:libasan-staticdev += "${libdir}/libasan.a"

FILES:libubsan += "${libdir}/libubsan.so.*"
FILES:libubsan-dev += "\
    ${libdir}/libubsan.so \
    ${libdir}/libubsan.la \
"
FILES:libubsan-staticdev += "${libdir}/libubsan.a"

FILES:liblsan += "${libdir}/liblsan.so.*"
FILES:liblsan-dev += "\
    ${libdir}/liblsan.so \
    ${libdir}/liblsan.la \
"
FILES:liblsan-staticdev += "${libdir}/liblsan.a"

FILES:libtsan += "${libdir}/libtsan.so.*"
FILES:libtsan-dev += "\
    ${libdir}/libtsan.so \
    ${libdir}/libtsan.la \
"
FILES:libtsan-staticdev += "${libdir}/libtsan.a"

FILES:${PN} = "${libdir}/*.spec ${libdir}/gcc/${TARGET_SYS}/${BINV}/include/sanitizer/*.h"
