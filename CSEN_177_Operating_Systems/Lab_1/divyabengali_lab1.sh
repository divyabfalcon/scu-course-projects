# Name: Divya Bengali
# Date: Wednesday - Sep 24th
# Title: Lab1 – Step 3
# Description: This program computes the area and perimeter using the circle's given radius.

#!/bin/sh

#Area and perimeter are calculated using functions
area(){
	echo "3.14 * $1 * $1" | bc
}

perimeter(){
	echo "3.14 * 2 * $radius" | bc
}

echo "What's the radius of your circle"
read radius

#Detects to ensure that the user inputted number is positive.
if [ $radius -le 0 ]; then
	echo "Please enter a positive radius"
	exit 1
fi
echo "The area is $(area $radius)"
echo "The perimeter is $(perimeter "$radius")"
