// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// $Id$
//
// Copyright (C) 1998-2006 by Randy Heit (ZDoom).
// Copyright (C) 2006-2013 by The Odamex Team.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	Client console variables
//
//-----------------------------------------------------------------------------

#include "c_cvars.h"

cvar_t cl_macro_cvars[] = {
	#ifdef _XBOX
	CVAR (chatmacro0, "Hi.", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)                       // A
	CVAR (chatmacro1, "I'm ready to kick butt!", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)   // B
	CVAR (chatmacro2, "Help!", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)                     // X
	CVAR (chatmacro3, "GG", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)                        // Y
	CVAR (chatmacro4, "No", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)                       // Black
	CVAR (chatmacro5, "Yes", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)                        // White
	CVAR (chatmacro6, "I'll take care of it.", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)     // Left Trigger
	CVAR (chatmacro7, "Come here!", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)                // Right Trigger
	CVAR (chatmacro8, "Thanks for the game. Bye.", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE) // Start
	CVAR (chatmacro9, "I am on Xbox and can only use chat macros.", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE) // Back
	#else
	// GhostlyDeath <November 2, 2008> -- someone had the order wrong (0-9!)
	CVAR (chatmacro1, "I'm ready to kick butt!", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (chatmacro2, "I'm OK.", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (chatmacro3, "I'm not looking too good!", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (chatmacro4, "Help!", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (chatmacro5, "You suck!", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (chatmacro6, "Next time, scumbag...", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (chatmacro7, "Come here!", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (chatmacro8, "I'll take care of it.", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (chatmacro9, "Yes", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (chatmacro0, "No", "",	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	#endif
	{0x0, 0x0, 0x0, CVARTYPE_NONE, 0x0}
};

cvar_t cl_misc_cvars[] = {
	CVAR (idmypos, "0", "Shows current player position on map",	CVARTYPE_BOOL, CVAR_NULL)

	CVAR (hud_crosshairdim, "0", "Crosshair transparency", CVARTYPE_BOOL, CVAR_ARCHIVE)
	CVAR (hud_crosshairscale, "0", "Crosshair scaling", CVARTYPE_WORD, CVAR_ARCHIVE)
	CVAR_FUNC_DECL (hud_crosshaircolor, "ff 00 00", "Crosshair color", CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (hud_crosshairhealth, "0", "Color of crosshair represents health level", CVARTYPE_BOOL, CVAR_ARCHIVE)
	CVAR (hud_fullhudtype, "1","Fullscreen HUD to display:\n// 0: ZDoom HUD\n// 1: New Odamex HUD", CVARTYPE_BYTE, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (hud_gamemsgtype, "2", "Game message type", CVARTYPE_BYTE, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (hud_revealsecrets, "0", "",	CVARTYPE_BOOL, CVAR_ARCHIVE)
	CVAR (hud_scale, "0", "HUD scaling", CVARTYPE_BOOL, CVAR_ARCHIVE)
	CVAR (hud_scalescoreboard, "0", "Scoreboard scaling", CVARTYPE_FLOAT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR_FUNC_DECL (hud_scaletext, "2", "Scaling multiplier for chat and midprint", CVARTYPE_BYTE, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR_FUNC_DECL (hud_targetcount, "2", "Number of players to reveal", CVARTYPE_BYTE, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (hud_targetnames, "1", "Show names of players you're aiming at", CVARTYPE_BOOL, CVAR_ARCHIVE)
	CVAR (hud_timer, "1", "Show the HUD timer", CVARTYPE_BOOL, CVAR_ARCHIVE)
	CVAR (hud_transparency, "0.5", "HUD transparency",	CVARTYPE_FLOAT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (hud_heldflag, "1", "Show the held flag border", CVARTYPE_BOOL, CVAR_ARCHIVE)
	{0x0, 0x0, 0x0, CVARTYPE_NONE, 0x0}
};

cvar_t cl_mp_cvars[] = {
	#ifdef _XBOX // Because Xbox players may be unable to communicate for now -- Hyper_Eye
	CVAR (cl_name,		"Xbox Player", "", CVARTYPE_STRING,	CVAR_USERINFO | CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	#else
	CVAR (cl_name,		"Player", "", CVARTYPE_STRING,	CVAR_USERINFO | CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	#endif
	CVAR (cl_color,		"40 cf 00", "", CVARTYPE_STRING,	CVAR_USERINFO | CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (cl_gender,	"male", "",	CVARTYPE_STRING,	CVAR_USERINFO | CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (cl_skin,		"base", "",	CVARTYPE_STRING,	CVAR_USERINFO | CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR_FUNC_DECL (cl_team,	"blue", "",	CVARTYPE_STRING,		CVAR_USERINFO | CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)

	// Intermission
	// ------------

	// Determines whether to draw the scores on intermission.
	CVAR (wi_newintermission, "0", "whether to draw the scores on intermission", CVARTYPE_STRING, CVAR_ARCHIVE)


	// Gameplay/Other
	// --------------

	// GhostlyDeath <August 1, 2008> -- Join/Part Sound
	// [ML] 8/20/2010 - Join sound, part sound
	CVAR (cl_connectalert, "1", "Plays a sound when a player joins", CVARTYPE_BOOL, CVAR_ARCHIVE)
	CVAR (cl_disconnectalert, "1", "Plays a sound when a player quits", CVARTYPE_BOOL, CVAR_ARCHIVE)

	CVAR (show_messages, "1", "", CVARTYPE_BOOL, CVAR_ARCHIVE)

	CVAR (mute_spectators, "0", "Mute spectators chat until next disconnect", CVARTYPE_BOOL, 0)
	CVAR (mute_enemies, "0", "Mute enemy players chat until next disconnect", CVARTYPE_BOOL, 0)

	// Rate of client updates
	CVAR_FUNC_DECL (rate, "200", "Rate of client updates in multiplayer mode", CVARTYPE_INT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	// Maximum number of clients who can connect to the server
	CVAR (sv_maxclients,       "0", "maximum clients who can connect to server", CVARTYPE_BYTE, CVAR_SERVERINFO | CVAR_LATCH | CVAR_NOENABLEDISABLE)
	// Maximum amount of players who can join the game, others are spectators
	CVAR (sv_maxplayers,		"0", "maximum players who can join the game, others are spectators", CVARTYPE_BYTE, CVAR_SERVERINFO | CVAR_LATCH | CVAR_NOENABLEDISABLE)
	// Maximum number of players that can be on a team
	CVAR (sv_maxplayersperteam, "0", "Maximum number of players that can be on a team", CVARTYPE_BYTE, CVAR_SERVERINFO | CVAR_LATCH | CVAR_NOENABLEDISABLE)

	CVAR_FUNC_DECL (cl_autoaim,	"5000", "", CVARTYPE_INT,		CVAR_USERINFO | CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)

	// Netcode Settings
	// --------------

	CVAR (cl_unlag,				"1", "client opt-in/out for server unlagging", CVARTYPE_BOOL,		CVAR_USERINFO | CVAR_ARCHIVE)
	CVAR_FUNC_DECL (cl_updaterate, "1",	"Update players every N tics", CVARTYPE_BYTE,	CVAR_USERINFO | CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR_FUNC_DECL (cl_interp,	"1", "Interpolate enemy player positions", CVARTYPE_INT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR_FUNC_DECL (cl_prednudge,	"0.70", "Smooth out the collisions", CVARTYPE_FLOAT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (cl_predictlocalplayer, "1", "Predict local player position", CVARTYPE_BOOL, CVAR_ARCHIVE)
	CVAR (cl_netgraph,				"0", "Show a graph of network related statistics", CVARTYPE_BOOL, CVAR_NULL)
	CVAR (cl_predictweapons, "1", "Draw weapon effects immediately", CVARTYPE_BOOL, CVAR_USERINFO | CVAR_ARCHIVE)


	// Sound and music
	// ---------------

	CVAR_FUNC_DECL (snd_sfxvolume, "0.5", "Sound volume",	CVARTYPE_FLOAT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)      // Sound volume
	CVAR_FUNC_DECL (snd_musicvolume, "0.5", "Music volume",	CVARTYPE_FLOAT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)    // Music volume
	CVAR_FUNC_DECL (snd_announcervolume, "1.0", "Announcer volume",	CVARTYPE_FLOAT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)    // CTF announcer volume
	CVAR (snd_voxtype, "2", "Voice announcer type", CVARTYPE_BYTE, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (snd_gamesfx, "1", "Game SFX", CVARTYPE_BOOL, CVAR_ARCHIVE)
	{0x0, 0x0, 0x0, CVARTYPE_NONE, 0x0}
};
