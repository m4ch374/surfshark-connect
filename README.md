# surfshark-connect

## :book: Description
### Streamlines the process of connecting to `Surfshark VPN` via `openvpn`

* No more copy and pasting server config
* No more entering username and password manually everytime on login

## :sunglasses: Installation 

1. Install prerequisites
```
sudo dnf install make git openvpn unzip
```

or 

```
sudo apt-get install make git openvpn unzip
```

2. Clone this repository:
```
git clone https://github.com/m4ch374/surfshark-connect.git
```

3. Navigate to the repo
```
cd surfshark-connect
```

4. Install using install.sh
```
sh ./install.sh
```

The program is installed to the directory: `/usr/bin/`

## :robot: Commands

The program connects to TCP server of a given location code by default:
```
sudo surfshark-connect <location_code>
```

To connect to UDP server instead:
```
sudo surfshark-connect --udp <location_code>
```

To list all location code:
```
sudo surfshark-connect --list
```

To edit username:
```
sudo surfshark-connect --username <username>
```

To edit password:
```
sudo surfshark-connect --passwd <password>
```

## :thinking: How to I get my credentials?

1. Navigate to this website: `https://my.surfshark.com`
2. Login and click `Manual Setup` under the tab `VPN`
3. Choose `Desktop or mobile` and click on `openvpn`

## :warning: **Caution!** :warning:

The username and password is stored as **plaintext files** in `/etc/openvpn/login.conf`  

#### USE IT AT YOUR OWN RISK!
