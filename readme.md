
# d2botNET - Diablo 2 Botting Engine

*This project was started ~2003 and is posted for historical purposes only.*

## Repo Contents
- Core source files (0.5.0)
- Pathing (2.0.3, not most recent version)
- BotOS (version doesn’t matter, it was experimental)

## How it All Started

I started coding for Diablo 2 botting back in d2jsp days. d2jsp being a JavaScript based botting engine. At the time there was no such thing as getting your character from point A to point B without a whole lot of guessing - and a whole lot more of dying - which made almost all bots useless.

Through a lot of reverse engineering and trial and error I finally found all the memory structures that held world info, such as tiles, rooms & areas, where you can walk, where you can't, etc. This paved the way for true pathfinding for your character, and true botting, anywhere in the game world.

I started with a pathfinding d2hackit module that could be called from d2jsp. This worked well and was fast, a fraction of a second to calculate everything.

After a while the author of d2jsp removed support for d2hackit. I provided him with all the info necessary to make area and room info available to scripts, and from there I created a JavaScript pathfinding library. OMG, it was SLOW. Going from compiled C++ to JavaScript on a circa 2002 computer and processing an entire diablo 2 area to find a path, avoiding monsters, etc, the game would freeze for up to 60 seconds!!!!

Anyhow, I started to have some differences of opinion (to put it mildly) with the author of d2jsp and decided to move away from d2jsp completely. 

Another take on the history of d2jsp, d2bs, and d2botNET by lord2800 can be found at the end of this readme.

## About the Core

I wanted to integrate a .NET managed language into an unmanaged environment, making it easier for new developers to get started.

A natural choice was Managed C++ to bridge that gap. However, at least at the time, managed C++ (.NET 1.1/2) did not support __fastcall so in came creating my own __fastcall using assembly!

The source shows a good mixture of classic C, MC++, and ASM.

The initial source used was from the d2bs C project, by lord2800 et al.



## Why did I Upload This?

I had been looking for the source code for a long time, and I finally came across it - although not the latest version - 
and since the source was never published years ago as it was meant to be, I have done
so now.

## Notes 

Wow, the amount of work the team and all the plugin developers put into this was truly amazing. It was a fun time, I learned a lot, and made a lot of awesome friends.

I am trying to find the official developer list and will post it here when I find it.

# Miscellaneous

## Original Website Description of botNET

_botNET is a new botting system. It is much like d2jsp or d2bs in that it is extendable thru scripts, but it is not based on JavaScript. botNET is based on the .NET framework, and as such, you can write bots or libs in any .NET language including but not limited to C#, C++, VB, JScript, Python.NET, Perl.NET, etc._

_With it being based on a compiled language it runs far faster than any other botting system of the past. Current tests show it to be anywhere from 50 - 100 x faster than any others._

_Developing Bots and libs for botNET is quite simple too, no need for illegal software (vs.net). You can download the .NET framework SDK, which is free from Microsoft, and then download SharpDevelop which is a 100% free opensource IDE for VB and C#. I will provide links below. Simply reference the library dll in your project and start developing. I will be writing up a developers guide as time permits._

_Our plan is for botNET to be free for anyone to download and use. Any bot dll's a developer makes and would like to host on our new site to come, would need to submit source code to us for our reviewers to parse through and compile. This ensures that any Bot dll's are not intentionally malicious._

_With the introduction of .NET into a botting system it gives us a great deal of power. Ever wanted an email client in diablo, no prob. Want your irc in diablo, no prob! Want real-time bot comm, no prob! Want customized gui front ends, again no prob! Need database access, no problem! Did I mention that you can make bots too?!!??   Since the .NET framework provides so much innate functionality, the possibilities are now truly endless for bot developers. Plus there is a lot of pre written open source code for pretty much anything you would need to integrate already._

_Hope this helps to make you more fully appreciate what botNET is all about. Feel free to ask any questions._
_

## History of d2jsp, d2bs, d2botNET, and more by lord2800

Let me tell you a little story about a project called JED and how njaguar ruined a perfectly good community project with his greed... 

It all started one day, when Morgalis announced that her "crack team of coders" (aka smoke) had written a bot platform using the SpiderMonkey javascript engine, called JED. It was posted far and wide, and drew in quite a bit of talent to write scripts to do various botting tasks. [1] All was going well, when an unknown person by the handle of njaguar decided he could do better. He asked Morgalis if he could join the team developing the core of JED, and was denied because no one knew who the hell he was. Undeterred, he found out that it was using SpiderMonkey, and set to work writing his own version, using publicly available source code from Mousepad's maphack. After several days, he had a somewhat working alpha that did little more than run a script and print in the game. That's where, as they say, things got interesting. 

