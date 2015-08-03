#!/usr/bin/env python
"""
" Copyright (c) 2013 Laurent Zubiaur
"
" http://www.pix2d.com/
"
" Permission is hereby granted, free of charge, to any person obtaining a copy
" of this software and associated documentation files (the "Software"), to deal
" in the Software without restriction, including without limitation the rights
" to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
" copies of the Software, and to permit persons to whom the Software is
" furnished to do so, subject to the following conditions:
" 
" The above copyright notice and this permission notice shall be included in
" all copies or substantial portions of the Software.
" 
" THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
" IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
" FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
" AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
" LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
" OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
" THE SOFTWARE.
"""

import os,sys,socket
import base64
import argparse
import plistlib
import ConfigParser
from struct import *

def main(argv=None):

    argv = (argv or sys.argv)[1:]

    parser = argparse.ArgumentParser(usage=("usage: %(prog)s [--conf | -c] [--plist | -p] [--json | -j] [--lua | -l]"))

    parser.add_argument("--conf", "-c",
            dest="conf_path",
            type=unicode,
            help="Configuration file")

    parser.add_argument("--plist", "-p",
        dest="plist_path",
        type=unicode,
        help="Sprites sheet plist path")

    parser.add_argument("--json", "-j",
            dest="json_path",
            type=unicode,
            help="level's json data")

    parser.add_argument("--lua", "-l",
            dest="lua_path",
            type=unicode,
            help="run custom lua script")

    options, args = parser.parse_known_args(argv)

    if not options.conf_path:
        options.conf_path = 'concli.conf'

    # load config file
    config = ConfigParser.ConfigParser()
    config.readfp(open(options.conf_path))

    if options.plist_path:
        UpdateSpritesCmd(options.plist_path,config).run()
    
    if options.json_path:
        ReloadLevelCmd(options.json_path,config).run()

    if options.lua_path:
        RunLuaScriptCmd(options.lua_path,config).run()
    
    return 0

class Command(object):
    
    msg = ''
    config = None
    sock = None
    PROTO_VERSION = 1

    def __init__(self,config):
        self.config = config
        # create an INET, STREAMing socket
        socket.setdefaulttimeout(5.0)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def send(self):
        # Request header
        header = pack('!IB',len(self.msg),self.PROTO_VERSION)
        # Construct the request message (header + content)
        packet = '{}{}'.format(header,self.msg)
        packet_len = len(packet)
        # send the message header and content
        total_sent = 0
        while True:
            sent = self.sock.send(packet[total_sent:])
            if sent == 0:
                raise RuntimeError("Can't send message. Please ensure that the remote application is running.")
            total_sent = total_sent + sent
            if total_sent == packet_len:
                break
        print '{} byte(s) sent'.format(total_sent)

    def recv(self):
        resp = ''
        while True: 
            chunk = self.sock.recv(4096)
            if chunk == '':
                break # EOF
            resp = resp + chunk
        return resp

    def run(self):
        port = self.config.getint("usbmuxd","console.port")
        addr = self.config.get("usbmuxd","console.ip")

        # Connect to the remote device
        code = self.sock.connect_ex((addr, port))
        if not code == 0:
            print "Can't connect to device ({}). Please check that the usbmuxd proxy is running if the device is attached via usb.".format(os.strerror(code))
            return
        print 'Connected to remote device.'
        # Send the command message
        self.send();
        # Done sending 
        # self.sock.shutdown(socket.SHUT_WR) # breaks receiving response on mac os

        # Read the response
        # resp = self.recv() # now implemented using makefile().read
        resp = self.sock.makefile().read()
        # close the connection
        self.sock.close()
        # Print the response message 
        print 'Response: ' + resp

class RunLuaScriptCmd(Command):
    def __init__(self,lua_path,config):
        super(RunLuaScriptCmd,self).__init__(config)
        with open(lua_path, 'r') as f:
           self.msg = f.read().encode('utf-8')
        f.close()

class ReloadLevelCmd(Command):
    def __init__(self,json_path,config):
        super(ReloadLevelCmd,self).__init__(config)
        # base64 encode the json file
        with open(json_path, 'r') as f:
            json_base64 = base64.encodestring(f.read())
        f.close()
        self.msg = """-- Lua script
data = [[
{}]]
v = pix2d_console.Command:new()
v:reloadLevel(data)
""".format(json_base64).encode('utf-8')
        
class UpdateSpritesCmd(Command):
    def __init__(self,plist_path,config):
        super(UpdateSpritesCmd,self).__init__(config)

        # base64 encode the plist file
        with open(plist_path, 'r') as f:
            plist_base64 = base64.encodestring(f.read())
        f.close()

        # Load the plist file
        plist = plistlib.readPlist(plist_path)

        # base64 encode the texture file
        texture_path = "{0}/{1}".format(os.path.dirname(plist_path), plist['metadata']['textureFileName'])
        with open(texture_path, 'r') as f:
            sprite_base64 = base64.encodestring(f.read())
        f.close()

        # The formated Lua script is formated with the base64 files content
        self.msg = """-- Lua script
texture = [[
{}]]
plist = [[
{}]]
v = pix2d_console.Command:new()
v:updateSpriteFrames(plist,texture)
v:reloadLevel()
""".format(sprite_base64,plist_base64).encode('utf-8')

if __name__ == "__main__":
    main()
