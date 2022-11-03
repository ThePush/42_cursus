FROM alpine:3.16

EXPOSE 3306

COPY tools/init_mariadb.sh /tmp/init_mariadb.sh

RUN echo -e "\n[ MARIADB ] UPDATING APK..." ; \
    apk update ; \
    echo "[ MARIADB ] APK UPDATED" ; \
    echo -e "\n[ MARIADB ] UPGRADING APK..." ; \
    apk upgrade ; \
    echo "[ MARIADB ] APK UPGRADED" ; \
    echo -e "\n[ MARIADB ] INSTALLING MARIADB..." ; \
    apk add --no-cache mariadb ; \
    echo "[ MARIADB ] MARIADB INSTALLED" ; \
    echo -e "\n[ MARIADB ] INSTALLING MARIADB-CLIENT..." ; \
    apk add --no-cache mariadb-client ; \
    echo -e "[ MARIADB ] MARIADB-CLIENT INSTALLED\n" ; \
    chmod a+x /tmp/init_mariadb.sh

CMD [ "/tmp/init_mariadb.sh"]
