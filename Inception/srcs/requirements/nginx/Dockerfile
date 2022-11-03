FROM alpine:3.16

RUN echo -e "\n[ NGINX ] UPDATING APK..." ; \
    apk update ; \
    echo "[ NGINX ] APK UPDATED" ; \
    echo -e "\n[ NGINX ] UPGRADING APK..." ; \
    apk upgrade ; \
    echo "[ NGINX ] APK UPGRADED" ; \
    echo -e "\n[ NGINX ] INSTALLING NGINX..." ; \
    apk add --no-cache nginx ; \
    echo "[ NGINX ] NGINX INSTALLED" ; \
    echo -e "\n[ NGINX ] INSTALLING OPENSSL..." ; \
    apk add --no-cache openssl ; \
    echo -e "[ NGINX ] OPENSSL INSTALLED\n"

RUN	echo -e "\n[ NGINX ] CREATING SELF SIGNED CERTIFICATE AND PRIVATE KEY..." ; \
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/ssl/private/nginx-selfsigned.key \
    -out /etc/ssl/certs/nginx-selfsigned.crt \
    -subj "/C=FR/ST=Ile de France/L=Paris/O=42 School/OU=42 School/CN=jsemel.42.fr" ; \
    echo -e "[ NGINX ] SELF SIGNED CERTIFICATE AND PRIVATE KEY CREATED\n"

COPY conf/nginx.conf /etc/nginx/nginx.conf

EXPOSE 443

# Launch nginx in foreground to prevent container from exiting
CMD [ "nginx", "-g", "daemon off;" ]

# SOURCES
# https://www.digicert.com/kb/ssl-support/openssl-quick-reference-guide.htm
# https://devopscube.com/create-self-signed-certificates-openssl/
# https://www.ruraldock.com/article/107503083
# https://hub.docker.com/_/nginx/