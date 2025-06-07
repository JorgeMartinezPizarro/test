.PHONY: compile run

NAME=c_test_image

compile:
	@docker build -t test .
run:
	-@make stop --no-print-director
	-@docker run --name ${NAME} -i test
stop:
	-@docker kill ${NAME}  > /dev/null 2>&1 || true
	-@docker rm ${NAME}  > /dev/null 2>&1 || true
