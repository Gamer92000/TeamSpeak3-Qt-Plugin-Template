#if defined(WIN32) || defined(__WIN32__) || defined(_WIN32)
#pragma warning(disable : 4100) /* Disable Unreferenced parameter warning */
#include <Windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "teamspeak/public_errors.h"
#include "teamspeak/public_errors_rare.h"
#include "teamspeak/public_definitions.h"
#include "teamspeak/public_rare_definitions.h"
#include "teamspeak/clientlib_publicdefinitions.h"
#include "ts3_functions.h"

#include "plugin.h"
#include "definitions.hpp"
#include "helper.h"
#include "config.h"

static struct TS3Functions ts3Functions;
static char *pluginID = NULL;
config *configObject;

/*-------------------------- Configure Here --------------------------*/
/*
 * The following functions should be configured to your needs.
 */
int ts3plugin_init()
{
	char configPath[PATH_BUFSIZE];
	ts3Functions.getConfigPath(configPath, PATH_BUFSIZE);
	configObject = new config(QString::fromUtf8(configPath) + CONFIG_FILE);

	return 0;
}

void ts3plugin_shutdown()
{
	if (configObject)
	{
		configObject->close();
		delete configObject;
		configObject = NULL;
	}

	if (pluginID)
	{
		free(pluginID);
		pluginID = NULL;
	}
}

enum
{
	MENU_ID_GLOBAL_SETTINGS = 1
};

void ts3plugin_initMenus(struct PluginMenuItem ***menuItems, char **menuIcon)
{
	BEGIN_CREATE_MENUS(1);
	CREATE_MENU_ITEM(PLUGIN_MENU_TYPE_GLOBAL, MENU_ID_GLOBAL_SETTINGS, "Settings", "");
	END_CREATE_MENUS;
	menuIcon = NULL;
}

void ts3plugin_onMenuItemEvent(uint64 serverConnectionHandlerID, enum PluginMenuType type, int menuItemID, uint64 selectedItemID)
{
	switch (type)
	{
	case PLUGIN_MENU_TYPE_GLOBAL:
		switch (menuItemID)
		{
		case MENU_ID_GLOBAL_SETTINGS:
			if (configObject->isVisible())
			{
				configObject->raise();
				configObject->activateWindow();
			}
			else
				configObject->show();
			break;
		}
		break;
	}
}

/*-------------------------- DON'T TOUCH --------------------------*/
/*
 * Those functions are setup nicely and
 * should be configured using the definitions.hpp file.
 */
const char *ts3plugin_name()
{
	return PLUGIN_NAME;
}

const char *ts3plugin_version()
{
	return PLUGIN_VERSION;
}

int ts3plugin_apiVersion()
{
	return PLUGIN_API_VERSION;
}

const char *ts3plugin_author()
{
	return PLUGIN_AUTHOR;
}

const char *ts3plugin_description()
{
	return PLUGIN_DESCRIPTION;
}

void ts3plugin_setFunctionPointers(const struct TS3Functions funcs)
{
	ts3Functions = funcs;
}

int ts3plugin_offersConfigure()
{
	return PLUGIN_OFFERS_CONFIGURE_QT_THREAD;
}

void ts3plugin_configure(void *handle, void *qParentWidget)
{
	if (configObject->isVisible())
	{
		configObject->raise();
		configObject->activateWindow();
	}
	else
	{
		configObject->show();
	}
}

void ts3plugin_registerPluginID(const char *id)
{
	const size_t sz = strlen(id) + 1;
	pluginID = (char *)malloc(sz * sizeof(char));
	_strcpy(pluginID, sz, id);
}

void ts3plugin_freeMemory(void *data)
{
	free(data);
}


/*-------------------------- OTHER STUFF --------------------------*/
/*
 * Those functions are not used in this demo plugin.
 */

/* Plugin command keyword. Return NULL or "" if not used. */
// const char *ts3plugin_commandKeyword()
// {
// 	return NULL;
// }

/* Plugin processes console command. Return 0 if plugin handled the command, 1 if not handled. */
// int ts3plugin_processCommand(uint64 serverConnectionHandlerID, const char *command)
// {
// 	return 0; /* Plugin handled command */
// }

/* Client changed current server connection handler */
// void ts3plugin_currentServerConnectionChanged(uint64 serverConnectionHandlerID)
// {
// }

/*
 * Implement the following three functions when the plugin should display a line in the server/channel/client info.
 * If any of ts3plugin_infoTitle, ts3plugin_infoData or ts3plugin_freeMemory is missing, the info text will not be displayed.
 */

