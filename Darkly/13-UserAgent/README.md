# User Agent

## Flag

f2a29020ef3132e01dd61df97fd33ec8d7fcd1388cc9601e7db691d17d4d6188

## Description

The html source code contains here a big comment where it's asked to login as a `ft_bornToSec` device (User agent) and from `https://www.nsa.gov` (referer)
Not really a security issue here, but shows that not sanitizing input can be dangerous

## URL

http://192.168.56.101/index.php?page=e43ad1fdc54babe674da7c7b8f0127bde61de3fbe01def7d00f151c2fcca6d1c

## Steps To Reproduce

This command returns a HTML page with the flag in it :
`curl -H "User-Agent: ft_bornToSec" --referer "https://www.nsa.gov/" http://192.168.56.101/index.php?page=e43ad1fdc54babe674da7c7b8f0127bde61de3fbe01def7d00f151c2fcca6d1c`

## Why is it dangerous ?

Printing User Agent can open XSS issues.
Evaluating it can allow Remote Code Execution in the server-side used language.
Checking the referer can prevent multiple security issues, like RFI (Remote File Inclusion) or CSRF (Cross-Site Request Forgery)

## Possible fixes

No particuliar fix here.

## Resources

There is no additional resource for this issue.

## Sources

https://ec.haxx.se/http/http-requests