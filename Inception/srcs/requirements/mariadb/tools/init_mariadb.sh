#!/bin/sh
if [ ! -d "/run/mysqld" ]; then
    mkdir -p /run/mysqld
    chown -R mysql:mysql /run/mysqld
fi

if [ ! -d "/var/lib/mysql/mysql" ]; then

    chown -R mysql:mysql /var/lib/mysql

    echo "[ MARIADB ] CREATING DATABASE..."
    mysql_install_db --basedir=/usr --datadir=/var/lib/mysql --user=mysql --rpm > /dev/null
    echo "[ MARIADB ] DATABASE CREATED"
    echo -e "\n[ MARIADB ] CONFIGURING DATABASE..."
    tmpfile=`mktemp`
    if [ ! -f "$tmpfile" ]; then
        return 1
    fi

    cat << EOF > $tmpfile
USE mysql;
FLUSH PRIVILEGES;
DELETE FROM mysql.user WHERE User='';
DROP DATABASE test;
DELETE FROM mysql.db WHERE Db='test';
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');
CREATE DATABASE IF NOT EXISTS $WP_DATABASE_NAME;
ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';
GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost';
CREATE USER '$MYSQL_USER'@'%' IDENTIFIED by '$MYSQL_PASSWORD';
GRANT ALL PRIVILEGES ON $WP_DATABASE_NAME.* TO '$MYSQL_USER'@'%';
FLUSH PRIVILEGES;
EOF
    mysqld --user=mysql --bootstrap < $tmpfile
    rm -f $tmpfile
    echo "[ MARIADB ] DATABASE CONFIGURED"
else
    echo "[ MARIADB ] DATABASE ALREADY CONFIGURED"
fi

# enable connection from outside
sed -i "s/skip-networking/# skip-networking/g" /etc/my.cnf.d/mariadb-server.cnf
#  sed -i "s/skip-networking/skip-networking=0/g" /etc/my.cnf.d/mariadb-server.cnf
sed -i "s/.*bind-address\s*=.*/bind-address=0.0.0.0/g" /etc/my.cnf.d/mariadb-server.cnf

echo -e "\n[ MARIADB ] STARTING MYSQL..."
exec mysqld --user=root

# SOURCES
# https://mariadb.com/kb/en/configuring-mariadb-for-remote-client-access/
# https://www.fosstechnix.com/tutorial/mysql/mysql-bind-address/
# https://bobcares.com/blog/mysql-bind-address-ubuntu/