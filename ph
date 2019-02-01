#!/bin/bash
# Usage ph new name number to add to the list or
# ph name to get a phone number

PHONELIST=.phonelist.txt

# If no command line param then error

if [ $# -lt 1 ] ; then
    echo "Usage:"
    echo "./ph name: To get phone number" 
    echo "./ph new name phone number: to add to the database."
    exit 1
fi

# Adding new phone number

if [ $1 = "new" ] ; then
    shift
    echo $* >> $PHONELIST
    echo $* added to database
    exit 0
fi

# Handling case with no entries
if [ ! -s $PHONELIST ] ; then
    echo "No names in the phone list yet."
    exit 1
else
    grep -i -q "$*" $PHONELIST
    if [ $? -ne 0 ] ; then
        echo "Sorry, that name was not found in the phone list"
        exit 1
    else
        grep -i "$*" $PHONELIST
    fi
fi
exit 0