/* Static title shown in the left column in the info frame */
// const char *ts3plugin_infoTitle()
// {
// 	return PLUGIN_NAME;
// }

/*
 * Dynamic content shown in the right column in the info frame. Memory for the data string needs to be allocated in this
 * function. The client will call ts3plugin_freeMemory once done with the string to release the allocated memory again.
 * Check the parameter "type" if you want to implement this feature only for specific item types. Set the parameter
 * "data" to NULL to have the client ignore the info data.
 */
// void ts3plugin_infoData(uint64 serverConnectionHandlerID, uint64 id, enum PluginItemType type, char **data)
// {
// 	*data = (char *)malloc(INFODATA_BUFSIZE * sizeof(char));	/* Must be allocated in the plugin! */
// 	snprintf(*data, INFODATA_BUFSIZE, PLUGIN_DESCRIPTION);		/* bbCode is supported. HTML is not supported */
// }

/*
 * Plugin requests to be always automatically loaded by the TeamSpeak 3 client unless
 * the user manually disabled it in the plugin dialog.
 * This function is optional. If missing, no autoload is assumed.
 */
// int ts3plugin_requestAutoload()
// {
// 	return 0; /* 1 = request autoloaded, 0 = do not request autoload */
// }

/*
 * Initialize plugin hotkeys. If your plugin does not use this feature, this function can be omitted.
 * Hotkeys require ts3plugin_registerPluginID and ts3plugin_freeMemory to be implemented.
 * This function is automatically called by the client after ts3plugin_init.
 */
// void ts3plugin_initHotkeys(struct PluginHotkey ***hotkeys)
// {
// 	/* Register hotkeys giving a keyword and a description.
// 	 * The keyword will be later passed to ts3plugin_onHotkeyEvent to identify which hotkey was triggered.
// 	 * The description is shown in the clients hotkey dialog. */
// 	BEGIN_CREATE_HOTKEYS(3); /* Create 3 hotkeys. Size must be correct for allocating memory. */
// 	CREATE_HOTKEY("keyword_1", "Test hotkey 1");
// 	CREATE_HOTKEY("keyword_2", "Test hotkey 2");
// 	CREATE_HOTKEY("keyword_3", "Test hotkey 3");
// 	END_CREATE_HOTKEYS;

// 	/* The client will call ts3plugin_freeMemory to release all allocated memory */
// }

/************************** TeamSpeak callbacks ***************************/
/*
 * Following functions are optional, feel free to remove unused callbacks.
 * See the clientlib documentation for details on each function.
 */

/* Clientlib */

// void ts3plugin_onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber)
// {
// }

// void ts3plugin_onNewChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID)
// {
// }

// void ts3plugin_onNewChannelCreatedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID, anyID invokerID, const char *invokerName, const char *invokerUniqueIdentifier)
// {
// }

// void ts3plugin_onDelChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char *invokerName, const char *invokerUniqueIdentifier)
// {
// }

// void ts3plugin_onChannelMoveEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 newChannelParentID, anyID invokerID, const char *invokerName, const char *invokerUniqueIdentifier)
// {
// }

// void ts3plugin_onUpdateChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID)
// {
// }

// void ts3plugin_onUpdateChannelEditedEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char *invokerName, const char *invokerUniqueIdentifier)
// {
// }

// void ts3plugin_onUpdateClientEvent(uint64 serverConnectionHandlerID, anyID clientID, anyID invokerID, const char *invokerName, const char *invokerUniqueIdentifier)
// {
// }

// void ts3plugin_onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char *moveMessage)
// {
// }

// void ts3plugin_onClientMoveSubscriptionEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility)
// {
// }

// void ts3plugin_onClientMoveTimeoutEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char *timeoutMessage)
// {
// }

// void ts3plugin_onClientMoveMovedEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID moverID, const char *moverName, const char *moverUniqueIdentifier, const char *moveMessage)
// {
// }

// void ts3plugin_onClientKickFromChannelEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char *kickerName, const char *kickerUniqueIdentifier, const char *kickMessage)
// {
// }

// void ts3plugin_onClientKickFromServerEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char *kickerName, const char *kickerUniqueIdentifier, const char *kickMessage)
// {
// }

// void ts3plugin_onClientIDsEvent(uint64 serverConnectionHandlerID, const char *uniqueClientIdentifier, anyID clientID, const char *clientName)
// {
// }

// void ts3plugin_onClientIDsFinishedEvent(uint64 serverConnectionHandlerID)
// {
// }

// void ts3plugin_onServerEditedEvent(uint64 serverConnectionHandlerID, anyID editerID, const char *editerName, const char *editerUniqueIdentifier)
// {
// }

