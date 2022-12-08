<div align="center">
  <center><h1>ft_irc 💬</h1></center>
  <img src="https://www.simplilearn.com/ice9/free_resources_article_thumb/Botnet_3.png" width="450">

## Goal of the project

This project is about creating our own [IRC](https://en.wikipedia.org/wiki/Internet_Relay_Chat) server.

We used [IRSSI](https://irssi.org/) to connect to our server and test it.

Project made in collaboration with [egeorgio3000](https://github.com/egeorgio3000)
</div>

## Skills involved
* Unix
* Rigor
* Network & system administration
* Object-oriented programming


## Usage

```shell
cd ft_irc/ && make
```
```shell
./ircserv <port> <password>
```

EXAMPLE:
```shell
./ircserv 6667 password
```
Then inside IRSSI, connect to the server:
```shell
/connect <ip> <port> <password> <nickname>
```

![image](https://user-images.githubusercontent.com/91064070/206379114-d5f64b50-b943-46e1-b6e5-759e50af25c2.png)

Fully functional with netcat as well:

![image](https://user-images.githubusercontent.com/91064070/206376759-d3e6f46b-cfae-4ebb-998f-9d6ea73a24a3.png)


## Commands supported

* `/nick <nickname>`: change nickname
* `/join <channel>{,<channel>} [<key>{,<key>}]`: join a channel
* `/part <channel>{,<channel>}`: leave a channel
* `/msg <target> <message>`: send a private message to a user or a channel
* `/list`: list all channels
* `/who <target>`: list users
* `/whois <target>`: get information about a user or a channel
* `/invite <nickname> <channel>`: invite a user to a channel
* `/motd`: print the message of the day
* `/notice <target>{,<target>} <text to be sent>`: send a notice to a user or a channel
* `/lusers`: print the number of users connected to the server
* `/topic <channel> <topic>`: set a topic for a channel (channel operators only) / print channel topic
* `/kick <channel> <nickname>`: kick a user from a channel (channel operators only)
* `/ban <nickname>`: ban a user from a channel (channel operators only)
* `/oper <nickname> <password>`: give operator status to a user (default is admin admin after connecting with 'mike' as nickname)
* `/kill <nickname> <reason>`: disconnect a user from the server (IRC operators only)
* `/restart`: restart the server (IRC operators only)
* `/wallops <message>`: send a message to all users connected to the server (IRC operators only)

## Modes supported

### Channel modes

* `+i`: invite only
* `+m`: moderated
* `+n`: no external messages
* `+p`: private
* `+s`: secret
* `+t`: topic settable by channel operators only
* `+k <key>`: set a key for the channel
* `+o <nickname>`: give channel operator status to a user
* `+l <limit>`: set a user limit to the channel
* `+b <nickname>`: ban a user from the channel
* `+v <nickname>`: give voice to a user

### User modes

* `+i`: invisible
* `+w`: receive wallops
* `+o`: IRC operator