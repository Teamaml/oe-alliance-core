SUMMARY = "WiFi devices for Realtek 8188fu chipsets."
inherit allarch

require conf/license/license-gplv2.inc

RRECOMMENDS:${PN} = " \
        rt8188fu \
        firmware-rt8188fu \
"

PV = "1.0"
PR = "r1"

ALLOW_EMPTY:${PN} = "1"
