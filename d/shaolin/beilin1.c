// Room: /d/shaolin/beilin1.c
// Date: YZC 96/01/19

inherit ROOM;


string look_tower();
string look_stone();


void create()
{
	set("short", "东碑林");
	set("long", @LONG
这里是一大片碑林。虽说是碑林，主要是少林历代高僧的
佛塔灵藏(tower)。一座座佛塔约有二三人高，有汉白玉的，
花冈石的，精工雕凿，薄薄的浮雕面上飞禽走兽，佛谒禅诗，
诸佛众生，可谓无所不包。底座有须弥座的，也有莲花座的，
各态纷呈。佛塔间疏疏落落的立着几块碑(stone)，有的题着
几句诗。
LONG
	);

	set("exits", ([
		"west" : __DIR__"taijie",
	]));

	set("outdoors", "shaolin");
	set("item_desc",([
		"tower"		:	(: look_tower :),
		"stone"		:	(: look_stone :),
	]));

	setup();
}


/* TODO
  tower 题谒，stone 题诗。
  在西碑林吟塔上之谒后，push stone 触发机关，露出密室
*/

string look_tower()
{
	return
	"\n"
	"    ※※※※※※※※※※※※※※※※※※※※\n"
	"    ※※※※　　　　　　　　　　　　※※※※\n"
	"    ※※※※　万物一般，众生平等。　※※※※\n"
	"    ※※※※　　　　　　　　　　　　※※※※\n"
	"    ※※※※　圣贤畜生，一视同仁。　※※※※\n"
	"    ※※※※　　　　　　　　　　　　※※※※\n"
	"    ※※※※　红颜白骨，亦幻一真。　※※※※\n"
	"    ※※※※　　　　　　　　　　　　※※※※\n"
	"    ※※※※　恩怨荣辱，俱在灰尘。　※※※※\n"
	"    ※※※※　　　　　　　　　　　　※※※※\n"
	"    ※※※※※※※※※※※※※※※※※※※※\n";
}

string look_stone()
{
	return
	"\n"
	"    ※※※※※※※※※※※※※※※※※※※※※※\n"
	"    ※※※※　　　　　　　　　　　　　　※※※※\n"
	"    ※※※※　汲井漱寒齿，清心拂尘服。　※※※※\n"
	"    ※※※※　闲持贝叶经，步出东斋读。　※※※※\n"
	"    ※※※※　真源了无取，妄迹世所逐。　※※※※\n"
	"    ※※※※　遗言冀可冥，缮性何由熟？　※※※※\n"
	"    ※※※※　道人庭宇静，苔色连深竹。　※※※※\n"
	"    ※※※※　日出雾露余，青松如膏沐。　※※※※\n"
	"    ※※※※　淡然离言说，悟悦心自足！　※※※※\n"
	"    ※※※※　　　　　　　　　　　　　　※※※※\n"
	"    ※※※※※※※※※※※※※※※※※※※※※※\n";
}

void init()
{
//        add_action("do_say", "say"); tldm,这个地方,gudu说先不开放,呵呵.
}

void close_passage()
{
        object room;
        if( !query("exits/down") ) return;
        message("vision", "佛塔忽然发出轧轧的声音，缓缓地移回原处，"
                "将向下的洞口盖住了。\n", this_object() );
        delete("exits/down");
}

int do_say(string arg)
{
        string dir;
        if( !arg || arg=="" ) return 0;
        if( arg=="恩怨荣辱，俱在灰尘" ) {
                write("只听四周的佛塔，石碑发出隆隆隆的响声，地面猛烈震动起来。\n不大一会儿，一个秘密通道展现在你面前。\n");
                set("exits/down", __DIR__"mishi");
                remove_call_out("close_passage");
                call_out("close_passage", 8);
                return 1;
        }
}
