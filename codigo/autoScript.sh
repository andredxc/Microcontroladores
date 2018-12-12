#!/bin/bash

set -e

show_help () {

    echo -e "\n  autoScript: add or remove initialization scripts from Galileo remotely"
    echo "  Usage:
            - First parameter must be the script path
            -h: Show this
            -r: Remove script
            -n: Galileo network name (default is 'galileo')
            -t: Show Galileo dirs containing scripts
            -f: Script path
            "
}

flag_remove=0
script_path=""
galileo_name="galileo17"
basename=""
show_g_dirs=0

while getopts "h?r?n:?t?f:?" opt; do
    case "$opt" in
    h|\?)
        show_help
        exit 0
        ;;
    r)
        flag_remove=1
        ;;
    n)
        galileo_name=$OPTARG
        ;;
    t)
        show_g_dirs=1
        ;;
    f)
        script_path=$OPTARG
        ;;
    esac
done

# Show Galileo dirs containing the script
if [ $show_g_dirs -eq 1 ]
then
    ssh root@"$galileo_name" 'echo -e "\n\t~/init_scripts";
        ls -l ~/init_scripts;
        echo -e "\n\t/etc/init.d";
        ls -l /etc/init.d;
        echo -e "\n\t/etc/rc0.d";
        ls -l /etc/rc0.d'
    exit 1
fi

# Manage Galileo scripts
basename=$(basename "$script_path")

if [ $flag_remove -eq 0 ]
then
    # Add script
    if [ ! -f "$script_path" ]; then echo "Error, file '"$script_path"' does not exist!"; exit 0; fi;
    scp "$script_path" root@"$galileo_name":~/init_scripts
    ssh root@"$galileo_name" 'cd ~/init_scripts;
        cp '$basename' /etc/init.d;
        chmod +x /etc/init.d/'$basename';
        update-rc.d '$basename' defaults;
        reboot'
else
    # Remove script
    ssh root@"$galileo_name" 'cd /etc/init.d;
        update-rc.d -f '$basename' remove'
fi
