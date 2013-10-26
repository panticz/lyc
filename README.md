lyc
===

Linux Yamaha receiver control

###Download binary
http://dl.panticz.de/lyc/i386/lyc - i386 compiled  
http://dl.panticz.de/lyc/ar9132/lyc - Atheros AR9132 (TP-LINK TL-WR1043ND / TL-WDR4300 router)

### Compile
1. Download lyc.c and Makefile  
`wget https://raw.github.com/panticz/lyc/master/Makefile`  
`wget https://raw.github.com/panticz/lyc/master/lyc.c`  
`wget https://raw.github.com/panticz/lyc/master/rxvx700.h`  

2. Compile  
  `make`

3. Set up USB Serial adapter  
http://www.panticz.de/USB-Serial-adapter

4. Run command
`./lyc input dvd`
`./lyc volume up`

### Compile for OpenWRT (ar9132) router:
http://www.panticz.de/Crosscompile-OpenWRT
