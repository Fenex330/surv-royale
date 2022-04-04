#!/bin/sh

if [[ $1 == "--server" ]]
then
    exec bin/surv-royale-server
else
    exec bin/surv-royale-client
fi
