#include <iostream>
#include "definitions.hpp"

#ifdef _WIN32
#define _strcpy(dest, destSize, src) strcpy_s(dest, destSize, src)
#define snprintf sprintf_s
#else
#define _strcpy(dest, destSize, src)  \
	{                                   \
		strncpy(dest, src, destSize - 1); \
		(dest)[destSize - 1] = '\0';      \
	}
#endif

/* Helper function to create a menu item */
static struct PluginMenuItem *createMenuItem(enum PluginMenuType type, int id, const char *text, const char *icon)
{
	struct PluginMenuItem *menuItem = (struct PluginMenuItem *)malloc(sizeof(struct PluginMenuItem));
	menuItem->type = type;
	menuItem->id = id;
	_strcpy(menuItem->text, PLUGIN_MENU_BUFSZ, text);
	_strcpy(menuItem->icon, PLUGIN_MENU_BUFSZ, icon);
	return menuItem;
}

/* Some makros to make the code to create menu items a bit more readable */
#define BEGIN_CREATE_MENUS(x) \
	const size_t sz = x + 1;    \
	size_t n = 0;               \
	*menuItems = (struct PluginMenuItem **)malloc(sizeof(struct PluginMenuItem *) * sz);
#define CREATE_MENU_ITEM(a, b, c, d) (*menuItems)[n++] = createMenuItem(a, b, c, d);
#define END_CREATE_MENUS    \
	(*menuItems)[n++] = NULL; \
	assert(n == sz);


/* Helper function to create a hotkey */
// static struct PluginHotkey *createHotkey(const char *keyword, const char *description)
// {
// 	struct PluginHotkey *hotkey = (struct PluginHotkey *)malloc(sizeof(struct PluginHotkey));
// 	_strcpy(hotkey->keyword, PLUGIN_HOTKEY_BUFSZ, keyword);
// 	_strcpy(hotkey->description, PLUGIN_HOTKEY_BUFSZ, description);
// 	return hotkey;
// }

// /* Some makros to make the code to create hotkeys a bit more readable */
// #define BEGIN_CREATE_HOTKEYS(x) \
// 	const size_t sz = x + 1;      \
// 	size_t n = 0;                 \
// 	*hotkeys = (struct PluginHotkey **)malloc(sizeof(struct PluginHotkey *) * sz);
// #define CREATE_HOTKEY(a, b) (*hotkeys)[n++] = createHotkey(a, b);
// #define END_CREATE_HOTKEYS \
// 	(*hotkeys)[n++] = NULL;  \
// 	assert(n == sz);