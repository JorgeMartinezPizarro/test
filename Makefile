.PHONY: compile run

compile:
	@docker build -t test .
run:
	@docker run -i test /app/run
