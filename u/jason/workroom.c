// Room: /u/jason/workroom.c
// Date: by jason(残叶) Tue Dec 25 22:32:33 2007
inherit ROOM;

//test svn
void create()
{
	set("short", "空空如也的房间");
	set("long", @LONG
这是一间冷冰冰的屋子，四壁，地板，屋顶都是由冰冷的大理石建造的。你来到这间屋子，感觉不到一丝的暖意。
仿佛所有的愉快，轻松，乐观，积极都被无情的岁月带走，只留下一个空空的口袋，呆呆着随波逐流。只有偶尔
的回忆，能带来一丝丝的温暖。
LONG
	);
	set("no_clean_up", 0);
	set("realmap", "                                               
                                    
                         [1;32m残叶工作室[2;37;0m            
                                    
                                               
");
	set("exits", ([ /* sizeof() == 2 */
		  "2" : "/d/wizard/wizard_room",
		  "1" : "/d/city/guangchang",
		]));
	set("valid_startroom", 1);
	setup();
//okokok
}

