.PHONY: compile run stop

NAME = c_test_image
IMAGE = test

compile:
	@docker build -t $(IMAGE) .

run: compile
	-@$(MAKE) stop --no-print-directory
	-@docker run --name $(NAME) -i $(IMAGE)

stop:
	-@docker kill $(NAME) > /dev/null 2>&1 || true
	-@docker rm $(NAME) > /dev/null 2>&1 || true