// void ts3plugin_onServerUpdatedEvent(uint64 serverConnectionHandlerID)
// {
// }

// int ts3plugin_onServerErrorEvent(uint64 serverConnectionHandlerID, const char *errorMessage, unsigned int error, const char *returnCode, const char *extraMessage)
// {
// 	/* A plugin could now check the returnCode with previously (when calling a function) remembered returnCodes and react accordingly */
// 	/* In case of using a a plugin return code, the plugin can return:
// 	 * 0: Client will continue handling this error (print to chat tab)
// 	 * 1: Client will ignore this error, the plugin announces it has handled it */
// 	return 0; /* If no plugin return code was used, the return value of this function is ignored */
// }

// void ts3plugin_onServerStopEvent(uint64 serverConnectionHandlerID, const char *shutdownMessage)
// {
// }

// int ts3plugin_onTextMessageEvent(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char *fromName, const char *fromUniqueIdentifier, const char *message, int ffIgnored)
// {
// 	return 0; /* 0 = handle normally, 1 = client will ignore the text message */
// }

// void ts3plugin_onTalkStatusChangeEvent(uint64 serverConnectionHandlerID, int status, int isReceivedWhisper, anyID clientID)
// {
// }

// void ts3plugin_onConnectionInfoEvent(uint64 serverConnectionHandlerID, anyID clientID)
// {
// }

// void ts3plugin_onServerConnectionInfoEvent(uint64 serverConnectionHandlerID)
// {
// }

// void ts3plugin_onChannelSubscribeEvent(uint64 serverConnectionHandlerID, uint64 channelID)
// {
// }

// void ts3plugin_onChannelSubscribeFinishedEvent(uint64 serverConnectionHandlerID)
// {
// }

// void ts3plugin_onChannelUnsubscribeEvent(uint64 serverConnectionHandlerID, uint64 channelID)
// {
// }

// void ts3plugin_onChannelUnsubscribeFinishedEvent(uint64 serverConnectionHandlerID)
// {
// }

// void ts3plugin_onChannelDescriptionUpdateEvent(uint64 serverConnectionHandlerID, uint64 channelID)
// {
// }

// void ts3plugin_onChannelPasswordChangedEvent(uint64 serverConnectionHandlerID, uint64 channelID)
// {
// }

// void ts3plugin_onPlaybackShutdownCompleteEvent(uint64 serverConnectionHandlerID)
// {
// }

// void ts3plugin_onSoundDeviceListChangedEvent(const char *modeID, int playOrCap)
// {
// }

// void ts3plugin_onEditPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, anyID clientID, short *samples, int sampleCount, int channels)
// {
// }

// void ts3plugin_onEditPostProcessVoiceDataEvent(uint64 serverConnectionHandlerID, anyID clientID, short *samples, int sampleCount, int channels, const unsigned int *channelSpeakerArray, unsigned int *channelFillMask)
// {
// }

// void ts3plugin_onEditMixedPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, short *samples, int sampleCount, int channels, const unsigned int *channelSpeakerArray, unsigned int *channelFillMask)
// {
// }

// void ts3plugin_onEditCapturedVoiceDataEvent(uint64 serverConnectionHandlerID, short *samples, int sampleCount, int channels, int *edited)
// {
// }

// void ts3plugin_onCustom3dRolloffCalculationClientEvent(uint64 serverConnectionHandlerID, anyID clientID, float distance, float *volume)
// {
// }

// void ts3plugin_onCustom3dRolloffCalculationWaveEvent(uint64 serverConnectionHandlerID, uint64 waveHandle, float distance, float *volume)
// {
// }

// void ts3plugin_onUserLoggingMessageEvent(const char *logMessage, int logLevel, const char *logChannel, uint64 logID, const char *logTime, const char *completeLogString)
// {
// }

// /* Clientlib rare */

// void ts3plugin_onClientBanFromServerEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char *kickerName, const char *kickerUniqueIdentifier, uint64 time, const char *kickMessage)
// {
// }

// int ts3plugin_onClientPokeEvent(uint64 serverConnectionHandlerID, anyID fromClientID, const char *pokerName, const char *pokerUniqueIdentity, const char *message, int ffIgnored)
// {
// 	return 0; /* 0 = handle normally, 1 = client will ignore the poke */
// }

// void ts3plugin_onClientSelfVariableUpdateEvent(uint64 serverConnectionHandlerID, int flag, const char *oldValue, const char *newValue)
// {
// }

// void ts3plugin_onFileListEvent(uint64 serverConnectionHandlerID, uint64 channelID, const char *path, const char *name, uint64 size, uint64 datetime, int type, uint64 incompletesize, const char *returnCode)
// {
// }

