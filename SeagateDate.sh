#!/bin/bash

# Seagate uses a fiscal year for their calculation which starts on the first Saturday in July (week 1)
# Ref: https://www.digital-detective.net/deciphering-seagate-date-codes/

# For example, the fiscal year 2021 starts on Saturday 4th July 2020 (Date Code 2111) and ends on Friday 2nd July 2021 (Date Code 21527).
# Date Code 13395 was manufactured on 3rd April 2013 (fiscal year 2013, week 39, day 5).

# 1st July 2000 was a Saturday

month=('July' 'August' 'September' 'October' 'November' 'December' 'January' 'February' 'March' 'April' 'May' 'June' 'July')
days=('31' '31' '30' '31' '30' '31' '31' '28' '31' '30' '31' '30' '31')
name=('Saturday' 'Sunday' 'Monday' 'Tuesday' 'Wednesday' 'Thursday' 'Friday')
adj=('1' '7' '6' '5' '4' '3' '2')

year=${1:0:2}
week=${1:2:2}
day=${1:4:1}

[ ${#1} -eq 4 ] && week=${1:2:1} && day=${1:3:1}

echo -n "Year: ${year} Week:${week} Day:${day} -> "

let day--

[ ${year:0:1} == "0" ] && year=${1:1:1}

# February has 29 days in a leap year
let leap=year/4
let leap=leap*4
[ ${leap} -eq ${year} ] && days[7]='29'

let year--
let offset=year*365
let offset+=year/4
let offset%=7
let offset=${adj[${offset}]}

let week--

let count=week*7+day+offset
let m=0
while [ $m -lt 12 ]
do
    [ ${count} -le ${days[$m]} ] && break
    let count=count-${days[$m]}
    let m++
done

[ $m -gt 5 ] && let year++

[ ${year} -lt 10 ] && year="0${year}"

echo "${name[${day}]} ${count} ${month[${m}]} 20${year}"