He began a campaign against JED and its manager and creator (Morgalis and smoke, respectively). He promised that d2jsp, his newly named bot, would be open source. He promised that he would listen to the people writing scripts, and never break backwards compatibility unless there was an extremely compelling reason to. He dragged other actually talented coders, such as Syadasti and a few others, to his cause. He started a website, but having no web skills to speak of, he brought in a few people to help: Raeky, HolyCoitus, and a few others. They managed to make the website into something usable, but not very pretty. It started as a wiki, and only lasted as such for a few weeks. Eventually, he licensed and installed IPB (Invision Power Board) on the website. Thus, the birth of d2jsp forums. [2] 

At this time, njaguar finally had a core that was semi-useful (it was capable of simple tasks like running pindleskin, but nothing even remotely complex like running mephisto), but he wasn't satisfied. He pushed Syadasti out of the way, for unknown (to me, anyway) reasons. He became a lot more closed minded, and eventually stopped listening to the coders entirely, making up his own damn mind about how the d2jsp API should function. Eventually, he entirely broke API compatibility. Anyone who complained was banned. Only a handful of people were allowed to know what was going to change beforehand; those he had personally chosen as his "elite" coders (most of them were first-year computer science students at best, and could barely code their way out of a paper bag). 

Now, during this time period, the JED project was in decline. As an attempt to revitalize it, Morgalis had allowed the JED source code to be open sourced, but that failed as well. [3] She tried bringing in other coders to help, but nothing could stop d2jsp's popularity at this point -- not even having a better product. Ultimately, she and everyone else gave up on the project. 

njaguar, however, was on a roll. With the fall of JED, he decided that now was a good time to completely disregard the input of everyone except a few very individuals. He broke the API with impunity. He kicked everyone but himself out of the core development "team", and he claimed "he was waiting for 1.0" before he was going to release the source code. Hindsight tells us that he was planning on monetizing d2jsp from the start. However, since he still didn't have enough control over the botting market (there was another competitor available still -- JED's code was open source), he waited until the next patch. Before long, people such as mattlant had come up with a solution to the problem of d2jsp path finding. Using bits and pieces of gathered knowledge about how d2 lays out areas, and building on the work of others, mattlant designed a path finder for d2jsp. Almost overnight, it became the single most important bit of code in every single script. And njaguar had not one single thing to do with it. 

Things went well for a time. New features were added, new bots were made, and eventually njaguar decided to take a break from the core to work on the website himself. Of course, he knew nothing about web programming, so instead of learning by playing and then reading up on things like security and such, he jumped head first in and started working on a "forum gold" system. The original system behaved like so: For each post, you got 1 gold; administrators and certain moderators could hand out gold whenever they wanted to whomever they wanted. You could only spend gold on certain "items" that did things like change the display color of your name or change your title. People liked this idea, and soon forum gold became desirable. People were willing to trade in-game items for forum gold, and njaguar didn't even attempt to regulate it. [4] 

Then came patch 1.10. Mousepad, being the only hacker still hanging around who would give njaguar any information (he had chased off everyone else), basically handed njaguar the updated function offsets/ordinals, data structures, and even his protection scheme. This was when njaguar got greedy. He decided that all future versions of d2jsp would be pay-per-use, and used mousepad's system to do it. [5] With that in place, he started completely ignoring everyone but his "elite" coders (who, by now, had all been changed out for "new" coders who still couldn't code their way out of wet paper bags, except now they weren't even CS students). He decided that even though there were a lot of potential coders who were talented, if they didn't pay the Paul Tax, they didn't play. This pissed off a good portion of the remaining semi-talented coders in the community (myself included), and so they left. 

Much of the information from this point on is secondhand information, and I can't guarantee the accuracy and/or timeline placement of all of it. 

Of the coders left, the bulk of the talent was concentrated on mattlant's new project: botOS. It was a full game bot that used object-oriented techniques to abstract away much of the pain in njaguar's API. [6] njaguar didn't seem to take too kindly to the fact that mattlant asked for donations on his work (since he apparently wasn't on the "approved" "elite" coders list), and after some conflicts that I was never made entirely privy to, mattlant decided to pack up and leave. He pulled all his work from d2jsp's website (including botOS and his path finding code) and demanded an immediate cease-and-desist on all coders using his libraries. njaguar, realizing that he had to do something, decided to do what he does best: he asked mousepad for a solution. That's when d2jsp got the crappy pathfinding API it has. Problem seemingly solved, njaguar again turned his sights to what he really wanted: money. He decided to close all the existing (known) loopholes in the forum gold system, and removed everyone but his privilege of giving forum gold. 

