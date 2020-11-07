# Write up

In the home folder, we have an executable `level06` an a PHP file `level06.php`
The executable execute the php file

On the php file : 
- The $z parameter of the x function is unused
- The y function does the following :
-- Replace all the "." occurences by " x "
-- Replace all the "@" occurences by " y"
-- Return the operation result
- The x function does the following :
-- Get the argv[1] file contents and store it in $a
-- Replace a "premade" function call patern (for exemple `[x test test2]`) by y(params), the regex uses the e (eval) option so the code may be vulnerable here
-- Replace all [ by ( and ] by )
-- Returns the value and print it

To be able to execute the `getflag` command within the script, we will have to inject it through the /e regex, but the replace string
is wrapped around the y function, we will have to find a way to execute it prior to the y function call.

We use the Complex syntax here to inject the following payload : `[x {${shell_exec(getflag)}}]`
Which get us the flag.

## Sources

https://stackoverflow.com/questions/3642156/how-to-use-constants-with-complex-curly-syntax