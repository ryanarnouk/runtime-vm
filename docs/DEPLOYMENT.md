# Deployment and Release Plans

My plan is to create a GitHub action `release.yml` that on push, checks for a change in the `common_properties.h` file for either the `MAJOR_VERSION` or the `MINOR_VERSION` If a release has already been tagged with this version, a new release is not needed. If a branch hasn't been tagged with this version yet, the action should go on to complete the build process and create a release with the downloadable binaries for users to download. 

A user can subsequently run the `env_setup.sh` Shell script to set `rvm` as a command on their machine. 

The GitHub action should correspondingly run on every push and make that check if a versioned release should be out.
