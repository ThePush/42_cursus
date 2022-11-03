FROM alpine:3.16

EXPOSE 9000

ARG PHP_VERSION=8

RUN echo -e "\n[ WORDPRESS ] UPDATING APK..." ; \
    apk update ; \
    echo "[ WORDPRESS ] APK UPDATED" ; \
    echo -e "\n[ WORDPRESS ] UPGRADING APK..." ; \
    apk upgrade ; \
    echo "[ WORDPRESS ] APK UPGRADED" ; \
    echo -e "\n[ WORDPRESS ] INSTALLING PHP AND REQUIRED MODULES..." ; \
    apk add --no-cache mariadb-client \
    mysql-client \
    wget \
    php${PHP_VERSION} \
    php${PHP_VERSION}-fpm \
    php${PHP_VERSION}-ftp \
    php${PHP_VERSION}-gd \
    php${PHP_VERSION}-phar \
    php${PHP_VERSION}-iconv \
    php${PHP_VERSION}-mongodb \
    php${PHP_VERSION}-zlib \
    php${PHP_VERSION}-mysqli \
    php${PHP_VERSION}-json \
    php${PHP_VERSION}-curl \
    php${PHP_VERSION}-dom \
    php${PHP_VERSION}-exif \
    php${PHP_VERSION}-fileinfo \
    php${PHP_VERSION}-mbstring \
    php${PHP_VERSION}-openssl \
    php${PHP_VERSION}-xml \
    php${PHP_VERSION}-zip ; \
    echo "[ WORDPRESS ] PHP AND REQUIRED MODULES INSTALLED"

COPY tools/init_wordpress.sh /tmp/init_wordpress.sh
# bonus website
#COPY bonus_site/index.html /tmp/index.html

RUN echo -e "\n[ WORDPRESS ] DOWNLOADING WORDPRESS..." ; \
    wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar &> /dev/null; \
    echo -e "[ WORDPRESS ] WORDPRESS DOWNLOADED\n" ; \
    mv wp-cli.phar /usr/bin/wp ; \
    chmod a+x /usr/bin/wp ; \
    chmod a+x /tmp/init_wordpress.sh

WORKDIR /var/www/html

CMD [ "/tmp/init_wordpress.sh" ]

# SOURCES
# https://make.wordpress.org/cli/handbook/guides/installing/