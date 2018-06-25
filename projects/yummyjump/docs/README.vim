Cocos2dx and Lua development environment

Configure Vim
================================
Useful Plugins
----------------------------
CursorLineCurrentWindow http://www.vim.org/scripts/script.php?script_id=4178

Logging view
----------------------------
Add syntax highlighting to the log view by adding the following line to your .vimrc. It will add the `messages` syntax to files with `.log` extension.
autocmd BufNewFile,BufReadPost *log* :set filetype=messages

Commands 
================================

Replace in multiple files
-------------------------
:args *.txt
:argdo %s/str1/str2/ge | update

Tools
================================
ctags
----------------------------
Download Exuberant Ctags and run it against the Lua files
# ctags -a level.lua manager.lua mainmenu.lua
Now in Vim type :ta <Tab> to see all available tags.
To narrow tags search you can enter the begining of the tag and hit <Tab> (autocompletion)
:ta level<Tab> 

Install Lua remote debugger
================================
Install LuaSocket
Laurent Zubiaur 2014

Clone the github repository
# git clone https://github.com/diegonehab/luasocket.git

Copy the `src` directory to your Xcode project
# cp luasocket/src xcode_project/libs/luasocket

Remove the Windows socket support
# rm xcode_project/libs/luasocket/wsocket.c

If it does not compile because of `LUASOCKET_API` not defined then include luasocket.h
For instance I had to include "luasocket.h" in `serial.c`

Load the LuaSocket core module by adding the following somewhere in your code (preferably in AppDelegate.cpp)
extern "C" {
#include "luasocket.h"
}
...
luaopen_socket_core(L);

LuaSocket should now compile. 

Move the LuaSocket scripts to your resource folder.
# mv xcode_project/libs/luasocket/*.lua xcode_project/Resources/lua/lib/socket
Note that the lua scripts must be in a folder named `socket`.

Add the `lua` and `lua/lib` folders (or whatever you named them) to the Lua path so the LuaSocket modules can be found.
    CCFileUtils::sharedFileUtils()->addSearchPath("lua");
    CCFileUtils::sharedFileUtils()->addSearchPath("lua/lib");

If Lua is not available in your environment yet download the last tarball here (http://www.lua.org/ftp/) and run the following.
# tar xzf lua-5.2.3.tar.gz
# cd lua-5.2.3
# make PLAT=macosx INSTALL_TOP=/Users/lzubiaur/gtk/inst clean all install
Change `INSTALL_TOP` to your installation destination.

Install LuaScoket on your desktop (macosx)
# cd LuaSocket
# make PLAT=macosx LUAINC_macosx_base=/Users/lzubiaur/gtk/inst/include LUAPREFIX_macosx=/Users/lzubiaur/gtk/inst prefix=/Users/lzubiaur/gtk/inst install-both
LuaSocket modules are now available in /Users/lzubiaur/gtk/inst/share/lua/5.2 (lua modules) and /Users/lzubiaur/gtk/inst/lib/lua/5.2 (core C modules)

Add MobDebug to your Xcode project and to your desktop's Lua installation
# git clone https://github.com/pkulchenko/MobDebug.github
# cp MobDebug/src/mobdebug.lua xcode_project/Resources/lua/lib/MobDebug/mobdebug.lua
# cp MobDebug/src/mobdebug.lua /Users/lzubiaur/gtk/inst/share/lua/5.2

Start the Debugger

Note that you can check that you're using the correct lua interpreter using the `which` command.
# which lua
/Users/lzubiaur/gtk/inst/bin/lua
# lua
Lua 5.2.3  Copyright (C) 1994-2013 Lua.org, PUC-Rio
> package.path = package.path..';/Users/lzubiaur/gtk/inst/share/lua/5.2/?.lua'
> package.cpath = package.cpath..';/Users/lzubiaur/gtk/inst/lib/lua/5.2/?.so'
> require('mobdebug').listen()
Lua Remote Debugger
Run the program you wish to debug

You would rather write a small lua script to configure and start the debugger and then call it using dofile.
# lua -e "dofile 'stardebug.lua'"

Add the following code somewhere in your Lua script and run your application
local mobdebug = require('MobDebug/mobdebug')
mobdebug.start("192.168.1.10",8172)
mobdebug.off() -- turn off debugging by default
...
mobdebug.on()
-- code to debug
mobdebug.off()

Your application should now connect the remote debugger controler on your desktop.
Paused at file level.lua
Type 'help' for commands
>

You can now remotely debug your Lua code. Type `help` to check all the debug commands available.


