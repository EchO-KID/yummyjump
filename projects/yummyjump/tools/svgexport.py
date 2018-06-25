#!/usr/bin/env python
# -*- coding: latin-1 -*-
"""
    svgexport.py - Batch export for Inkscape - Laurent Zubiaur
    version 1.1

description:
    Python script that can be used to automate batch exports of Inkscape objects by providing their id (set in the Object Properties dialog). 
    Also useful to batch export with a specific dpi (only available for individual object export in GUI mode).
    For all available inkscape command line options see http://inkscape.org/doc/inkscape-man.html.

usage:
    python svgexport.py <path>

argument:
    Path to the directory containing the 'export.conf' file.

configuration:
    All export options are defined in 'export.conf'. Multiple svg files can be configured using sections (see options and example below).

options:
    inkscape: absolute path to the Inkscape binary (on Mac OS it's something like /somepath/Inkscape.app/Contents/Resources/bin/inkscape)
    svg: the svg file path relative to 'export.conf'
    dpi: the dots per inch to be used
    output: where to export the images. The path is relative to 'export.conf'
    id: list of inkscape object ids to export. The first line must be empty. Other lines must begin with a whitespace (or tab)

example:

[DEFAULT]
inkscape=/somepath/Inkscape.app/Contents/Resources/bin/inkscape

[exportconfig]
svg=my_awesome_draws.svg
dpi=180
output=sprites/somedir
id=
    object1
    object2
    object3

[otherexport]
svg=other_awesome_draws.svg
dpi=90
output=sprites/otherdir
id=
    object1 
    object2

CHANGES
1.1 Add object filter option
"""
import sys,os
import argparse
import subprocess
import ConfigParser

configfile = 'export.conf'

class ExportSVG(object):

    config = None
    proc = None
    exportCmd = '--export-png'

    def __init__(self,config,idsFilter,sections,fmt):
        self.config = config
        self.idsFilter = idsFilter
        self.sections = sections
        if fmt is None:
            self.format = 'png'
        else:
            self.format = fmt
        if self.format == 'png':
            self.exportCmd = '--export-png'
        elif self.format == 'svg':
            self.exportCmd = '--export-plain-svg'
        elif self.format == 'pdf':
            self.exportCmd = '--export-pdf'

    # multi-line configuration-values with ConfigParser needs a workaround 
    # http://stackoverflow.com/questions/335695/lists-in-configparser
    def getlist(self,section,option):
        value = self.config.get(section,option)
        return list(filter(None, (x.strip() for x in value.splitlines())))

    def export(self):
        inkscape = self.config.get('DEFAULT','inkscape')
        
        env = os.environ.copy()
        env["DISPLAY"] = ''

        # Open the inkscape process
        cmd = [inkscape,'--without-gui','--shell']
        self.proc = subprocess.Popen(cmd,stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,env=env)

        # Process sections
        for section in self.config.sections():
            if self.sections and section not in self.sections:
                continue
            self.exportSection(section)
        self.proc.stdin.close()
        
        # Print the process output
        while self.proc.poll() is None:
            output = self.proc.stdout.readline()
            print output,
        
        self.proc.stdout.close()
        self.proc.wait()

    def exportSection(self,section):
        # Get options from the config file
        ids = self.getlist(section,'id')
        dpi = self.config.get(section,'dpi')
        svg = self.config.get(section,'svg')
        path = ''
        try:
            path = self.config.get(section,'output')
            if not os.path.exists(path):
                os.makedirs(path)
        except ConfigParser.NoOptionError:
            pass

        # When used in a loop the first call to subprocess.communicate closes the pipe
        # So we have to use stdin.write. See https://gist.github.com/waylan/2353749
        for oid in ids:
            if self.idsFilter and oid not in self.idsFilter:
                continue
            cmdline = '{0} --export-id-only --export-id={1} {2}={3}.{4} --export-dpi={5}\n'.format(svg,oid,self.exportCmd,os.path.join(path,oid),self.format,dpi)
            try:
                # Write to the subprocess input stream
                self.proc.stdin.write(cmdline)
            except IOError as e:
                if e.errno == errno.EPIPE or e.errno == errno.EINVAL:
                    break
                else:
                    raise

def main(argv=None):
    argv = (argv or sys.argv)[1:]
    parser = argparse.ArgumentParser(usage=("%(prog)s path"))

    parser.add_argument("path",
        type=unicode,
        help="Directory containing the export.conf file")

    parser.add_argument('-s','--sections', nargs='*',
            type=unicode,
            help="List of config sections to export (default all)")

    parser.add_argument('-f','--format', nargs=1,
        type=unicode,
        default=['png'],
        help="Export format: png,svg or pdf")

    parser.add_argument('-o','--objects', nargs='*',
        type=unicode,
        help="List of objects ids to export (default all)")

    options, args = parser.parse_known_args(argv)

    if not os.path.isdir(options.path):
        parser.error("Directory not found: '{0}'".format(options.path))

    if options.sections:
        print 'Export sections:',options.sections

    if options.objects:
        print str(options.objects)

    if options.format:
        print 'Export to',options.format[0]

    os.chdir(options.path)

    # Open the configuration file
    config = ConfigParser.ConfigParser()
    config.readfp(open(configfile))

    ExportSVG(config,options.objects,options.sections,options.format[0]).export()

# Main
if __name__ == "__main__":
    sys.exit(main())
