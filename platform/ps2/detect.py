import os
import sys
import platform
import subprocess

from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from SCons import Environment

def get_name():
    return "PS2"


def can_build():
    return os.path.exists(get_env_ps2toolkit_root())


def get_opts():
    return [
        ("PS2TOOLKIT", "Path to the PS2Toolkit", get_env_ps2toolkit_root())
    ]


def get_flags():
    return [
        ("arch", "mips64"),
        ("opengl3", False),
        ("openxr", False),
        ("use_volk", False),
        ("vulkan", False),
    ]


def get_doc_classes():
    return [
        "EditorExportPlatformPS2",
    ]


def get_doc_path():
    return "doc_classes"


def get_env_ps2toolkit_root():
    return os.environ.get("PS2TOOLKIT", -1)


def configure(env: "Environment"):
    # Validate

    supported_arches = ["mips64"]
    if env["arch"] not in supported_arches:
        print(
            'Unsupported CPU architecture "%s" for PS2. Supported architectures are: %s.'
            % (env["arch"], ", ".join(supported_arches))
        )
        sys.exit()

    toolkit_root = env["PS2TOOLKIT"]

    # Compiler

    ee_toolchain_path = os.path.join(toolkit_root, "ee")
    ee_compiler_path = os.path.join(ee_toolchain_path, "bin")
    ee_compiler_prefix = "mips64el-elf-"

    compiler_path = ee_compiler_path
    compiler_prefix = ee_compiler_prefix

    env["AR"] = os.path.join(compiler_path, compiler_prefix + "ar")
    env["AS"] = os.path.join(compiler_path, compiler_prefix + "as")
    env["CC"] = os.path.join(compiler_path, compiler_prefix + "gcc")
    env["CXX"] = os.path.join(compiler_path, compiler_prefix + "g++")
    env["LINK"] = os.path.join(compiler_path, compiler_prefix + "gcc")
    env["RANLIB"] = os.path.join(compiler_path, compiler_prefix + "gcc-ranlib")

    # Linker

    # Flags

    env.Append(CCFLAGS=["-march=r5900"])
    env.Prepend(CPPPATH=["#platform/ps2"])
    env.Append(CPPDEFINES=["PS2_ENABLED", "UNIX_ENABLED"])
    env.Append(CPPDEFINES=["NEED_LONG_INT"]) # PS2_TODO: Is this a hack?