With the pesky problem of distribution out of the way, njaguar started giving "rewards" of forum gold to people who "donated" money to him. This continued on for a considerable amount of time, unchecked. At some point in mid-1.10, a group of somewhat experienced coders (Mace, ApacheChief, Glorfindel, myself, Ninjai, and a handful of others) decided to make a d2jsp-like clone, called d2bs. After much trial and error, we got to the point that njaguar was at just before the fall of JED. We didn't expect much, but we got considerably far (given that this was the first major project for most of us); unfortunately, we decided to be too much of a d2jsp clone, and copied its poorly designed API. This also drew the attention of mattlant, who used the base of d2bs to create d2botnet. His was designed in .NET 1.1, however, so the two projects were mostly incompatible. 

After a time, both the d2bs and d2botnet projects faded into obscurity. D2bs because of a lack of interest, and d2botnet because of a lack of time. This left users with only one botting system again: d2jsp. With his stranglehold complete, njaguar decided he'd had enough working on the core, and that it was "good enough" as it was, so new updates became more and more scarce. There were still plenty of bugs in both the bots and the core, but people had little other choice than to use them. Patch 1.11 came along, and with it came Warden. 

When 1.11 came out finally, Blizzard had decided to introduce a new protection scheme called Warden. It ran as a separate, downloadable piece of code, meaning that Blizzard could change their protection scheme any time they pleased. Mousepad, as usual, gave njaguar his code, but had decided he wanted to keep his Warden protection updates to himself, for some unknown reason. After d2jsp was quickly marked as a bannable program, njaguar took the money he made and ran. He claimed that d2jsp was for single player use only, and how dare those users run it on battle.net where it was against the TOS! He acted as if he'd been in the right the whole time, and it was those pesky users who were the ones fucking everything up. In other words, njaguar pushed the blame onto everyone but him. 

This is where I get back into the picture, and this information is firsthand again. 

This is when d2jsp shifted focus into the site it is today. With d2jsp (the bot) basically gone, njaguar sells forum gold for money. He barely does any actual work to speak of, except to make appearances and pretend he's some sort of rock star whom everyone should look up to. It was later in patch 1.11b that an up-and-coming hacker named Sheppard decided to revive d2bs. After updating the function offsets/ordinals/structs, he took it upon himself to take the project under his wing and continue it. Given that d2bs is licensed under the GPL, he has managed to raise a talented community of scripters (and the community has actual talent, not pretend talent like d2jsp had) under the promise that d2bs will always and forever be open source. They can make any changes to the API that they deem necessary, and they can even fork the project to create their own work, if they desire. These are all things that njaguar promised, but never delivered on. 

Unfortunately, patch 1.12 is out, and d2bs is currently down for the count, but Sheppard is hard at work, fixing it as best as possible. He decided that the current code was nearly unmaintainable, and is in the process of rewriting the entire thing, which is part of what's keeping it from being updated as of yet. 

How has njaguar responded to all of this? He hasn't updated, and won't be updating, d2jsp to meet the new patch. So all the people who paid for it (I don't care if it was called a donation, it's still payment in every legal sense) are now screwed for using it. They can't use it on battle.net, because it results in a ban (when Warden is turned on). They can't use it with the new 1.12 feature (no cd required to play), because it's not updated. They're basically screwed, and njaguar won't do a thing for them. 

Now tell me, would you respect a man who sold you a defective product? 

[1] I even wrote a few scripts for JED. I unfortunately don't have them any more, but I distinctly remember having a pindle script, a leechbot, and had invented the now-unfortunately-all-too-common method of storing the configuration parameters inside of the script, instead of in a separate file. 

[2] As an interesting sidenote, njaguar wasn't even registered for his own website's forums for quite some time. In fact, I have an older account than he does. 

[3] For the interested, here's the SF.net project.page for JED. As you'll notice, by that time, quite a few others had committed code to it, including such famed people as Dan_Goon and bootyjuice. Also, if you notice, JED uses d2hackit! as its loading system. Almost all good hacks (the only major exception is mousepad's maphack) used d2hackit! at that point, including d2jsp. 

[4] Originally, forum gold was supposed to be simply a toy to play with. It wasn't until later that njaguar saw the real potential of it and started abusing his position as head administrator and made it into what it is today. 

[5] Notice the recurring trend here? There isn't a single bit of real work that njaguar has done so far. As I recall, he even had Raeky and HolyCoitus helping him code the forum gold system. 

[6] Interestingly, the botOS source code seems to still be available.
