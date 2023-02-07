#!/bin/bash

SERVER_CONFIG="https://my.surfshark.com/vpn/api/v1/server/configurations"
CONFIG_INSTALL_DIR="/etc/openvpn"
INSTALL_DIR="/usr/bin"
CONFIG_DIR_NAME="server_config"
PROGRAM_NAME="surfshark-connect"
CONFIG_ZIP_NAME="configurations"

echo -e "\nDownload server configurations to $CONFIG_INSTALL_DIR"
if [[ -d "$CONFIG_INSTALL_DIR" ]]; then
    sudo mkdir $CONFIG_INSTALL_DIR
fi

if [[ -f "$CONFIG_INSTALL_DIR/$CONFIG_ZIP_NAME" ]]; then
    sudo rm -f $CONFIG_INSTALL_DIR/$CONFIG_ZIP_NAME
fi
sudo wget -P $CONFIG_INSTALL_DIR/ $SERVER_CONFIG

echo "Unpacking......"
sudo mkdir $CONFIG_INSTALL_DIR/$CONFIG_DIR_NAME
sudo unzip $CONFIG_INSTALL_DIR/$CONFIG_ZIP_NAME -d $CONFIG_INSTALL_DIR/$CONFIG_DIR_NAME

echo "Compiling and installng surfshark-connect......"
make
sudo cp ./$PROGRAM_NAME $INSTALL_DIR/

echo -e "\nScript finished running\n"
