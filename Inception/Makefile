USER = jsemel
SRC = srcs/docker-compose.yaml

all:
	@ if [ ! -d /home/$(USER)/data/wordpress ]; then \
		mkdir -p /home/$(USER)/data/wordpress; \
	fi
	@ if [ ! -d /home/$(USER)/data/database ]; then \
		mkdir -p /home/$(USER)/data/database; \
	fi
	@ if ! grep -q "127.0.0.1 $(USER).42.fr" /etc/hosts; then  \
		echo "127.0.0.1 $(USER).42.fr" >> /etc/hosts; \
	fi
	@ if grep -q "#.*127.0.0.1\s\s*$(USER).42.fr" /etc/hosts; then \
		sed -i "s/.*#.*127.0.0.1\s\s*$(USER).42.fr.*/127.0.0.1 $(USER).42.fr/g" /etc/hosts; \
	fi
	@ if grep -q "mv /tmp/index.html /var/www/html/index.html" srcs/requirements/wordpress/tools/init_wordpress.sh; then \
		sed -i "s/.*mv \/tmp\/index.html \/var\/www\/html\/index.html.*/#mv \/tmp\/index.html \/var\/www\/html\/index.html/g" srcs/requirements/wordpress/tools/init_wordpress.sh; \
	fi
	@ if grep -q "COPY bonus_site\/index.html \/tmp\/index.html" srcs/requirements/wordpress/Dockerfile; then \
		sed -i "s/.*COPY bonus_site\/index.html \/tmp\/index.html.*/#COPY bonus_site\/index.html \/tmp\/index.html/g" srcs/requirements/wordpress/Dockerfile; \
	fi
	@ docker-compose -f $(SRC) up --build

bonus: fclean
	@ if [ ! -d /home/$(USER)/data/wordpress ]; then \
		mkdir -p /home/$(USER)/data/wordpress; \
	fi
	@ if [ ! -d /home/$(USER)/data/database ]; then \
		mkdir -p /home/$(USER)/data/database; \
	fi
	@ if ! grep -q "$(USER).42.fr" /etc/hosts; then  \
		echo "127.0.0.1 $(USER).42.fr" >> /etc/hosts; \
	fi
	@ if grep -q "#.*127.0.0.1\s\s*$(USER).42.fr" /etc/hosts; then \
		sed -i "s/.*#.*127.0.0.1\s\s*$(USER).42.fr.*/127.0.0.1 $(USER).42.fr/g" /etc/hosts; \
	fi
	@ if grep -q ".*#.*COPY bonus_site\/index.html \/tmp\/index.html" srcs/requirements/wordpress/Dockerfile; then \
		sed -i "s/.*#.*COPY bonus_site\/index.html \/tmp\/index.html.*/COPY bonus_site\/index.html \/tmp\/index.html/g" srcs/requirements/wordpress/Dockerfile; \
	fi
	@ if grep -q ".*#.*mv \/tmp\/index.html \/var\/www\/html\/index.html" srcs/requirements/wordpress/tools/init_wordpress.sh; then \
		sed -i "s/.*#.*mv \/tmp\/index.html \/var\/www\/html\/index.html.*/mv \/tmp\/index.html \/var\/www\/html\/index.html/g" srcs/requirements/wordpress/tools/init_wordpress.sh; \
	fi
	@ docker-compose -f $(SRC) up --build

stop:
	@docker-compose -f $(SRC) stop

clean:
	@docker-compose -f $(SRC) down

fclean: clean
	@ if [ -d /home/$(USER)/data/wordpress ]; then \
		rm -rf /home/$(USER)/data/wordpress; \
	fi
	@ if [ -d /home/$(USER)/data/database ]; then \
		rm -rf /home/$(USER)/data/database; \
	fi
	@ if grep -q "$(USER).42.fr" /etc/hosts; then  \
		sed -i '/$(USER).42.fr/d' /etc/hosts; \
	fi

sn:
	@docker exec -it nginx sh

sm:
	@docker exec -it mariadb sh

sw:
	@docker exec -it wordpress sh

destroy: fclean
	@- docker stop $(docker ps -aq)
	@- docker kill $(docker ps -aq)
	@- docker rm -v $(docker ps -aq)
	@- docker rmi $(docker images -aq)
	@- docker volume rm $(docker volume ls -q)
	@- docker network rm $(docker network ls -q)
	@- docker system prune -af

build: all
re: fclean all

.PHONY: all bonus stop clean fclean sn sm sw destroy build re