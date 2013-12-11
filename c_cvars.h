#ifndef C_CVARS_H_
#define C_CVARS_H_

#define CVAR_NULL               0 // [deathz0r] no special properties
#define CVAR_ARCHIVE            1 // set to cause it to be saved to vars.rc
#define CVAR_USERINFO           2 // added to userinfo  when changed
#define CVAR_SERVERINFO         4 // [Toke - todo] Changed the meaning of this flag
                                  // it now describes cvars that clients will be
                                  // informed if changed
#define CVAR_NOSET              8 // don't allow change from console at all,
                                  // but can be set from the command line
#define CVAR_LATCH             16 // save changes until server restart
#define CVAR_UNSETTABLE        32 // can unset this var from console
#define CVAR_DEMOSAVE          64 // save the value of this cvar_t in a demo
#define CVAR_MODIFIED         128 // set each time the cvar_t is changed
#define CVAR_ISDEFAULT        256 // is cvar unchanged since creation?
#define CVAR_AUTO             512 // allocated, needs to be freed when destroyed
#define CVAR_NOENABLEDISABLE 1024 // [Nes] No substitution (0=disable, 1=enable)
#define CVAR_SERVERARCHIVE   4096 // [Nes] Server version of CVAR_ARCHIVE
#define CVAR_CLIENTARCHIVE   8192 // [Nes] Client version of CVAR_ARCHIVE

#include <string.h>

typedef enum
{
     CVARTYPE_NONE = 0 // Used for no sends

    ,CVARTYPE_BOOL
    ,CVARTYPE_BYTE
    ,CVARTYPE_WORD
    ,CVARTYPE_INT
    ,CVARTYPE_FLOAT
    ,CVARTYPE_STRING

    ,CVARTYPE_MAX = 255
} cvartype_t;

struct cvar_t {
	char *name;
	char *def_val;
	char *descript;
	cvartype_t type;
	int properties;
};

#define CVAR(_a,_b,_c,_d,_e) {#_a,strdup(_b),_c,_d,_e},
#define CVAR_FUNC_DECL CVAR

extern cvar_t cl_macro_cvars[];
extern cvar_t cl_misc_cvars[];
extern cvar_t cl_mp_cvars[];

extern cvar_t sv_gameplay_cvars[];
extern cvar_t sv_misc_cvars[];

void CVAR_MenuFromList(void *widget, void *user_data);
void CVAR_SaveSettings();
void CVAR_LoadSettings();

//void CVAR_SaveCvars(char *file, ...);

#endif /* C_CVARS_H_ */
