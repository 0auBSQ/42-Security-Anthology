# Input Data Falsification

## Flag

03A944B434D5BAFF05F46C4BEDE5792551A2595574BCAFC9A6E25F67C382CCAA

## Description

A form lacking of server side verification allow us to send invalid values to the database.

## URL

http://192.168.56.101/index.php?page=survey

## Steps To Reproduce

- Inspect the elements of the page.
- Choose a `<select>` and set the `value` of one of its `<option>` to a number higher than 10.
- Click on the modified `<option>`.

## Why is it dangerous ?

You can very easily falsify the survey results (A big clue on the survey page is the 4200 score)
In some cases (not tested on this survey page), you can also inject alphabetic strings to cause server side errors (status 500), which can make the page totally inaccessible and unusable.

## Possible fixes

- Verify (Server side) if the entered value is an integer, and if it's between 1 and 10.

## Resources

There is no additional resource for this issue.
