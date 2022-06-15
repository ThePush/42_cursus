<div align="center">
  <center><h1>Born2beroot 💻</h1></center>

<img src="https://user-images.githubusercontent.com/91064070/147373484-5f9d6a42-38d3-459b-89c3-24ea6e96c580.png" />

## Goal of the project
The first system administration project.

The goal of this project is to set up a safe ssh server on a virtual machine from the scratch and without any graphic interface.

What you will find here is not a perfect solution to follow step by step to achieve this project, those are my notes and some resources (en and fr) to understand what is this project all about.
</div>

## Skills involved
* Set up a well partitioned Debian OS with LVM
* Set up an SSH server and ufw firewall
* Configure AppArmor
* Set a static IP for the server
* Configure sudoers and set a strong password policy
* Use of CRON and Bash scripts

## Table of contents
* [About partitioning and file system](#About-partitioning-and-file-system)
* [Sudo configuration](#Sudo-configuration)
* [SSH setup](#SSH-setup)
* [Set a static IP](#set-a-static-ip)
* [Users and groups commands](#Users-and-groups-commands)
* [AppArmor](#AppArmor)
* [Password Management](#Password-Management)
* [CRON](#CRON)

## About partitioning and file system
[Wiki ubuntu partitions fr](https://doc.ubuntu-fr.org/partitions)

[Debian partitioning tutorial en](https://techencyclopedia.wordpress.com/2020/04/21/debian-10-manual-partition-for-boot-swap-root-home-tmp-srv-var-var-mail-var-log/)

[Debian partitioning tutorial fr](https://www.debian.org/releases/stretch/s390x/ch06s03.html.fr)

[Hard disk partitions explained en](https://www.howtogeek.com/184659/beginner-geek-hard-disk-partitions-explained/)


#### Different kinds of sd

* sdxx = storage-driver
* sd/abcd = slave/master on primary/secondary SATA connection
* sdx1 to sdx4 denominations are used for primary partitions including extended if there is one
* sdx5 will always be the first logical volume of extended partitions on hard-disk sdX, even if the primary partition is only split in one primary / one extended part

#### Different kind of partitions

**Primary** : 
Usually stores OS, applications, settings etc. 
Sometimes called boot partition/volume because it contains informations that the computer uses to start up (boot)
4 primary partitions max or 3 + 1 extended

**Extended** :
Stores logical partitions(volumes)

**Logical** :
Created within the extended partition

[ext4](https://en.wikipedia.org/wiki/Ext4) : file system, logical structure that enables OS to reach informations contained into a file, save them etc. (linux can handle ReiserFS, JFS, HFS as well; NTFS or FAT32 are other file systems for windows)

[LVM](https://en.wikipedia.org/wiki/Logical_Volume_Manager_(Linux)) = Logical Volume Manager

One should never encrypt /boot, as we could not load the kernel from an encrypted partition

Show partitioned system :
```
lsblk
```


List of packages on the computer :
```
dpkg -l
```

## Sudo configuration
>Sudo stands for Superuser Do

Get root :
```
su
```


Install sudo :
```
apt install sudo
```


Create a sudo configuration file :

```shell
sudo vim /etc/sudoers.d/<sudo_config>

# Set max passwords attempts to 3
Defaults	passwd_tries=3


# Add a message in case of incorrect password
Defaults	badpass_message="<message>"


# Mark the file as the sudo log file
Defaults	logfile="/var/log/sudo/sudo_log"


# Sends sudo input and output logs to the file
Defaults	log_input, log_output
Defaults	iolog_dir="/var/log/sudo"


# Set tty for sudo
Defaults	requiretty

# Set the paths that sudo is allowed to use
Defaults	secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"
```

For more informations on requiretty check [this post on stackoverflow](https://stackoverflow.com/questions/67985925/why-would-i-want-to-require-a-tty-for-sudo-whats-the-security-benefit-of-requi)

## SSH setup

[Openclassroom SSH course fr](https://openclassrooms.com/fr/courses/43538-reprenez-le-controle-a-laide-de-linux/41773-la-connexion-securisee-a-distance-avec-ssh)


Secure Shell : tunneling network tool that encrypts datas

SSH : client (e.g. : a web browser)

SSHD : server (daemon)(e.g. : a ...server)

```shell
# Install openssh package
sudo apt install openssh-server

# Install the firewall
sudo apt install ufw

# Install net-tools to get informations about connections
sudo apt install net-tools

# Configure the desired port for the server, uncomment and modify line 15
vim /etc/ssh/sshd_config
:15s/\<#Port 22\>/Port 4242/gc

# Restrict root login, uncomment and modify line 32
:32s/\<#PermitRootLogin prohibit-password\>/PermitRootLogin no/gc>

# Launch SSH
systemctl enable ssh
systemctl status ssh
systemctl start ssh

# Check opened ports
netstat -tulpn | grep sshd
ss -tulpn

# Start firewall and allow port 4242
sudo ufw enable
sudo ufw allow 4242

# Check permissions and delete wanted lines if needed
sudo ufw status numbered
sudo ufw delete <number>

# Connect to server from client through port 4242
ssh <login>@<ip> -p 4242

# Finish session
logout / exit / ctrl+D

# Monitor connections to server
tail -f /var/log/auth.log | grep ssh
```

## Set a static IP
Grab the current IP with :
```
sudo ifconfig
```
Note down the inet (should look like 192.168.x.xxx or 10.0.x.x) and netmask (usually 255.255.255.0).

Then :
```
sudo route -n
```
Note down the default gateway on the line with the UG flag (192.168.x.xxx or 10.0.x.x)

Then :
```
sudo vim /etc/network/interfaces
```
Edit this file from line 12, switch dhcp with static and input your informations, chose an IP between 192.168.1.1 to 192.168.1.255 or between 10.1.1.1 to 10.1.1.255 :
```
iface enpos3 inet static
address <wanted static ip>
netmask <your netmask>
gateway <your gateway>
```
For example :
```
iface enpos3 inet static
address 192.168.1.20
netmask 255.255.255.0
gateway 192.168.1.1
```
Now restart the virtual machine to check that the informations have changed in ifconfig.

Check the result :
```
ss -tulpn
```
The UDP line should have disappeared.

## Users and groups commands
```shell
# Add a user
sudo adduser <username>

# Delete a user
sudo deluser <username>

# Show the user’s line in the passwd file
cat etc/passwd | grep <username>
or
getent passwd <user>

# Create a new group
sudo addgroup <group>

# Delete a group
sudo delgroup <group>

# Adds a user to a group
adduser <username> <group>

# Shows a group's informations
getent group <group>

# Show a user's groups
sudo groups <user>

# Switch to \<username\> user
su <username>

# Change hostname
hostnamectl set-hostname \<new_hostname\>
modify /etc/hosts
```

## AppArmor :

[Wiki Ubuntu AppArmor en](https://wiki.ubuntu.com/AppArmor)

[Wiki Ubuntu AppArmor fr](https://doc.ubuntu-fr.org/apparmor)


AppArmor is a security software that enables the superuser to associate a security profile to each program and manages to restrict it. It locks applications and prevent them to reach other resources than the ones they truly need.

To disable an app profile :
```
sudo ln -s /etc/apparmor.d/<app> /etc/apparmor.d/disable

apparmor_parser -R /etc/apparmor.d/<app>
```

## Password Management

```shell
sudo vim etc/login.defs

# Modify the password days expiration
 #160	PASS_MAX_DAYS 30

# To change the number of days between password modification
 #161	PASS_MIN_DAYS 2

# Days before the user warning message before password expiry
 #162	PASS_WARN_AGE 7
```

Apply these rules to a previously created user with ```sudo chage <user>```

Set password policies :
```shell
sudo apt install libpam-pwquality

sudo vi etc/pam.d/common-password

 #25 password requisite pam_pwquality.so retry=3 minlen=10 ucredit=-1 dcredit=-1 maxrepeat=3 reject_username difok=7 enforce_for_root
```
Checks users' password 's informations :
```
sudo chage -l <user>
```


## CRON 
>CRON stands for Chrono Table.

The system utility cron can be used to schedule programs to run automatically at predetermined intervals.
```
 Example of a job definition :
 .---------------- minute (0 - 59)
 |  .------------- hour (0 - 23)
 |  |  .---------- day of month (1 - 31)
 |  |  |  .------- month (1 - 12) || jan,feb,mar,apr ...
 |  |  |  |  .---- day of week (0 - 6) (Sunday == 0 or 7) || sun,mon,tue,wed,thu,fri,sat
 |  |  |  |  |
 *  *  *  *  * <username>/<command>
```
\* means the job will be performed every minute, hour, day of month, month, day of week

Exemple for this project, the scripts needs to be ran every 10 minutes :
```
*/10 * * * * bash /path_to_file/monitoring.sh | wall
```
The ```wall``` command allows the script to be executed on all tty.

```shell
# Display content of cron table for current user :
crontab -l

# Edit the cron file :
crontab -e

# Prevent cron from running :
sudo systemctl disable cron
sudo /etc/init.d/cron stop
```
