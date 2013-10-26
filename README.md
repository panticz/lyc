lyc
===

###Linux Yamaha receiver control
wlyc (Optional, webinterface for lyc: https://github.com/panticz/wlyc)  
* |  
* lyc https://github.com/panticz/lyc  
  * |  
  * PC / Raspberry Pi / Router (e.g. TP-Link-TL-WR1043ND: http://panticz.de/OpenWrt-on-TP-Link-TL-WR1043ND)  
    * |  
    * USB seriell adapter (e.g. Digitus DA-70156: http://panticz.de/USB-Serial-adapter)  
    * |  
    * Serial cable  
    * |  
    * Yamaha AV-Receiver (Yamaha RX-V3800)


###Download binary
http://dl.panticz.de/lyc/i386/lyc - i386 compiled  
http://dl.panticz.de/lyc/ar9132/lyc - Atheros AR9132 (TP-LINK TL-WR1043ND / TL-WDR4300 router)

### Compile (Linux)
1. Download source files  
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


### Cross-Compile for OpenWRT (ar9132) router
http://www.panticz.de/Crosscompile-OpenWRT
