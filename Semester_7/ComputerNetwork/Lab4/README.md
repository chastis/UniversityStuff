# Lab 4

form: https://forms.gle/jJikuT3np6R6yGNYA

important:
* Switch> enable | enter to privileged mode
* Switch# show running-config | show runtime config (in ram)
* Switch# show startup-config | show saved config (in nvram)
* Switch# configure terminal | global configuration mode
* Switch(config)# hostname S1 | name of commutator
* Switch(config)# exit | go to back mode, also can use ctrl+z
* Switch(config)# line console 0 | console mode
* Switch(config-line)# password letmein | console pas
* Switch(config-line)# login | enable console pas
* Switch(config)# enable password c1$c0 | enable __enable__ pas
* Switch(config)# enable secret itsasecret | enable encryption __enable__ pas (reinit previous)
* Switch(config)# service password-encryption | enable encryption for all passwords
* Switch(config)# banner motd "This is a secure system. Authorized Access Only!" | set "hello world" message for commutator
* Switch# copy running-config startup-config | save ram config to nvram 

also important, but not used:
* Switch# erase startup-config | delete nvram conf
* Switch# delete vlan.dat | this have to be also used with previous one | return to default settings
* Switch# reload | reload commutator