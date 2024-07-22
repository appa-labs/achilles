"""
create cc_test if exist scrs
"""

# def cc_test_if_exists(srcs, **kwargs):
#     if native.glob(srcs):
#         cc_test(srcs = srcs, **kwargs)

# def cc_gtest(srcs, **kwargs):
#     if native.glob(srcs):
#         cc_test(
#             srcs = srcs,
#             copts = [
#                 "-Iexternal/gtest/googletest/include",
#                 "-Iexternal/gtest/googletest",
#             ] + kwargs.get("copts", []),
#             **kwargs
#         )
load("@depend_on_what_you_use//:defs.bzl", "dwyu_aspect_factory")

# Provide no arguments for the default behavior
# Or set a custom value for the various attributes
dwyu_aspect = dwyu_aspect_factory(
    recursive = True,
    skip_external_targets = True,
    use_implementation_deps = True,
    ignored_includes = Label("//tools/bazel:dwyu_ignore_includes"),
    skipped_tags = ["disable_dwyu"],
)
