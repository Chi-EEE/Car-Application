# Setup compiling on Windows with Docker

DISCLAIMER: This method may use over 1000% of the Container CPU and it is recommended to use the Raspberry Pi for development instead.

To start compiling the raspberry pi application on Windows or possibility on other operating systems, you would need to install [Docker](https://docs.docker.com/get-docker/).

We are going to install a Docker image from this repository: [https://hub.docker.com/r/satmandu/raspios/tags](https://hub.docker.com/r/satmandu/raspios/tags)

Run these commands after installing Docker:
```
docker pull satmandu/raspios:lite && docker run -it satmandu/raspios:lite /bin/bash
```

Afterwards, open the Docker container in VSCode and run `sudo apt-get install git` to install Git.

Go to the `/home/pi/` directory, create a `Github` directory via `mkdir Github`, and store all the git cloned directories in it.

Now you can follow `SETUP.md`.