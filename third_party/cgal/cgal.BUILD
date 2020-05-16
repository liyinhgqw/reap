licenses(["notice"])

exports_files(["LICENSE.txt"])

cc_library(
    name = "cgal",
    hdrs = glob([
        "**/*",
    ]),
    includes = [
        ".",
    ],
    deps = [
        "@boost//:config",
    ],
    visibility = ["//visibility:public"],
)