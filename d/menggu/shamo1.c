inherit ROOM; 
#include <ansi.h>
#include <random_clone.h>

void create() 
{ 
        set("short", "草原中心");
        set("long", @LONG
这里是草原的中央。
LONG
        );
	
        set("exits", ([ /* sizeof() == 3 */
   //"south" : __DIR__"zoudao2.c",
]));
        set("migong_name","库布齐沙漠"),
        set("no_clean_up", 1);
        set("no_reset", 1);
		set("outdoors", "menggu_s");
        setup();
}

int start()
{
    object ob=this_object();
    object exit1=load_object(__DIR__"random_shaomo1_e");
    object exit2=load_object("/d/huanghenorth/hhb");
    object exit3=load_object(__DIR__"random_shaomo1_w");
    object exit4=load_object(__DIR__"random_shaomo1_n");
    set("migong_name","库布齐沙漠"),
    gene("沙漠",4,ob,exit1,exit2,exit3,exit4,0); //样本，随机迷宫8个参数，第一个为迷宫地貌类型，在include/random_map.h可查，第二个为迷宫复杂度，3为迷宫原点，4-7为出口，无出口则需补0,第八个参数为迷宫出口对于真实地图是否可见，不可见为1，可见为0
    call_out("over",3600*8);//沙漠每8小时刷新一次。
    return 1;
}

int over()
{
    clear_all();
	start();
    return 1;
}