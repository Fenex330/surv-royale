#!/bin/sh

if [$1 == "--server"] then
    exec surv-royale-server
else
    exec surv-royale-client
fi
