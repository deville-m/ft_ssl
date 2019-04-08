#!/bin/zsh
tee >(openssl sha -$1 $2) > >(./ft_ssl $1 $2)
