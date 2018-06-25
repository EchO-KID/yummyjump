#!/usr/bin/env python 
# -*- coding: utf-8 -*-

import os, sys 
import filecmp 
import re 
import string
from distutils import dir_util 
import shutil 
import zipfile
import json 
import io
from pprint import pprint
from inspect import getsourcefile
from os.path import abspath
import tinify

reload(sys)  
sys.setdefaultencoding('Cp1252')
tinify.key = 'GBybDYwFLIj5G1P_9Hk3-MNm9sWWo9O_'

#tinify.from_file('unoptimized.png').to_file('optimized.png')
# 
def compress_image(res_dir, out_dir):   
    #reload(sys)  
    #sys.setdefaultencoding('utf8')
    #print(sys.getdefaultencoding())

    # find .png AND .jpg
    for root, dirs, files in os.walk(res_dir):
        for file in files:
            if file.endswith(".jpg") or file.endswith(".png"):
                src_file = os.path.join(root, file)       # img path
                dist_file = string.replace(src_file, res_dir, out_dir)
                print("root:%s src_file:%s dist_file:%s" % (root, src_file, dist_file))
                tinify.from_file(src_file).to_file(dist_file)
def main(): 

    if len(sys.argv)!=3:
        print("ERROR!WRONG NUMBER OF ARGV")
        return

    #print ("argv:%s" % sys.argv[1])
    work_path = os.path.dirname(abspath(getsourcefile(lambda:0)))
    print "work_path:%s" % work_path
    #res_dir = os.path.join(os.path.join(work_path, os.pardir), "Images")  
	
    #compress_image(sys.argv[1], sys.argv[2])
    compress_image('Resources', 'Resources_compress')

if __name__ == '__main__': 
    main()