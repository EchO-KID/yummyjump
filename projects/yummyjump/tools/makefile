SHELL = /bin/bash
all: help

help:
	@echo "Available targets"
	@echo "svg              Export png images from SVG file"
	@echo "sprite           Create the sprites sheets"
	@echo "startproxy       Start the usbmux proxy deamon"
	@echo "deploy           Deploy resouces to remote device"
	@echo "startdevicelog        Start device's log monitoring"
	@echo "stopdevicelog    Stop log monitoring"
	@echo "startdebug       Start remote lua debuger"
	@echo "convert		Convert TiledMap file to level files"
	@echo "screenshot	Capture the device screen"

1: svg
2: sprites
3: startproxy
4: deploy
5: startdevicelog
6: stopdevicelog
7: startdebug

svg:
	# Export some objects from SVG file
	./svgexport.py ../Assets/svg
sprites:
	# Create the sprites sheet
	./sprites.py
	# DEPRECATED Upload the sprites sheet to remote device
	# cd ./client; \
	# ./concli.py --plist=../../Resources/hd/actions.plist 

startproxy:
	# Start the usbmuxd proxy
	cd ./client/lib; \
	nohup python tcprelay.py 8080 & 
deploy:
	python client/concli.py --conf client/concli.conf --lua ../Resources/lua/refreshAssets.lua
startdevicelog: 
	nohup ~/gtk/inst/bin/idevicesyslog &> logs/iossys.log &
	# nohup script -q /dev/null ~/gtk/inst/bin/idevicesyslog &> logs/iossys.log &
stopdevicelog:
	pkill idevicesyslog
purgedevicelog:
	pkill idevicesyslog
	sleep 1
	> logs/iossys.log
	nohup ~/gtk/inst/bin/idevicesyslog &> logs/iossys.log &
	# nohup script -q /dev/null ~/gtk/inst/bin/idevicesyslog &> logs/iossys.log &
startdebug:
	lua -e "dofile 'debug/start.lua'"
screenshot:
	pushd screenshots; ~/gtk/inst/bin/idevicescreenshot; popd
convert:
	./convertLevels.sh	
