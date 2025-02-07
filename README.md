## Readme

This repo contains config.h files for various Suckless-related software. They are set up so the main builds on each machine contain symbiotic links to the corresponding repos one level (../config-h) up.
This enables patching of each build to be general while the configs to differ based on which machine compiles and installs the packages.
Each package repo must also contain a .gitignore file that ignores the config.h when comitting and pushing. This removes the issue of creating divergent changes on each install.
