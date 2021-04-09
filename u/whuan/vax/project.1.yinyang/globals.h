// globals.h
// this file will be automatically included by the driver
// for XKX mudlib, by Xiang
// Important directories

#pragma save_binary
#define INC_DIR		"/include/"
#define COMMAND_DIR	"/cmds/"
#define CONFIG_DIR	"/adm/etc/"
#define DATA_DIR	"/data/"
#define HELP_DIR	"/help/"
#define LOG_DIR		"/log/"
#define PRIVATE_DIR "/d/private/"
#define CM_DIR "/u/aiai/create_menpai/"
#define BABY_DIR "/d/baby/"

// Daemons
#define ALIAS_D		"/adm/daemons/aliasd"
#define BAN_D		"/adm/daemons/band"
#define BBS_D           "/adm/daemons/bbsd"
#define CREATE_D       "/adm/daemons/created"
#define CHANNEL_D	"/adm/daemons/channeld"
#define CHAR_D		"/adm/daemons/chard"
#define CHINESE_D	"/adm/daemons/chinesed"
#define CNAME_D       "/adm/daemons/cnamed"
#define COMBAT_D	"/adm/daemons/combatd"
#define COMMAND_D	"/adm/daemons/commandd"
#define EMOTE_D		"/adm/daemons/emoted"
#define FINGER_D	"/adm/daemons/fingerd"
#define FTP_D		"/adm/daemons/ftpd"
#define INQUIRY_D	"/adm/daemons/inquiryd"
#define LANGUAGE_D              "/adm/daemons/languaged"
#define LOGIN_D		"/adm/daemons/logind"
#define MONEY_D		"/adm/daemons/moneyd"
#define MONITOR_D	"/adm/daemons/monitord"
#define NAME_D		"/adm/daemons/named"
#define NATURE_D	"/adm/daemons/natured"
#define NEWS_D		"/adm/daemons/newsd"
#define PIG_D		"/adm/daemons/pigd"
#define PROFILE_D	"/adm/daemons/profiled"
#define RANK_D		"/adm/daemons/rankd"
#define READWRITE_D	"/adm/daemons/readwrited"
#define PET_D           "/adm/daemons/petd"
#define SECURITY_D	"/adm/daemons/securityd"
#define STORY_D	        "/adm/daemons/storyd"
#define TASK_D 		"/adm/daemons/taskd"
#define VIRTUAL_D	"/adm/daemons/virtuald"
#define WEAPON_D	"/adm/daemons/weapond"
#define TOP_D           "/adm/daemons/topd"
#define TOPTEN_D        "/adm/daemons/toptend"
#define MUSIC_D        "/adm/daemons/musicd"
#define CMENPAI_D "/adm/daemons/cmenpaid"
#define CLASS_D(x)	("/kungfu/class/" + x)
#define SKILL_D(x)	("/kungfu/skill/" + x)
#define CONDITION_D(x)	("/kungfu/condition/" + x)
// self_create_skill
#define PLAYER_SKILL_D(x)	("/kungfu/player_skill/" + x)
// yinyang
#define YINYANG_D 	"/adm/daemons/yinyangd"
//add for quest
#define AQUEST_D(x) ("/quest/aquest/aquest" + x)
#define BQUEST_D(x) ("/quest/bquest/bquest" + x)
#define MDFIVE_D	"/adm/daemons/mdfived"
#define ONLINE_D        "/adm/daemons/onlineuserd"
#define EXAMINE_D    "/adm/daemons/examined"

// Clonable/Non-inheritable Standard Objects
#define COIN_OB		"/clone/money/coin"
#define CORPSE_OB	"/clone/misc/corpse"
#define GOLD_OB		"/clone/money/gold"
#define LOGIN_OB	"/clone/user/login"
#define MASTER_OB	"/adm/single/master"
#define MAILBOX_OB	"/clone/misc/mailbox"
#define SILVER_OB	"/clone/money/silver"
#define SIMUL_EFUN_OB	"/adm/single/simul_efun"
#define USER_OB		"/clone/user/user"
#define VOID_OB		"/clone/misc/void"
#define PET_OB          "/clone/npc/pet.c"
#define BABY_OB          "/clone/npc/baby.c"

