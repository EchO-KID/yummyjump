#!/usr/bin/env python2.7
# -*- mode: Python;-*-
# -*- coding: utf-8 -*-

"""
Copyright (C) 2012-2014 pix2d.com
Author: Laurent Zubiaur
"""
import sys, json
from jsonschema import validate
from jsonschema import ValidationError
 
# Load the json document
with open(sys.argv[1], 'rt') as f1:
        doc = json.load(f1)
        f1.close()
 
# Load the json schema
with open(sys.argv[2], 'rt') as f2:
        schema = json.load(f2)
        f2.close()
 
try:
        validate(doc, schema)
except ValidationError as e:
        print e.message
        print "context:"
        print e.context
        exit(-1)
 
print sys.argv[1] + " is valid"
exit(0)
