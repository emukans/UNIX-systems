#!/usr/bin/env bash

random_number=$(( $RANDOM % 100 + 1 ))
number_of_tries_left=10
is_user_correct=false

echo "Guess my number from 1 to 100:"

while [ $number_of_tries_left -ne 0 ]; do
    read guess

    if [ $guess -eq $random_number ]; then
        is_user_correct=true
        break
    fi

    if [ $guess -gt $random_number ]; then
        echo "My number is less than yours"
    else
        echo "My number is greated than yours"
    fi

    number_of_tries_left=$((number_of_tries_left - 1))
    echo "Number of tries left: $number_of_tries_left"
done


if $is_user_correct; then
    echo "You won. Congratulations."
else
    echo "You suck!"
fi

echo "Guessed number: $random_number"
