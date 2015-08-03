#!/usr/bin/env python2.7
# -*- mode: Python;-*-
# -*- coding: utf-8 -*-

# Format the lua package template (../Resources/lua/package_template.lua)
# Usage: luapack.py <name>
# The following parameters are updated in the template
# year: the current year for the license header
# filename: <name> is lowercased and used to create the file and 
#           to update the filename parameter in the header
# package: <name> is titled (first letter uppercase and the rest lowercase) 
#          and used as the package name 

import os,sys,time
from time import gmtime, strftime
import argparse

def format_template(package):
    year = strftime("%Y",gmtime())
    package = package.title()
    filename = package.lower()
    filepath = '../Resources/lua/{}.lua'.format(filename)

    if os.path.exists(filepath):
        print 'ERROR: Lua package already exists: {}'.format(filepath)
        return

    with open('../Resources/lua/package_template.lua','r') as f:
        txt = f.read().encode('utf-8').format(year=year,filename=filename,package=package).encode('utf-8')
    f.close()

    with open(filepath,'w') as f:
        f.write(txt)
    f.close()

def main(argv=None):

    argv = (argv or sys.argv)[1:]

    parser = argparse.ArgumentParser(usage=("%(prog)s package"))

    parser.add_argument("package",
        type=unicode,
        help="package name")

    options, args = parser.parse_known_args(argv)

    format_template(options.package)

if __name__ == "__main__":
    sys.exit(main())
