cc_binary(
    name = "test",
    srcs = [
        "draw_area_bound.cc",
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