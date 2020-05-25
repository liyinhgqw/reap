cc_binary(
    name = "test",
    srcs = [
        "test_arrangement.cc",
    ],
    linkopts = [
        "-lm",
    ],
    deps = [
        "//reap/core",
        "//reap/plan",
        "//reap/proto",
    ],
)

cc_binary(
    name = "test_cgal",
    srcs = [
        "test_cgal.cc",
    ],
    linkopts = [
        "-lm",
    ],
    deps = [
        "@cgal",
    ],
)