# Remote File Inclusion - DataURI (Document forgery)

## Flag

928D819FC19405AE09921A2B71227BD9ABA106F9D2D37AC412E9E5A750F1506D

## Description

By clicking on the NSA picture, I'm moved to this page : http://192.168.56.101/?page=media&src=nsa
By changing the src value, I get a wrong answer gif and a <object> tag wrapper containing the local ressource with the src value as URI.
Result is splitted in 2 tr, each tr containing a td.
With src = nsa :
- First td : Title (File: nsa_prism.jpg)
- Second td : `<object>` with data=http://192.168.56.101/images/nsa_prism.jpg
With any other src :
- First td : Wrong answer gif
- Second td : `<object>` with data=src

I first expected a LFI (Local File Inclusion) or an url RFI (Remote File Inclusion by external url) but :
- `javascript:` is escaped
- `php://` wrappers are not escaped, but useless because no include()/require() call
- `http://` and `https://` are escaped
- `../` isn't escaped, but index.php is displayed, files are therefore located in the root folder.

After some researches, I was able to inject data using the data: wrapper, showing that a RFI by DataURI is possible
For exemple :
`data:text/html,<script>alert('test');</script>`
Display an alert with `test` displayed

We try a PHP injection :
`data:text/html,<?php phpinfo();`
But too bad (https://image.noelshack.com/fichiers/2017/33/5/1503085226-pas-de-chance.png)
If there is a `<?` tag, the whole content is automaticaly escaped to comment.

ASP tag injection also doesn't work, PHP version is therefore at least 7.0.0
`data:text/html,<% phpinfo(); %>`

I also tried the external RFI (and bypassed the `http://` escape) with concat function in javascript, but X-Frame-Options is sadly set to sameorigin so we can't exploit the external RFI here.
`data:text/html,<script>window.location="ht".concat("tp://google.fr");</script>`

After some unsatisfying attempts, I decided to test my old payload again, but with the base64 option on.
And surprise, the first payload got me the flag.

## URL

http://192.168.56.101/?page=media&src=YOUR_PAGE

## Steps To Reproduce

Access this URL to get the flag directly :
http://192.168.56.101/?page=media&src=data:text/html;base64,PHNjcmlwdD5hbGVydCgndGVzdCcpOzwvc2NyaXB0Pg==

## Why is it dangerous ?

If you feel like a ninjavascript (Popular Samuraxmls who live in this beautiful country of Japhpan), you can forge a file directly in the data: wrapper and execute your code like if it was directly on the server, depending of the language, you can, for exemple :
- Show the pages source code (Especially powerful in php)
- Forge malicious AJAX requests and bypass CORS/sameorigin filters
- And lots of other cool things 

## Possible fixes

- Limit user input to an alphanumerical charset, and add manualy the jpg extention (No null byte in php7)
- If the number of pictures is low enough, it's also possible to make a conditional display in raw code like for the nsa picture, using for exemple a key/value dict.
- If the number of pictures is high (or if you want to display images user uploaded as well), follow the 1st fix, then while uploading images give them an unique md5 hash as name and convert them to jpg.

## Resources

There is no additional resource for this issue.

## Sources

https://developer.mozilla.org/fr/docs/Web/HTTP/Basics_of_HTTP/Data_URIs
https://www.php.net/manual/fr/language.basic-syntax.phptags.php
https://blog.clever-age.com/fr/2014/10/21/owasp-local-remote-file-inclusion-lfi-rfi/