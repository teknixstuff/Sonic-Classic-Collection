#!/bin/bash
for rom in "$@"
do
	echo "$(basename "$rom" ".${rom##*.}" | tr '[:lower:]' '[:upper:]') ROM \"$rom\""
	echo "$(basename "$rom" ".${rom##*.}" | tr '[:lower:]' '[:upper:]')_PAD ROM { 0 }"
done