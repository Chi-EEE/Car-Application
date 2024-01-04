Set up the following first:

- Wifi - Use the Mobile Hotspot feature of your device
- SSH - Enable
- I2C - Enable

See if Wifi does not connect: [Raspberrypi Stackexchange](https://raspberrypi.stackexchange.com/questions/96736)

Now connect to the Raspberry Pi with SSH

Run the following commands to get the raspberry pi running:
```
sudo apt-get install build-essential
curl -fsSL https://xmake.io/shget.text | bash
source ~/.xmake/profile
```

Run the following commands before cross compilation:
```
sudo apt update
sudo apt upgrade
sudo apt dist-upgrade
```
or
`sudo apt update && sudo apt upgrade && sudo apt dist-upgrade`

Afterwards run `chmod +x ./raspberry_pi` on the new executable

Use [CyberDuck](https://cyberduck.io/) to copy the raspberry_pi folder.