// void ts3plugin_onFileListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelID, const char *path)
// {
// }

// void ts3plugin_onFileInfoEvent(uint64 serverConnectionHandlerID, uint64 channelID, const char *name, uint64 size, uint64 datetime)
// {
// }

// void ts3plugin_onServerGroupListEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID, const char *name, int type, int iconID, int saveDB)
// {
// }

// void ts3plugin_onServerGroupListFinishedEvent(uint64 serverConnectionHandlerID)
// {
// }

// void ts3plugin_onServerGroupByClientIDEvent(uint64 serverConnectionHandlerID, const char *name, uint64 serverGroupList, uint64 clientDatabaseID)
// {
// }

// void ts3plugin_onServerGroupPermListEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip)
// {
// }

// void ts3plugin_onServerGroupPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID)
// {
// }

// void ts3plugin_onServerGroupClientListEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID, uint64 clientDatabaseID, const char *clientNameIdentifier, const char *clientUniqueID)
// {
// }

// void ts3plugin_onChannelGroupListEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID, const char *name, int type, int iconID, int saveDB)
// {
// }

// void ts3plugin_onChannelGroupListFinishedEvent(uint64 serverConnectionHandlerID)
// {
// }

// void ts3plugin_onChannelGroupPermListEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip)
// {
// }

// void ts3plugin_onChannelGroupPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID)
// {
// }

// void ts3plugin_onChannelPermListEvent(uint64 serverConnectionHandlerID, uint64 channelID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip)
// {
// }

// void ts3plugin_onChannelPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelID)
// {
// }

// void ts3plugin_onClientPermListEvent(uint64 serverConnectionHandlerID, uint64 clientDatabaseID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip)
// {
// }

// void ts3plugin_onClientPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 clientDatabaseID)
// {
// }

// void ts3plugin_onChannelClientPermListEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 clientDatabaseID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip)
// {
// }

// void ts3plugin_onChannelClientPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 clientDatabaseID)
// {
// }

// void ts3plugin_onClientChannelGroupChangedEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID, uint64 channelID, anyID clientID, anyID invokerClientID, const char *invokerName, const char *invokerUniqueIdentity)
// {
// }

// int ts3plugin_onServerPermissionErrorEvent(uint64 serverConnectionHandlerID, const char *errorMessage, unsigned int error, const char *returnCode, unsigned int failedPermissionID)
// {
// 	return 0; /* See onServerErrorEvent for return code description */
// }

// void ts3plugin_onPermissionListGroupEndIDEvent(uint64 serverConnectionHandlerID, unsigned int groupEndID)
// {
// }

// void ts3plugin_onPermissionListEvent(uint64 serverConnectionHandlerID, unsigned int permissionID, const char *permissionName, const char *permissionDescription)
// {
// }

// void ts3plugin_onPermissionListFinishedEvent(uint64 serverConnectionHandlerID)
// {
// }

// void ts3plugin_onPermissionOverviewEvent(uint64 serverConnectionHandlerID, uint64 clientDatabaseID, uint64 channelID, int overviewType, uint64 overviewID1, uint64 overviewID2, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip)
// {
// }

// void ts3plugin_onPermissionOverviewFinishedEvent(uint64 serverConnectionHandlerID)
// {
// }

// void ts3plugin_onServerGroupClientAddedEvent(uint64 serverConnectionHandlerID, anyID clientID, const char *clientName, const char *clientUniqueIdentity, uint64 serverGroupID, anyID invokerClientID, const char *invokerName, const char *invokerUniqueIdentity)
// {
// }

// void ts3plugin_onServerGroupClientDeletedEvent(uint64 serverConnectionHandlerID, anyID clientID, const char *clientName, const char *clientUniqueIdentity, uint64 serverGroupID, anyID invokerClientID, const char *invokerName, const char *invokerUniqueIdentity)
// {
// }

// void ts3plugin_onClientNeededPermissionsEvent(uint64 serverConnectionHandlerID, unsigned int permissionID, int permissionValue)
// {
// }

// void ts3plugin_onClientNeededPermissionsFinishedEvent(uint64 serverConnectionHandlerID)
// {
// }

// void ts3plugin_onFileTransferStatusEvent(anyID transferID, unsigned int status, const char *statusMessage, uint64 remotefileSize, uint64 serverConnectionHandlerID)
// {
// }

// void ts3plugin_onClientChatClosedEvent(uint64 serverConnectionHandlerID, anyID clientID, const char *clientUniqueIdentity)
// {
// }

