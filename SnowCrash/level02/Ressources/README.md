# Write up

With a `ls -a`, we notice a `level02.pcap` file in the level02 home folder.

PCAP file show packet exchanges and can be read with softwares like WireShark
We download it to have more freedom : `scp -P 4242 level02@192.168.56.101:level02.pcap level02.pcap`

Using this command : `tshark -r level02.pcap -x`
We can clearly see login and password parameters, which we will have to find.

We follow the TCP streams to retrieve the exchanged data : `tshark -r level02.pcap -z follow,tcp,ascii,0`
Which highlight us the password parameter 1 letter per line, each char separated by a 1
We remove the 1s, the new lines and replace dots by spaces : `tshark -r level02.pcap -z follow,tcp,ascii,0 | tr -d '1' | tr -d '\n' | tr '.' ' ' > parsed02`
Which gives us the password in clear : `Password: ft_wandr   NDRel L0L`
But something looks odd, a password usually can't contain spaces, those spaces are therefore unprintable chars.
We follow the TCP streams again, but using the hex charset : `tshark -r level02.pcap -z follow,tcp,hex,0`
Which tell us that the 4 spaces are actually 7f sequences, which are DEL in ASCII.
Giving us the final password : `ft_waNDReL0L`

 
## Softs

- WireShark `sudo apt install tshark`
