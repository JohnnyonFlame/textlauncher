#include "c_cvars.h"

cvar_t sv_gameplay_cvars[] =
{
		CVAR (sv_gametype, "0", "Sets the game mode, values are:\n" \
		                        "// 0 = Cooperative\n" \
		                        "// 1 = Deathmatch\n" \
		                        "// 2 = Team Deathmatch\n" \
		                        "// 3 = Capture The Flag",
		      CVARTYPE_BYTE, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH | CVAR_NOENABLEDISABLE)

		// (Coop/Teamplay/CTF): Players can injure others on the same team
		CVAR (sv_friendlyfire, "1", "When set, players can injure others on the same team, it is ignored in deathmatch",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
		// (Teamplay/CTF): Game ends when team score is reached
		CVAR (sv_scorelimit, "5", "Game ends when team score is reached in Teamplay/CTF",
		      CVARTYPE_BYTE, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)
		// (Teamplay/CTF) When disabled, treat team spawns like normal deathmatch spawns.
		CVAR (sv_teamspawns, "1", "When disabled, treat team spawns like normal deathmatch spawns in Teamplay/CTF",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_LATCH | CVAR_SERVERINFO)
		// Cheat code usage is allowed
		CVAR (sv_allowcheats, "0", "Allow usage of cheats in all game modes",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
		// Exit switch/teleports are usable
		CVAR (sv_allowexit, "1", "Allow use of Exit switch/teleports in all game modes",
		     CVARTYPE_BOOL,  CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
		// Players can jump
		CVAR (sv_allowjump, "0", "Allows players to jump when set in all game modes",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
		// Give double ammo regardless of difficulty
		CVAR (sv_doubleammo, "0", "Give double ammo regardless of difficulty",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
		// Multiplier for player weapon damage
		CVAR (sv_weapondamage, "1.0", "Amount to multiply player weapon damage by",
		      CVARTYPE_FLOAT, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH | CVAR_NOENABLEDISABLE)
		// Makes water movement more realistic
		CVAR_FUNC_DECL (sv_forcewater, "0", "Makes water more realistic (boom maps at the moment)",
		                CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)
		// Look up/down is allowed
		CVAR (sv_freelook,      "0", "Allow Looking up and down",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
		// Names of players appear in the FOV
		CVAR (sv_allowtargetnames, "0", "When set, names of players appear in the FOV",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
		// Game ends on frag limit being reached
		CVAR (sv_fraglimit,     "0", "Sets the amount of frags a player can accumulate before the game ends",
		      CVARTYPE_BYTE, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)
		// Monsters are at nightmare speed
		CVAR (sv_fastmonsters,     "0", "Monsters are at nightmare speed",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
		// Multiplier for monster damage
		CVAR (sv_monsterdamage, "1.0", "Amount to multiply monster weapon damage by",
		      CVARTYPE_FLOAT, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH | CVAR_NOENABLEDISABLE)
		// OLD: Allow exit switch at maxfrags, must click to exit
		// NEW: When enabled, exit switch will kill the player who flips it
		// [ML] NOTE: Behavior was changed October 2012, see bug
		CVAR (sv_fragexitswitch,   "0", "When enabled, exit switch will kill the player who flips it",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
		// Players will have infinite ammunition
		CVAR (sv_infiniteammo,     "0", "Infinite ammo for all players",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
		// Items will respawn after time
		CVAR (sv_itemsrespawn,     "0", "Items will respawn after a fixed period, see sv_itemrespawntime",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH)
		// If itemrespawn is on, items will respawn after this time. (in seconds)
		CVAR (sv_itemrespawntime,  "30", "If sv_itemsrespawn is set, items will respawn after this time (in seconds)",
		      CVARTYPE_BYTE, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)
		// Monsters will respawn after time
		CVAR (sv_monstersrespawn,  "0", "Monsters will respawn after a period of time",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
		// Monsters are not present
		CVAR (sv_nomonsters,    "0", "No monsters will be present",
		     CVARTYPE_BOOL,  CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH)
		// Monsters have a specific percentage of their normal health
		CVAR (sv_monstershealth, "1.0", "Amount to multiply monster health by",
		      CVARTYPE_FLOAT, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH | CVAR_NOENABLEDISABLE)
		// Skill level
		CVAR (sv_skill,             "3", "Sets the skill level, values are:\n" \
		                                 "// 0 - No things mode\n" \
		                                 "// 1 - I'm Too Young To Die\n" \
		                                 "// 2 - Hey, Not Too Rough\n" \
		                                 "// 3 - Hurt Me Plenty\n" \
		                                 "// 4 - Ultra-Violence\n" \
		                                 "// 5 - Nightmare",
		      CVARTYPE_BYTE, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH | CVAR_NOENABLEDISABLE)
		// Game ends on time limit being reached
		CVAR_FUNC_DECL (sv_timelimit,    "0", "Sets the time limit for the game to end, must be greater than 1",
		      CVARTYPE_WORD, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)

		// Intermission ends on intermission time limit being reached
		CVAR_FUNC_DECL (sv_intermissionlimit, "10", "Sets the time limit for the intermission to end, 0 disables (defaults to 10 seconds)",
		      CVARTYPE_WORD, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)

		// Weapons stay
		CVAR (sv_weaponstay,    "1", "Weapons stay after pickup",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH)
		// Keep keys on death
		CVAR(sv_keepkeys, "0", "Keep keys on death",
		     CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH)

		// [SL] 2011-05-11 - Allow reconciliation for players on lagged connections
		CVAR (sv_unlag,            "1", "Allow reconciliation for players on lagged connections",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH)
		CVAR (sv_maxunlagtime,	"1.0", "Cap the maxiumum time allowed for player reconciliation",
		      CVARTYPE_FLOAT, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)
		// [ML] allow weapon & view bob changing
		CVAR (sv_allowmovebob, "0", "Allow weapon & view bob changing",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)

		// [ML] Allow clients to adjust amount of red pain screen intensity
		CVAR (sv_allowredscreen, "0","Allow clients to adjust amount of red pain screen intensity",
		     CVARTYPE_BOOL, CVAR_SERVERINFO | CVAR_SERVERARCHIVE)

		// [SL] Allow PWO
		CVAR (sv_allowpwo, "0", "Allow clients to set their preferences for automatic weapon swithching",
		   CVARTYPE_BOOL, CVAR_SERVERINFO | CVAR_SERVERARCHIVE)

		// [AM] Allow true widescreen usage
		CVAR_FUNC_DECL (sv_allowwidescreen, "1", "Allow clients to use true widescreen",
		      CVARTYPE_BOOL, CVAR_SERVERINFO | CVAR_SERVERARCHIVE | CVAR_LATCH)

		// [AM] Allow players to see the spawns on the map
		CVAR (sv_allowshowspawns, "1", "Allow clients to see spawn points as particle fountains",
		      CVARTYPE_BOOL, CVAR_SERVERINFO | CVAR_SERVERARCHIVE | CVAR_LATCH)

		// Compatibility options for vanilla
		// ---------------------------------

		// Enable/disable infinitely tall actors
		CVAR (co_realactorheight, "0", "Enable/Disable infinitely tall actors",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH)

		// [Spleen] When enabled, monsters can get pushed or thrusted off of ledges, like in boom
		CVAR (co_allowdropoff, "0", "When enabled, monsters can get pushed or thrusted off of ledges, like in boom",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH)

		// [ML] When enabled, activate correct impact of projectiles and bullets on surfaces (spawning puffs,explosions)
		CVAR (co_fixweaponimpacts, "0", "When enabled, activate correct impact of projectiles and bullets on surfaces (spawning puffs,explosions)",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO)

		// Allow line specials with sector tags of 0 to be used for moving floors/ceilings.
		CVAR (co_fixzerotags, "0", "Allow line specials with sector tags of 0 to be used for moving floors/ceilings.",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO)

		// [ML] When enabled, additional checks are made on two-sided lines, allows additional
		// silent bfg tricks, and the player will "oof" on two-sided lines
		CVAR (co_boomlinecheck, "0", "additional checks are made on two-sided lines, allows additional silent bfg tricks, and the player will \"oof\" on two-sided lines",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO)

		// Use Boom's algorithm for determining the actors in, or at least touching, a sector
		CVAR (co_boomsectortouch, "0", "Use a finer-grained, faster, and more accurate test for actors that are touching a sector (i.e. those affected if it moves)",
			  CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO)

		// Enable/disable the "level 8 full sound at far distances" feature
		CVAR (co_level8soundfeature, "0", "Enable/disable the \"level 8 full sound at far distances\" feature",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH)

		// Fix the blockmap collision bug
		CVAR (co_blockmapfix, "0", "Fix the blockmap collision bug",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH)

		// Enable/disable zdoom-based gravity and physics interactions
		CVAR (co_zdoomphys, "0", "Enable/disable zdoom-based gravity and physics interactions",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO)

		// 0 - Play the switch resetting sound at map location (0,0) like the vanilla bug
		// 1 - switch sounds attenuate with distance like plats and doors.
		CVAR (co_zdoomswitches, "0", "Play switch sounds attenuate with distance",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO)

		// Use ZDoom's sound curve instead of vanilla Doom's
		CVAR (co_zdoomsoundcurve, "0", "Use ZDoom's sound curve instead of vanilla Doom's",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO)

		// Turns off the west-facing silent spawns vanilla bug
		CVAR (co_nosilentspawns, "0", "Turns off the west-facing silent spawns vanilla bug",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO)

		// Increase precision of autoatim
		CVAR (co_fineautoaim, "0", "Increase precision of autoatim",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO)

		// Dead player's view follows the actor who killed them
		CVAR (cl_deathcam, "1", "Dead player's view follows the actor who killed them",
		      CVARTYPE_BOOL, CVAR_ARCHIVE)

		CVAR (cl_predictsectors, "1", "Move floors and ceilings immediately instead of waiting for confirmation",
		     CVARTYPE_BOOL, CVAR_ARCHIVE)

		CVAR (cl_predictpickup, "1", "Predict weapon pickups", CVARTYPE_BOOL, CVAR_ARCHIVE)

		// Movebob
		CVAR_FUNC_DECL (cl_movebob, "1.0", "Adjust weapon and movement bobbing",
		      CVARTYPE_BOOL, CVAR_CLIENTARCHIVE | CVAR_NOENABLEDISABLE)

		CVAR (cl_rockettrails, "0", "Rocket trails on/off (currently unused)", CVARTYPE_BOOL,  CVAR_ARCHIVE)

		// [AM] Force a player to respawn.
		CVAR (sv_forcerespawn, "0", "Force a player to respawn.",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
		// [AM] Force a player to respawn after a set amount of time
		CVAR (sv_forcerespawntime, "30", "Force a player to respawn after a set amount of time",
		      CVARTYPE_WORD, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)
		CVAR (sv_spawndelaytime, "0.0", "Force a player to wait a period (in seconds) before respawning",
		      CVARTYPE_FLOAT, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)

		CVAR_FUNC_DECL (sv_gravity, "800", "Gravity of the environment",
		      CVARTYPE_INT, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)
		CVAR_FUNC_DECL (sv_aircontrol, "0.00390625", "How much control the player has in the air",
		      CVARTYPE_FLOAT, CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)

		CVAR_FUNC_DECL (sv_splashfactor, "1.0", "Rocket explosion thrust effect?",
		      CVARTYPE_FLOAT,  CVAR_ARCHIVE | CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)


		// Misc stuff
		// ----------

		// debugging mode
		CVAR (developer, "0", "debugging mode",
		      CVARTYPE_BOOL, CVAR_NULL)
		// Chase camera settings
		CVAR (chase_height,     "-8", "Height of chase camera",
		      CVARTYPE_WORD, CVAR_CLIENTARCHIVE | CVAR_NOENABLEDISABLE)
		CVAR (chase_dist,    "90", "Chase camera distance",
		      CVARTYPE_WORD, CVAR_CLIENTARCHIVE | CVAR_NOENABLEDISABLE)
		// Generate centerview when -mlook encountered?
		CVAR (lookspring,    "1", "Generate centerview when mlook encountered",
		      CVARTYPE_BOOL, CVAR_CLIENTARCHIVE)
		// Allows players to walk through other players
		CVAR (sv_unblockplayers, "0", "Allows players to walk through other players",
		      CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_LATCH | CVAR_SERVERINFO)
		// [Spleen] Allow custom WAD directories to be specified in a cvar
		CVAR (waddirs, "", "Allow custom WAD directories to be specified",
		      CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)

		// Experimental settings (all categories)
		// =======================================

		// Speedhack code (server related)
		CVAR (sv_speedhackfix,     "0", "Experimental anti-speedhack code",
		      CVARTYPE_BOOL, CVAR_SERVERARCHIVE)

		{0x0, 0x0, 0x0, CVARTYPE_NONE, 0x0}
};

cvar_t sv_misc_cvars[] =
{
	// Log file settings
	// -----------------

	// Server administrative settings
	// ------------------------------
		// [Xyltol 02/27/2012] Hostname retrieval for Scoreboard
	CVAR (sv_hostname,      "Untitled Odamex Server", "Server name to appear on masters, clients and launchers",
	   CVARTYPE_STRING, CVAR_SERVERARCHIVE | CVAR_NOENABLEDISABLE | CVAR_SERVERINFO)

	// Server "message of the day" that gets to displayed to clients upon connecting
	CVAR (sv_motd, "Welcome to Odamex", "Message Of The Day", CVARTYPE_STRING,
			CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)

	// Administrator email address
	CVAR (sv_email, "email@domain.com", "Administrator email address",
			CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)
	// Website of this server/other
	CVAR (sv_website, "http://odamex.net/", "Server or Admin website",
			CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)

	// Extended timestamp info (dd/mm/yyyy hh:mm:ss)
	CVAR (log_fulltimestamps, "0", "Extended timestamp info (dd/mm/yyyy hh:mm:ss)",
			CVARTYPE_BOOL, CVAR_ARCHIVE)
	CVAR (log_packetdebug, "0", "Print debugging messages for each packet sent",
			CVARTYPE_BOOL, CVAR_ARCHIVE)

	// Enables WAD file downloading
	CVAR (sv_waddownload, "0", "Allow downloading of WAD files from this server",
			CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_SERVERINFO)
	// Enables WAD file download cap
	CVAR (sv_waddownloadcap, "200", "Cap wad file downloading to a specific rate",
			CVARTYPE_INT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	// Reset the current map when the last player leaves
	CVAR (sv_emptyreset, "0", "Reloads the current map when all players leave",
			CVARTYPE_BOOL, CVAR_ARCHIVE)
	// Allow spectators talk to show to ingame players
	CVAR (sv_globalspectatorchat, "1", "Players can see spectator chat",
			CVARTYPE_BOOL, CVAR_ARCHIVE)
	// Maximum corpses that can appear on a map
	CVAR (sv_maxcorpses, "200", "Maximum corpses to appear on map",
			CVARTYPE_WORD, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	// Deprecated
	CVAR (sv_cleanmaps, "", "Deprecated",
	CVARTYPE_NONE, CVAR_NULL)
	// Anti-wall hack code
	CVAR (sv_antiwallhack, "0", "Experimental anti-wallkhack code",
			CVARTYPE_BOOL, CVAR_ARCHIVE | CVAR_LATCH)
	// Maximum number of clients that can connect to the server
	CVAR_FUNC_DECL (sv_maxclients, "4", "Maximum clients that can connect to a server",
			CVARTYPE_BYTE, CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_LATCH | CVAR_NOENABLEDISABLE)
	// Maximum number of players that can join the game, the rest are spectators
	CVAR_FUNC_DECL (sv_maxplayers, "4", "Maximum players that can join the game, the rest are spectators",
			CVARTYPE_BYTE, CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_LATCH | CVAR_NOENABLEDISABLE)
	// Maximum number of players that can be on a team
	CVAR_FUNC_DECL (sv_maxplayersperteam, "0", "Maximum number of players that can be on a team",
			CVARTYPE_BYTE, CVAR_ARCHIVE | CVAR_SERVERINFO | CVAR_LATCH | CVAR_NOENABLEDISABLE)
	// Clients can only join if they specify a password
	CVAR_FUNC_DECL (join_password, "", "Clients can connect if they have this password",
			CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	// TODO: document
	CVAR_FUNC_DECL (spectate_password, "", "",
	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	// Remote console password
	CVAR_FUNC_DECL (rcon_password, "", "Remote console password",
	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	// Advertise on the master servers
	CVAR_FUNC_DECL (sv_usemasters, "1", "Advertise on master servers",
			CVARTYPE_BOOL, CVAR_ARCHIVE)
	// script to run at end of each map (e.g. to choose next map)
	CVAR (sv_endmapscript, "", "Script to run at end of each map (e.g. to choose next map)",
			CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	// script to run at start of each map (e.g. to override cvars)
	CVAR (sv_startmapscript, "", "Script to run at start of each map (e.g. to override cvars)",
			CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	// tracks next map to be played
	CVAR (sv_nextmap, "", "Tracks next map to be played",
	CVARTYPE_STRING, CVAR_NULL | CVAR_NOENABLEDISABLE)
	// Determines whether Doom 1 episodes should carry over.
	CVAR (sv_loopepisode, "0", "Determines whether Doom 1 episodes carry over",
			CVARTYPE_BOOL, CVAR_ARCHIVE)
	// GhostlyDeath <August 14, 2008> -- Randomize the map list
	CVAR_FUNC_DECL (sv_shufflemaplist, "0", "Randomly shuffle the maplist",
			CVARTYPE_BOOL, CVAR_ARCHIVE)

	// Network settings
	// ----------------

	// Network compression (experimental)
	CVAR (sv_networkcompression, "1", "Network compression",
	CVARTYPE_BOOL, CVAR_ARCHIVE)
	// NAT firewall workaround port number
	CVAR (sv_natport, "0", "NAT firewall workaround, this is a port number",
			CVARTYPE_INT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	// The time difference in which a player message to all players can be repeated
	// in seconds
	CVAR (sv_flooddelay, "1.5", "Flood protection time",
	CVARTYPE_FLOAT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	// [Spleen] limits the rate of clients to avoid bandwidth issues
	CVAR_FUNC_DECL (sv_maxrate, "200", "Forces clients to be on or below this rate",
			CVARTYPE_INT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	#ifdef ODA_HAVE_MINIUPNP
	// Enable Universal Plug and Play to auto-configure a compliant router
	CVAR (sv_upnp, "1", "UPnP support",
	CVARTYPE_BOOL, CVAR_ARCHIVE)
	// The timeout looking for upnp routers
	CVAR (sv_upnp_discovertimeout, "2000", "UPnP Router discovery timeout",
	CVARTYPE_INT, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	// Description for the port mapping
	CVAR (sv_upnp_description, "", "Router-side description of port mapping",
	CVARTYPE_STRING, CVAR_ARCHIVE | CVAR_NOENABLEDISABLE)
	#endif

	// Gameplay settings
	// =================

	// (CTF/Team play): Teams that are enabled
	CVAR (sv_teamsinplay, "2", "Teams that are enabled", CVARTYPE_BYTE,
			CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_LATCH | CVAR_NOENABLEDISABLE)
	// (CTF) Flags dropped by the player must be returned manually
	CVAR (ctf_manualreturn, "0", "Flags dropped must be returned manually",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
	// (CTF) Team flag must be at home pedestal for any captures of an enemy flag
	// returned to said pedestal to count as a point
	CVAR (ctf_flagathometoscore, "1", "Team flag must be at home pedestal for any captures of an enemy flag returned to said pedestal to count as a point",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)
	// (CTF) Time for a dropped flag to be returned to its home base, in seconds
	CVAR (ctf_flagtimeout, "10", "Time for a dropped flag to be returned automatically to its home base",
			CVARTYPE_BYTE, CVAR_SERVERARCHIVE | CVAR_SERVERINFO | CVAR_NOENABLEDISABLE)
	// (ALL) Display a countdown to all players during intermission screen
	//CVAR (sv_inttimecountdown, "0",  "Display time left for an intermission screen to next map",
	//      CVARTYPE_BYTE, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)

	CVAR (sv_ticbuffer, "1", "Buffer controller input from players experiencing sudden latency spikes for smoother movement",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_SERVERINFO)

	// Ban settings
	// ============

	CVAR (sv_banfile, "banlist.json", "Default file to save and load the banlist.",
			CVARTYPE_STRING, CVAR_SERVERARCHIVE | CVAR_NOENABLEDISABLE)
	CVAR (sv_banfile_reload, "0", "Number of seconds to wait between automatically loading the banlist.",
			CVARTYPE_INT, CVAR_SERVERARCHIVE | CVAR_NOENABLEDISABLE)

	// Vote settings
	// =============

	// Enable or disable counting absnet voters as "no" if a vote is undecided.
	CVAR (sv_vote_countabs, "1", "Count absent voters as 'no' if the vote timer runs out.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	// A percentage of players needed to pass a vote.
	CVAR (sv_vote_majority, "0.5", "Ratio of yes votes needed for vote to pass.",
			CVARTYPE_FLOAT, CVAR_SERVERARCHIVE | CVAR_NOENABLEDISABLE)
	// Spectators are allowed to vote.
	CVAR (sv_vote_speccall, "1", "Spectators are allowed to callvote.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	// Spectators are allowed to vote.
	CVAR (sv_vote_specvote, "1", "Spectators are allowed to vote.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	// Number of seconds that a countdown lasts.
	CVAR (sv_vote_timelimit, "30", "Amount of time a vote takes in seconds.",
			CVARTYPE_INT, CVAR_SERVERARCHIVE | CVAR_NOENABLEDISABLE)
	// Number of seconds between callvotes.
	CVAR (sv_vote_timeout, "60", "Timeout between votes in seconds.",
			CVARTYPE_INT, CVAR_SERVERARCHIVE | CVAR_NOENABLEDISABLE)

	// Enable or disable specific votes.
	CVAR (sv_callvote_coinflip, "0", "Clients can flip a coin.",
	CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	CVAR (sv_callvote_kick, "0", "Clients can votekick other players.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	CVAR (sv_callvote_forcespec, "0", "Clients can vote to force a player to spectate.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	CVAR (sv_callvote_forcestart, "0", "Clients can vote to force the match to start.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	CVAR (sv_callvote_map, "0", "Clients can vote to switch to a specific map from the server's maplist.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	CVAR (sv_callvote_nextmap, "0", "Clients can vote on progressing to the next map.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	CVAR (sv_callvote_randmap, "0", "Clients can vote to switch to a random map from the server's maplist.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	CVAR (sv_callvote_randcaps, "0", "Clients can vote to force the server to pick two players from the pool of ingame players and force-spectate everyone else.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	CVAR (sv_callvote_randpickup, "0", "Clients can vote to force the server to pick a certian number of players from the pool of ingame players and force-spectate everyone else.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	CVAR (sv_callvote_restart, "0", "Clients can vote to reload the current map.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	CVAR (sv_callvote_fraglimit, "0", "Clients can vote a new fraglimit.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	CVAR (sv_callvote_scorelimit, "0", "Clients can vote a new scorelimit.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)
	CVAR (sv_callvote_timelimit, "0", "Clients can vote a new timelimit.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE)

	// Warmup mode
	CVAR (sv_warmup, "0", "Enable a 'warmup mode' before the match starts.",
			CVARTYPE_BOOL, CVAR_SERVERARCHIVE | CVAR_LATCH)
	CVAR (sv_warmup_autostart, "1.0", "Ratio of players needed for warmup to automatically start the game.",
			CVARTYPE_FLOAT, CVAR_SERVERARCHIVE | CVAR_LATCH | CVAR_NOENABLEDISABLE)
	CVAR (sv_countdown, "5", "Number of seconds to wait before starting the game from warmup or restarting the game.",
			CVARTYPE_BYTE, CVAR_SERVERARCHIVE | CVAR_LATCH | CVAR_NOENABLEDISABLE)

	// Experimental settings (all categories)
	// =======================================

	// Do not run ticker functions when there are no players
	CVAR (sv_emptyfreeze, "0", "Experimental: Does not progress the game when there are no players",
			CVARTYPE_BOOL, CVAR_ARCHIVE)

	{0x0, 0x0, 0x0, CVARTYPE_NONE, 0x0}
};

