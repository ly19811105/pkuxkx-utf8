//made by hacky;
#include <ansi.h>

inherit ITEM;

void create()
{
   set_name("全真地图",({"qz-map","map","ditu"}));
   set_weight(100);
   if (clonep() )
        set_default_object(__FILE__);
   else {
   set("long",
"                            全真教地图                                        \n"
"------------------------------------------------------------------------------\n"
"|                                                                            |\n"
"|                                                                            |\n"
"|            走廊--清池--名木--药圃--果园--奇草--芳花                        |\n"
"|             ||                ||                 ||                        |\n"
"|      走廊--走廊              走廊               走廊--走廊                 |\n"
"|       ||                      ||                       ||                  |\n"
"|     寻真台  炼气台  祈真台   走廊    吸景台  散华台  承露台                |\n"
"|       ||      ||      ||      ||       ||      ||      ||                  |\n"
"|     延灵阁--乘云阁--游仙阁--九仙楼 --凝灵阁--飞鸾阁--迎风阁                |\n"
"|       ||      ||      ||      ||       ||      ||      ||                  |\n"
"|     延真楼  午凤楼 逍遥楼 天尊讲经堂 九真楼  焚香楼  静念楼                |\n"
"|       ||      ||      ||      ||       ||      ||                          |\n"
"|      走廊    走廊---精思院--说法院--受道院    走廊                         |\n"
"|       ||                      ||               ||                          |\n"
"|      走廊            校经堂--走廊--写经房---- 钟阁                         |\n"
"|       ||                      ||     ||                                    |\n"
"|      走廊-走廊--门屋--门楼--天尊殿  经楼  斋厨                             |\n"
"|            ||    ||           ||           ||                              |\n"
"|           浴堂  师房        崇虚堂 俗客房 斋堂                             |\n"
"|                               ||     ||    ||                              |\n"
"|     走廊--走廊--走廊--走廊--崇玄台--走廊--走廊--净人坊                     |\n"
"|      ||    ||                 ||                                           |\n"
"|   车牛房 骡马房     烧香坊--三清殿--升遐房                                 |\n"
"|---------------------------------------------------------------------------- \n"
" 月如手抄\n" 
     );
    set("unit","张");
    set("materal","paper");
    set("value",100000);
   }
} 
