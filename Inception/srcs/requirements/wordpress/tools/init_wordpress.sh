#!/bin/sh

# configure php-fpm to communicate via port 9000
echo -e "\n[ WORDPRESS ] CONFIGURING PHP-FM..." ; \
    sed -i "s/listen = 127.0.0.1:9000/listen = 9000/g" /etc/php$PHP_VERSION/php-fpm.d/www.conf ; \
echo -e "[ WORDPRESS ] PHP-FM CONFIGURED\n"

# wait for mariadb to be ready before starting wordpress setup
while ! mariadb -h$MYSQL_HOST -u$MYSQL_USER -p$MYSQL_PASSWORD $WP_DATABASE_NAME > /dev/null; do
	echo "[ WORDPRESS ] DATABASE NOT READY YET, WAITING..."
	sleep 4
done
echo "[ WORDPRESS ] DATABASE READY"

# core installation
if [ ! -f "index.php" ]; then
	echo "[ WORDPRESS ] INSTALLING WORDPRESS..."
	wp core download --allow-root
	wp config create --dbname=$WP_DATABASE_NAME --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --dbhost=$MYSQL_HOST --allow-root
	wp core install --url=$DOMAIN_NAME --title="$WP_TITLE" --admin_user=$WP_ADMIN --admin_password=$WP_ADMIN_PASSWORD --admin_email=$WP_ADMIN_EMAIL --skip-email --allow-root
	wp user create $WP_USER $WP_USER_EMAIL --role=$WP_USER_ROLE --user_pass=$WP_USER_PASSWORD --allow-root
	wp search-replace http://$DOMAIN_NAME https://$DOMAIN_NAME --allow-root
fi
echo "[ WORDPRESS ] WORDPRESS READY"

# bonus website
#mv /tmp/index.html /var/www/html/index.html

echo "[ WORDPRESS ] STARTING PHP-FPM"
exec php-fpm$PHP_VERSION -F -R

# SOURCES
# https://make.wordpress.org/cli/handbook/how-to-install/
# https://developer.wordpress.org/cli/commands/config/create/