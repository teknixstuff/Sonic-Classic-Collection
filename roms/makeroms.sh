#!/bin/bash
for rom in "$@"
do
	echo "$(basename "$rom" ".${rom##*.}" | tr '[:lower:]' '[:upper:]') ROM \"$rom\""
done