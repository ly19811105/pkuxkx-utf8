 // daritang

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short",HIY "大日法堂"NOR);
        set("long",@LONG
这是一间气势雄伟的法堂，法堂正中立着大日如来佛法象，四壁上端坐着
座座比规模较小的法象，是如来的十二大弟子。黄缦低垂，庄严肃穆。一座香
炉，香烟缭绕，袅袅上升。炉前跌坐着一位须发全白的老僧，喃喃低语，似乎
正在念诵什么佛。
LONG);
       set("exits", ([
        "west" : __DIR__"luoweitang"
          ]));
         set("objects", ([
                "/kungfu/class/dalunsi/huofo.c" : 1,
             ]));
          setup();
   
}

