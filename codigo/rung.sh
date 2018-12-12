#!/bin/bash

# $1 -> Executable path
# $2 (optional) -> Galileo username ('micros' by default)
# $3 (optional) -> Galileo network name ('galileo' by default)

show_help () {

    echo "Usage: ./rung <exec_path> <?username> <?network_name>"
    echo -e "\tFields marked with '?' are optional"
}

username="micros"
galileo_name="galileo17"

if [ -z "$1" ]
then
    show_help
    exit 0
fi

if [ ! -z $2 ] ; then username=$2; fi
if [ ! -z $3 ] ; then galileo_name=$3; fi

scp "$1" "$username"@"$galileo_name":~/execs
ssh "$username"@"$galileo_name" 'cd ~/execs; ./'$(basename "$1")''