// Inheritable Standard Objects
#define BANK		"/inherit/room/bank"
#define HSBG_BOARD  "/inherit/misc/hboard"
#define HSLJ_BOARD	"/inherit/misc/hsljboard"
#define BULLETIN_BOARD	"/inherit/misc/bboard"
#define TOWIZ_BOARD  "/inherit/misc/towizboard"
#define PLAN_BOARD  "/inherit/misc/jboard"
#define FIGHT_BOARD  "/inherit/misc/fboard"
#define CHARACTER	"/inherit/char/char"
#define COMBINED_ITEM	"/inherit/item/combined"
#define EQUIP		"/inherit/misc/equip"
#define FORCE		"/inherit/skill/force"
#define HOCKSHOP	"/inherit/room/hockshop"
#define ITEM		"/inherit/item/item"
#define MUSIC		"/inherit/item/instrument"
#define LIQUID		"/inherit/food/liquid"
#define MONEY		"/inherit/item/money"
#define NPC		"/inherit/char/npc"
#define NPC_TRAINEE	"/inherit/char/trainee"
#define PILL		"/inherit/medicine/pill"
#define POWDER		"/inherit/medicine/powder"
#define ROOM		"/inherit/room/room"
#define SKILL		"/inherit/skill/skill"

// User IDs

#define ROOT_UID        "XKX"
#define BACKBONE_UID	"BackBone"


//自造武功
#define SKILL_MODEL_UNARMED    "/kungfu/vast/skill_model_unarmed.c"
#define SKILL_MODEL_WEAPON     "/kungfu/vast/skill_model_weapon.c"
#define SKILL_MODEL_DEFAULT    "/kungfu/vast/skill_model_default.c"
#define PLAYER_SKILL_D(x)	("/kungfu/player_skill/" + x)

//小宝任务
#define QUESTW_D(x)	("/new_quest/xiaobao/qwlist" + x)
#define MAX_LOOP 3000
// Features

#define F_ACTION		"/feature/action.c"
#define F_ALIAS			"/feature/alias.c"
#define F_APPRENTICE		"/feature/apprentice.c"
#define F_ATTACK		"/feature/attack.c"
#define F_ATTRIBUTE		"/feature/attribute.c"
#define F_AUTOLOAD		"/feature/autoload.c"
#define F_CLEAN_UP		"/feature/clean_up.c"
#define F_COMMAND		"/feature/command.c"
#define F_CONDITION		"/feature/condition.c"
#define F_DAMAGE		"/feature/damage.c"
#define F_DBASE			"/feature/dbase.c"
#define F_DEALER		"/feature/dealer.c"
#define F_EDIT			"/feature/edit.c"
#define F_EQUIP			"/feature/equip.c"
#define F_FINANCE		"/feature/finance.c"
#define F_FOOD			"/feature/food.c"
#define F_HOCKSHOP           "/feature/hockshop.c"
#define F_LIQUID		"/feature/liquid.c"
#define F_MASTER		"/inherit/char/master.c"
#define F_MAILQUEST             "/inherit/char/mailquest.c"
#define F_MESSAGE		"/feature/message.c"
#define F_MORE			"/feature/more.c"
#define F_MOVE			"/feature/move.c"
#define F_NAME			"/feature/name.c"
#define F_NEWQUEST		"/feature/newquest.c"
#define F_ONEOWNER		"/feature/oneowner.c"
#define F_QUEST			"/feature/quest.c"
#define F_SAVE			"/feature/save.c"
#define F_SHELL			"/feature/shell.c"
#define F_SKILL			"/feature/skill.c"
#define F_TEAM			"/feature/team.c"
#define F_TREEMAP		"/feature/treemap.c"
#define F_VENDOR		"/feature/dealer.c"
#define F_SSERVER		"/feature/sserver.c"
#define F_UNIQUE		"/feature/unique.c"
#define F_VI "/feature/vi"

#define F_QUESTMASTER		"/inherit/char/questmaster.c"
#define F_AQUESTMASTER		"/inherit/char/aquestmaster.c"
#define F_BQUESTMASTER		"/inherit/char/bquestmaster.c"
#define F_TRIGGER 		"/feature/trigger" 

//随机迷宫
#define RANDOM_MAZE          "/adm/daemons/randommazed.c"

//宝石镶嵌系统
#define F_GEMS			"/feature/gems.c"
#define S_WEAPON		"/inherit/gems/weapon.c"
#define LDC_NPC(x)             ("/d/ludingshan/npc/" + x)
#define LDC_OBJ(x)             ("/d/ludingshan/obj/" + x)
#define GEMDROP_D               "/d/ludingshan/gem_dropd.c"
#define NPCGEN_D		"/d/ludingshan/npc_gend.c"

//记录玩家log
#define F_LOGUSER			"/adm/daemons/loguserd.c"

// Profiling switches
//
// If you changed any of these defines, you'll need reboot to make it
// in effect.

#define message_combatd message_vision
#undef PROFILE_COMMANDS
