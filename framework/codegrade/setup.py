#!/usr/bin/env python3

import getpass
import shutil as sh
import subprocess as sp
import sys
import os

# This script is executed on codegrade during the initial shared setup.

grade_dir = os.path.dirname(os.path.realpath(__file__))
base_dir = os.path.realpath(os.path.join(grade_dir, "..", ".."))

if getpass.getuser() != "codegrade":
    print("This is supposed to run on the codegrade environment. Exiting...")
    sys.exit(1)

os.chdir(base_dir)
# If we're in a git repo, clean it from build files.
sp.run(["git", "clean", "-fdx"], cwd=base_dir, stderr=sp.DEVNULL, stdout=sp.DEVNULL)
# Get rid of the git folder to save snapshot space.
sh.rmtree(os.path.join(base_dir, ".git"), ignore_errors=True)

# Setup docker.
sp.check_call("sudo groupadd docker", shell=True)
sp.check_call("sudo usermod -aG docker codegrade", shell=True)
sp.check_call("curl -fsSL https://get.docker.com -o install-docker.sh", shell=True)
sp.check_call("sudo sh install-docker.sh", shell=True)
os.remove("install-docker.sh")

# Build the container for the first time so the image is cached.
# The 'ls' is just a short dummy command to trigger a build.
run_py = os.path.join(base_dir, "run.py")
sp.check_call([run_py, "-c", "ls"])