// void ts3plugin_onClientChatComposingEvent(uint64 serverConnectionHandlerID, anyID clientID, const char *clientUniqueIdentity)
// {
// }

// void ts3plugin_onServerLogEvent(uint64 serverConnectionHandlerID, const char *logMsg)
// {
// }

// void ts3plugin_onServerLogFinishedEvent(uint64 serverConnectionHandlerID, uint64 lastPos, uint64 fileSize)
// {
// }

// void ts3plugin_onMessageListEvent(uint64 serverConnectionHandlerID, uint64 messageID, const char *fromClientUniqueIdentity, const char *subject, uint64 timestamp, int flagRead)
// {
// }

// void ts3plugin_onMessageGetEvent(uint64 serverConnectionHandlerID, uint64 messageID, const char *fromClientUniqueIdentity, const char *subject, const char *message, uint64 timestamp)
// {
// }

// void ts3plugin_onClientDBIDfromUIDEvent(uint64 serverConnectionHandlerID, const char *uniqueClientIdentifier, uint64 clientDatabaseID)
// {
// }

// void ts3plugin_onClientNamefromUIDEvent(uint64 serverConnectionHandlerID, const char *uniqueClientIdentifier, uint64 clientDatabaseID, const char *clientNickName)
// {
// }

// void ts3plugin_onClientNamefromDBIDEvent(uint64 serverConnectionHandlerID, const char *uniqueClientIdentifier, uint64 clientDatabaseID, const char *clientNickName)
// {
// }

// void ts3plugin_onComplainListEvent(uint64 serverConnectionHandlerID, uint64 targetClientDatabaseID, const char *targetClientNickName, uint64 fromClientDatabaseID, const char *fromClientNickName, const char *complainReason, uint64 timestamp)
// {
// }

// void ts3plugin_onBanListEvent(uint64 serverConnectionHandlerID, uint64 banid, const char *ip, const char *name, const char *uid, const char *mytsid, uint64 creationTime, uint64 durationTime, const char *invokerName,
// 															uint64 invokercldbid, const char *invokeruid, const char *reason, int numberOfEnforcements, const char *lastNickName)
// {
// }

// void ts3plugin_onClientServerQueryLoginPasswordEvent(uint64 serverConnectionHandlerID, const char *loginPassword)
// {
// }

// void ts3plugin_onPluginCommandEvent(uint64 serverConnectionHandlerID, const char *pluginName, const char *pluginCommand, anyID invokerClientID, const char *invokerName, const char *invokerUniqueIdentity)
// {
// }

// void ts3plugin_onIncomingClientQueryEvent(uint64 serverConnectionHandlerID, const char *commandText)
// {
// }

// void ts3plugin_onServerTemporaryPasswordListEvent(uint64 serverConnectionHandlerID, const char *clientNickname, const char *uniqueClientIdentifier, const char *description, const char *password, uint64 timestampStart, uint64 timestampEnd, uint64 targetChannelID, const char *targetChannelPW)
// {
// }

// /* Client UI callbacks */

// /*
//  * Called from client when an avatar image has been downloaded to or deleted from cache.
//  * This callback can be called spontaneously or in response to ts3Functions.getAvatar()
//  */
// void ts3plugin_onAvatarUpdated(uint64 serverConnectionHandlerID, anyID clientID, const char *avatarPath)
// {
// }

// /* This function is called if a plugin hotkey was pressed. Omit if hotkeys are unused. */
// void ts3plugin_onHotkeyEvent(const char *keyword)
// {
// 	/* Identify the hotkey by keyword ("keyword_1", "keyword_2" or "keyword_3" in this example) and handle here... */
// }

// /* Called when recording a hotkey has finished after calling ts3Functions.requestHotkeyInputDialog */
// void ts3plugin_onHotkeyRecordedEvent(const char *keyword, const char *key)
// {
// }

// // This function receives your key Identifier you send to notifyKeyEvent and should return
// // the friendly device name of the device this hotkey originates from. Used for display in UI.
// const char *ts3plugin_keyDeviceName(const char *keyIdentifier)
// {
// 	return NULL;
// }

// // This function translates the given key identifier to a friendly key name for display in the UI
// const char *ts3plugin_displayKeyText(const char *keyIdentifier)
// {
// 	return NULL;
// }

// // This is used internally as a prefix for hotkeys so we can store them without collisions.
// // Should be unique across plugins.
// const char *ts3plugin_keyPrefix()
// {
// 	return NULL;
// }

// /* Called when client custom nickname changed */
// void ts3plugin_onClientDisplayNameChanged(uint64 serverConnectionHandlerID, anyID clientID, const char *displayName, const char *uniqueClientIdentifier)
// {
// }
