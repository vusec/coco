#!/usr/bin/env python3

import argparse
import getpass
import subprocess as sp
import os
import socket
import sys

if socket.gethostname() == "coco" and getpass.getuser() == "coco":
    print("error: It appears you're already in the docker container.")
    sys.exit(1)

script_dir = os.path.dirname(os.path.realpath(__file__))
os.chdir(script_dir)

parser = argparse.ArgumentParser(description="Starts CoCo docker container.")
parser.add_argument(
    "-s", "--nosudo", action="store_true", help="Run docker *without* sudo."
)
parser.add_argument(
    "-v", "--verbose", action="store_true", help="Print more information."
)
parser.add_argument(
    "-n", "--nobuild", action="store_true", help="Skip container build."
)
parser.add_argument(
    "-l", "--legacy", action="store_true", help="Don't use build kit from docker"
)
parser.add_argument(
    "-y", "--nohost", action="store_true", help="Don't use network=host fix."
)
parser.add_argument(
    "-d", "--download", action="store_true", help="Download image instead of building locally."
)
parser.add_argument(
    "-c", "--command", default=None, help="Command to run instead of shell."
)
parser.add_argument(
    "-u",
    "--ulimit",
    action="store_false",
    help="Don't try to set ulimit to get valgrind working",
)

cmd_args = parser.parse_args()
build_container = not cmd_args.nobuild
verbose = cmd_args.verbose
nosudo = cmd_args.nosudo
nohost = cmd_args.nohost
download = cmd_args.download

docker_cmd = ["docker"] if nosudo else ["sudo", "docker"]
image_name = "coco/docker"
if download:
    image_name = "teemperor/coco"
    build_container = False

# The default dir in the docker container.
docker_home_dir = "/home/coco/mnt/"
# The shell to start in the container.
shell = "/usr/bin/fish"

# Extra args passed to all docker commands.
# --network=host gets networking running if the host's network drivers are busted.
docker_extra_args = [] if nohost else ["--network=host"]

# The path to the docker file.
docker_path = os.path.join(script_dir, "framework", "docker")

# Use docker's build kit unless disabled by user.
if not cmd_args.legacy:
    os.environ["DOCKER_BUILDKIT"] = "1"


def build():
    args = docker_cmd + ["build"] + docker_extra_args + ["-t", image_name, docker_path]
    if verbose:
        print(args)
    sp.check_call(args)


def start():
    args = docker_cmd[:]
    args += ["run", "-w", docker_home_dir, "--hostname", "coco"]
    args += docker_extra_args
    # These args allow debugging within the container.
    args += ["--cap-add=SYS_PTRACE"]
    args += ["--security-opt", "seccomp=unconfined"]
    # Some platforms set a very high fd limit which breaks valgrind.
    if cmd_args.ulimit:
        args += ["--ulimit", "nofile=10000:10000"]
    # Mount the course folder in the container.
    args += ["--mount", f"type=bind,source={script_dir},target={docker_home_dir}"]
    if cmd_args.command:
        args += [image_name]
        args += [shell, "-c", cmd_args.command]
    else:
        args += ["-it"]
        # Start an interactive shell.
        args += [image_name]
        args += [shell]
    if verbose:
        print(args)
    sp.run(args)


if build_container:
    build()
start()
