#!/usr/bin/python3

import argparse
import logging
import os
import subprocess


log = logging.getLogger(__name__)


def kill_process(port):
    '''
    Kill process that listens on a given port.
    '''
    pid_cmd = "lsof -ti :%s -sTCP:LISTEN" % port
    pid = subprocess.check_output(pid_cmd, shell=True).strip().decode("utf-8")
    log.info("Process %s is going to be killed." % pid)
    kill_cmd = "kill -9 %s" % pid
    log.info(os.system(kill_cmd))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--port", type=int, default=10000)
    args = parser.parse_args()

    kill_process(args.port)
