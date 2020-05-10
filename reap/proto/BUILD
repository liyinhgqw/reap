package(
    default_visibility = ["//visibility:public"],
)

load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
    name = "reap_proto",
    srcs = [
        "geometry.proto",
        "plan.proto",
    ],
)

cc_proto_library(
    name = "reap_cc_proto",
    deps = [":reap_proto"],
)

cc_library(
    name = "proto",
    deps = [":reap_cc_proto"],
)
