#!/bin/bash
apt update
apt-get install -y git
apt-get install -y \
  ca-certificates \
  curl \
  gnupg \
  lsb-release
mkdir -p /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | gpg --dearmor -o /etc/apt/keyrings/docker.gpg
echo \
  "deb [arch=amd64 signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  $(lsb_release -cs) stable" | tee /etc/apt/sources.list.d/docker.list >/dev/null
apt-get install -y docker-ce docker-ce-cli containerd.io
systemctl enable docker
systemctl start docker
apt-get install -y docker-compose
apt-get install -y openssh-server
systemctl enable ssh
mkdir -p /home/${USER}/data/database
mkdir -p /home/${USER}/data/wordpress
apt-get install -y build-essential
apt-get install -y make
usermod -aG docker $USER
usermod -aG $USER
newgrp docker
newgrp
#ssh-keygen;
#systemctl status sshd;
#systemctl status docker;
