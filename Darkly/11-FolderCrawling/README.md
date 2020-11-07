# Folder Crawling

## Flag

99dde1d35d1fdd283924d84e6d9f1d820

## Description

A genius hid some flug in a folder forest, my professor layton investigation skills found it.
フォルダの森、隠れるぞー！

## URL

http://192.168.56.101/.hidden/

## Steps To Reproduce

The robots.txt file contains ressources that shouldn't be indexed on browsers.
By checking the robots.txt file, we get 2 ressources :
`/whatever`
`/.hidden`

In the whatever folder, we find an htpasswd file containing the root credentials, where the password is... the md5 hash for dragon.
Dammit, we could get the admin part without the hydra.

In the .hidden folder, we find something which looks like a folder maze.
3 layers of 26 folders, which are 26^3 possibilities, we have to find an alternative way to exploit this.

Using a recursive wget :
`wget -r -p -e robots=off http://192.168.56.101/.hidden/`
I can get all the .hidden/ files and folders

We, then read recursively all the README files and exclude the failed messages
`find .hidden/ -name 'README' -exec cat {} \; | grep -Ev "Demande|craquer|toujours|aussi"`

The flag comes after ~5 min, the time to drink a very dark coffee and to think about how many dates we wasn't able to have because we're too busy coding

## Why is it dangerous ?

Hidden or not, the file is accessible for everyone.

## Possible fixes

- Don't hide files directly on your client app, in some languages you can put the sensitive files directly server-side and make a method to access it only as admin from the client.
- If you REALLY want to put sensitive files client-side, you can use a .htaccess file, be aware that requests other than POST or GET can break your .htaccess protection so limit the request methods as well.

## Resources

- robots.txt (Ressource folder)
- htpasswd (Ressource folder)
