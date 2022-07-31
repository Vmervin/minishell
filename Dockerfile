FROM alpine AS build-env
RUN apk add --no-cache build-base
RUN apk add readline-dev
RUN mkdir /minishell
COPY . ./minishell

# Compile the binaries
RUN cd minishell && make
FROM alpine
COPY --from=build-env /minishell/minishell /minishell/minishell
RUN apk add readline-dev
WORKDIR /minishell
CMD ["./minishell"]
