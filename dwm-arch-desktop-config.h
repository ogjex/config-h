/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 2;        /* 2 is the default spacing around the bar's font */
static const char *fonts[]          = { "JetbrainsMono:size=16" };
static const char dmenufont[]       = "JetbrainsMono:size=16";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const char *const autostart[] = {
	"alacritty", NULL,
	"1password", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagsalt[] = { "", "󰖟", "󰻣", "󱓩", "󱍻", "󰚗", "", "󰄯", "󰄯" };
static const int momentaryalttags = 1; /* 1 means alttags will show only when key is held down*/
static const int taglayouts[] = { 0, 1, 1, 0, 0, 0, 0, 0, 0 };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     		NULL,       NULL,       0,            1,           -1 },
	/* 1 - terminal and system tools */	
	/* 2 - browsing */	
	{ "firefox",  		NULL,       NULL,       1 << 1,       0,           -1 },
	/* 3 - email*/	
	{ "Brave-browser",  	NULL,       NULL,       1 << 2,       0,           -1 },
	/* 4 - writing*/	
	{ "obsidian",	  	NULL,       NULL,       1 << 3,       0,           -1 },
	/* 5 - Reference management */	
	{ "Zotero",	  	NULL,       NULL,       1 << 4,       0,           -1 },
	/* 6 - development, */	
	/* 7 - Virtual Machines */	
	/* 8 - unused */	
	/* 9 - background apps with helpers */	
	{ "1password",	  	NULL,       NULL,       1 << 8,       0,           -1 },
	{ "1password",	  	NULL,       "Lock Screen - 1Password",       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     	= 0.75; /* factor of master area size [0.05..0.95] */
static const int nmaster     	= 1;    /* number of clients in master area */
static const int resizehints 	= 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; 	/* 1 will force focus on the fullscreen window */
static int attachbelow 		= 1;    /* 1 means attach after the currently active window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "MM:",      tilewide },/* 0 - first entry is default */
	{ ":M:",      centeredmaster },// 1
	/*{ "[]=",      tile },*/  
	{ "[M]",      monocle },// 2 
	{ "[@]",      spiral },// 3 
	{ "[\\]",     dwindle },// 4   
	//{ "H[]",      deck },
	{ "TTT",      bstack },// 5
	{ "===",      bstackhoriz },// 6
	//{ "HHH",      grid },
	//{ "###",      nrowgrid },
	//{ "---",      horizgrid },
	//{ ":::",      gaplessgrid },
	//{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },   /* 7 - no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static const char *copycmd[]  = { "dmenu_cliphist", "add", NULL };
static const char *cliphistcmd[]  = { "dmenu_cliphist", "sel", NULL };
static const char *devcmd[]  = { "zellij", NULL };
static const char *browsecmd[]  = { "firefox", NULL };
static const char *coordcmd[]  = { "brave-browser", NULL };
static const char *notecmd[]  = { "obsidian", NULL };
static const char *refcmd[]  = { "zotero", NULL };
static const char *pwcmd[]  = { "1password", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,			XK_c,      spawn,          {.v = copycmd } },
	{ MODKEY|ShiftMask,		XK_c,      spawn,          {.v = cliphistcmd } },
	{ MODKEY|ShiftMask,		XK_F1,     spawn,          {.v = devcmd } },
	{ MODKEY|ShiftMask,	        XK_F2,     spawn,          {.v = browsecmd } },
	{ MODKEY|ShiftMask,	        XK_F3,     spawn,          {.v = coordcmd } },
	{ MODKEY|ShiftMask,             XK_F4,     spawn,          {.v = notecmd } },
	{ MODKEY|ShiftMask,		XK_F5,     spawn,          {.v = refcmd } },
	{ MODKEY|ShiftMask,		XK_F6,     spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_F7,     spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_F8,     spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_F9,     spawn,          {.v = pwcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_b,	   toggleAttachBelow, {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_s,	   togglesticky,   {0} },
	{ MODKEY,                       XK_Right,  viewnext,       {0} },
	{ MODKEY,                       XK_Left,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

