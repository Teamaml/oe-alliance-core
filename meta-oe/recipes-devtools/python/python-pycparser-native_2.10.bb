require python-pycparser_${PV}.bb
inherit native pythonnative
DEPENDS = "python-native"
RDEPENDS_${PN} = ""
PR = "r0"