#!/bin/bash
function get_num()
{
    count=-1


    for file in $folder/dev/sd?
    do
        echo $file
        ((count++))
    done

    read -p "Which disk you want to download?(0:$count): " num
    return $num
}

get_num
num=$?
index=0

for file in $folder/dev/sd?
do
    if [ "$index" == "$num" ]; then
        read -p "Please confirm you want to download bin to $file? (Y/N): " confirm
        while [ "$confirm" != "n" ] && [ "$confirm" != "N" ] && [ "$confirm" != "y" ] && [ "$confirm" != "Y" ]
        do
            read -p "Please confirm you want to download bin to $file? (Y/N): " confirm
        done
        while [ "$confirm" == "n" ] || [ "$confirm" == "N" ]
        do
            get_num
            num=$?
            read -p "Please confirm you want to download bin to $file? (Y/N): " confirm
        done
        if [ "$confirm" == "y" ] || [ "$confirm" == "Y" ]; then
            ./imxdownload ../bin/*.bin $file
            exit 0
        fi
    else
        ((index++))
    fi
done