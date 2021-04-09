#include <ansi.h>
inherit __DIR__"yanmenguan.c";
string look_notice();
void create()
{
	set("short", "官道");
	set("long", @LONG
这是一条官道，前方的山路往西南面通向雁门关，墙上挂了个木牌(notice)。
LONG
	);
    set("item_desc", ([
        "notice" : (:look_notice:),
	]));
    set("exits", ([
        "southwest" : __DIR__"guandao2",        
        "northwest" : "d/saiwai/guandaosw",
        ]));
    set("road_no",1);
    set("objects", ([
		
        __DIR__"npc/weishi" : 2,
        __DIR__"npc/mes" : 1,
		
	    ]));
	set("outdoors", "jinyang");
	setup();
	
}

string look_notice()
{
    object pl,center=load_object("/d/jinyang/yanmenguan/center");
    string msg,msg_list,*list=center->query("list");
    int i,count=0;
    if (sizeof(list)<1)
    {
        msg="现在雁门关战役无人报名。\n";
    }
    else
    {
        for (i=0;i<sizeof(list);i++)
        {
            if (pl=find_player(list[i]))
            {
                count+=1;
                msg_list=HIW+pl->query("name")+" "+NOR;
            }
        }
        msg="雁门关战役现有"+HIR+chinese_number(count)+NOR+"人报名，分别是：\n";
        msg+=msg_list;
        msg+="\n";
        msg+="尚缺"+HIG+chinese_number(8-count)+NOR+"人，方可开启任务。\n";
    }
    return msg;
}


