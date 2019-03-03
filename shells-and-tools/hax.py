#!/usr/bin/python3
# hax.py - a script to automate frequent tasks on
#   wargame-style CTF (capture the flag) exercises
#   and okay, yeah, also to keep my python sharp.
#
# (TODO - key features)
# - Log in via SSH using "hax.py levelname"
# - Grab flags
# (TODO - nice to have)
# - Default to "current" level
# - Grab the text of the overthewire hint page
# - Command-line flag "-g" drops your go-bag in /tmp/nicknameN
# - Might need "gobag.py" to support SCP'ing files back home
# - Detect that you beat a new level and cheer you on

import ssh


def getcredentials(filename, level):
    creds = "password1"
    f = filename
    print("Looking in {} for {}.".format(filename, levelname))
    return creds


def putcredentials(filename, level, flag):
    f = filename
    print("{} is dead! Long live {}")
    return 0


class CTF:
    def __init__(self, ctfname: string, server, port: int, username: string):
        self.ctfname = ctfname
        self.server = "localhost"
        self.port = 22
        self.username = "hacker"

    @classmethod
    def initialize_from_overthewire(cls, ctfname):
        ctflist = ["bandit", "behemoth", "krypton", "leviathan", "maze", "manpage", "narnia",
                   "utumno", "vortex", "semtex",  "drifter"]
        if ctfname in ctflist:
            server = ctfname + ".labs.overthewire.org"  # bandit is at bandit.labs.overthewire.org
            username = ctfname                          # username starts with "bandit" but we'll append digits later
            portlist = []
            for p in range(2220, 2231):                 # Excludes port 2231
                portlist.append(p)
            config = dict(zip(ctflist, portlist))
            port = config.get(ctfname)
            new_ctf = cls(ctfname, server, port, username)
        else:
            print("{} is not an overthewire level name".format(ctfname))
            exit(-1)

