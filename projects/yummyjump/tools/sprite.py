#!/usr/bin/env python2.7
# -*- mode: Python;-*-
# -*- coding: utf-8 -*-
"""
Copyright (C) 2012-2014 pix2d.com
Author: Laurent Zubiaur
"""
import sys, os, glob, shutil
from subprocess import call
import fileinput

import ConfigParser
from glue import bin as glue

def replace_string(fileToSearch,textToSearch,textToReplace):
    print 'replace '+textToSearch+' with '+textToReplace+' in '+fileToSearch
    for line in fileinput.input(fileToSearch, inplace=True):
        # note the final comma, this makes it end the line with a space rather than a linebreak
        # this can be change by end='' in python 3.0
        print line.replace(textToSearch, textToReplace),

def move_files():
    for filename in glob.glob(tmp_dir+"/*"):
	fileNoExt, ext = os.path.splitext(filename)
	basename = os.path.basename(fileNoExt)
	p1, sep, p2 = basename.partition("@")
	if p2 == "4x":
                newfile = retina+"/"+p1+ext
		shutil.move(filename,newfile)
                if ext == ".plist":
                    replace_string(newfile,basename+".png",p1+".png")
	elif p2 == "2x":
                newfile = hd+"/"+p1+ext
		shutil.move(filename,newfile)
                if ext == ".plist":
                    replace_string(newfile,basename+".png",p1+".png")
	else:
		shutil.move(filename,sd+"/"+basename+ext)

    # Remove temporary directory
    shutil.rmtree(tmp_dir)

# load config file
config = ConfigParser.ConfigParser()
config.readfp(open('defaults.cfg'))

resources_dir = config.get("dir","resources")
assets_dir = config.get("dir","assets") + '/svg'
tmp_dir = resources_dir + "/glue_tmp"
optipng = config.get("tool","optipng")
sd = config.get("dir","sd")
hd = config.get("dir","hd")
retina = config.get("dir","retina")

# glue command line arguments
argv = [ "--source", assets_dir+"/sprites",
	 "--output", tmp_dir,
         # "--version",
         # square|vertical|hortizontal|diagonal|vertical-right|horizontal-bottom
         "--algorithm","square",
         # Crop unnecessary transparent spaces
         "--crop",
	 # Force glue to create every output
	 # "--force",
	 # run glue in 'project' mode
	 "--project",
	 # enable cocos2d format output
	 "--cocos2d",
	 "--margin", "3",
         "--padding", "0",
	 # ratios sd=1, hd=2, retina/ipadhd=4
	 "--ratios", "2,4"]

# call glue passing command line arguments
glue.main(argv)
move_files()

exit(0)
