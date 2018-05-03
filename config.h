/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Inconsolata:size=11" };
static const char dmenufont[]       = "Inconsolata:size=12";

static const char border1[]         = "#090908";
static const char border2[]         = "#d09d3f";

static const char background1[]     = "#090908";
static const char background2[]     = "#101110";

static const char foreground1[]     = "#848981";
static const char foreground2[]     = "#d09d3f";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { foreground1, background1, border1 },
    [SchemeSel] =  { foreground2, background2, border2  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /*  class                  instance  title  tags mask  isfloating  monitor */
    {   "Thunar",              NULL,     NULL,  2,         0,          1     },
    {   "st-256color",         NULL,     NULL,  1,         0,          1     },
    {   "urxvt-256color",      NULL,     NULL,  1,         0,          1     },
    {   "URxvt",               NULL,     NULL,  1,         0,          1     },
    {   "Firefox",             NULL,     NULL,  1,         0,          0     },
    {   "firefox",             NULL,     NULL,  1,         0,          0     },
    {   "Surf",                NULL,     NULL,  1,         0,          0     },
    {   "krita",               NULL,     NULL,  5,         0,          0     },
    {   "Chromium-browser",    NULL,     NULL,  2,         0,          0     },
    {   "chromium-browser",    NULL,     NULL,  2,         0,          0     },
    {   "Chromium",            NULL,     NULL,  2,         0,          0     },
    {   "chromium",            NULL,     NULL,  2,         0,          0     },
    {   "Thunderbird",         NULL,     NULL,  1 << 2,    0,          0     },
    {   "thunderbird",         NULL,     NULL,  1 << 2,    0,          0     },
    {   "Slack",               NULL,     NULL,  1 << 8,    0,          1     },
    {   "slack",               NULL,     NULL,  1 << 8,    0,          1     },
    {   "Wire",                NULL,     NULL,  1 << 8,    0,          1     },
    {   "wire",                NULL,     NULL,  1 << 8,    0,          1     },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "[M]",      monocle },
    // { "><>",      NULL },    /* no layout function means floating behavior */
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
static const char *dmenucmd[] = { "dmenu_run", "-p", ">>", "-fn", dmenufont, "-nb", background1, "-nf", foreground1, "-sb", background2, "-sf", foreground2, "-l", "20", NULL };
static const char *passmenu[] = { "passmenu", "-p", "*>", "-fn", dmenufont, "-nb", background1, "-nf", foreground1, "-sb", background2, "-sf", foreground2, "-l", "20", NULL };
static const char *termcmd[]  = { "/home/jonathan/.dwm/scripts/termcmd", NULL };
static const char *browser[]  = { "surf", "duckduckgo.com" };
static const char *chrome[]  = { "chromium", NULL};
static const char *chrome_incognito[]  = { "chromium", "--incognito", NULL };
static const char *firefox[]  = { "firefox", NULL};
static const char *firefox_private[]  = { "firefox", "-private-window", NULL};
static const char *printscreen[]  = { "/home/jonathan/.dwm/scripts/screenshot", NULL};
static const char *poweroff[]  = { "systemctl", "poweroff", NULL};
static const char *reboot[]  = { "systemctl", "reboot", NULL};
static const char *volup[]  = { "amixer", "-c", "0",  "--",  "set",  "Master",  "1+", NULL };
static const char *voldown[]  = { "amixer", "-c", "0",  "--",  "set",  "Master",  "1-", NULL };
static const char *volmute[]  = { "amixer", "-c", "0",  "--",  "set",  "Master",  "0", NULL };
static const char *brightup[]  = { "/home/jonathan/.dwm/scripts/brightup", NULL };
static const char *brightdown[]  = { "/home/jonathan/.dwm/scripts/brightdown", NULL };
static const char *killscreensaver[]  = {"pkill", "xscreensaver", NULL };
static const char *killmon[]  = {"mons", "-o", "HDMI1", "--off", NULL };
static const char *attachmon[]  = {"/home/jonathan/.screenlayout/work.sh", NULL};

#define  XF86AudioMute          0x1008ff12
#define  XF86AudioLowerVolume   0x1008ff11
#define  XF86AudioRaiseVolume   0x1008ff13
#define  XF86MonBrightnessUp    0x1008ff02
#define  XF86MonBrightnessDown  0x1008ff03

static Key keys[] = {
    /* modifier                     key        function        argument */
    { ControlMask,                  XK_space,  spawn,          {.v = dmenucmd } },
    { Mod1Mask,                     XK_space,  spawn,          {.v = passmenu } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_w,      spawn,          {.v = browser } },
    { MODKEY,                       XK_g,      spawn,          {.v = chrome } },
    { MODKEY,                       XK_m,      spawn,          {.v = firefox } },
    { MODKEY|ShiftMask,             XK_g,      spawn,          {.v = chrome_incognito } },
    { MODKEY|ShiftMask,             XK_m,      spawn,          {.v = firefox_private } },
    { 0,                            XK_Print,  spawn,          {.v = printscreen } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY|ControlMask,           XK_j,      incnmaster,     {.i = +1 } },
    { MODKEY|ControlMask,           XK_k,      incnmaster,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      setmfact,       {.f = -0.05} },
    { MODKEY|ShiftMask,             XK_k,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_space,  zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_e,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_h,      focusmon,       {.i = -1 } },
    { MODKEY,                       XK_l,      focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_h,      tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_l,      tagmon,         {.i = +1 } },
    { ShiftMask,                    XK_F12,    spawn,          {.v = poweroff } },
    { ControlMask|ShiftMask,        XK_F12,    spawn,          {.v = reboot } },
    { 0,                            XK_F8,     spawn,          {.v = killscreensaver } },
    { 0,                            XK_F10,    spawn,          {.v = killmon } },
    { 0,                            XK_F11,    spawn,          {.v = attachmon } },
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
    { 0,                            XF86AudioMute,  spawn,          {.v = volmute } },
    { 0,                            XF86AudioRaiseVolume,  spawn,          {.v = volup } },
    { 0,                            XF86AudioLowerVolume,  spawn,          {.v = voldown } },
    { 0,                            XF86MonBrightnessUp,   spawn,          {.v = brightup } },
    { 0,                            XF86MonBrightnessDown, spawn,          {.v = brightdown } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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
