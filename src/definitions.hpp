#pragma once
#include <string>

#define PLUGIN_API_VERSION 26

/*-------------------------- CHANGE THESE --------------------------*/

// this needs to be unique for each plugin
#define CONFIG_FILE "qtexample.ini"

#define PLUGIN_NAME "Qt Example Plugin"
#define PLUGIN_AUTHOR "JUL14N"
#define PLUGIN_DESCRIPTION "A simple Qt plugin to demonstrate a full toolchain."

/*-------------------------- INTERNAL DEFINITIONS --------------------------*/
// don't change this, it is replaced by the build script
#define PLUGIN_VERSION "<version>"

#define PATH_BUFSIZE 512
#define COMMAND_BUFSIZE 128
#define INFODATA_BUFSIZE 128
#define SERVERINFO_BUFSIZE 256
#define CHANNELINFO_BUFSIZE 512
#define RETURNCODE_BUFSIZE 128