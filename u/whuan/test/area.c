
/* area.c  这里负责区域物件的载入、清除、重设等工作。 */
#include <area.h>
#include <dbase.h>
#include <ansi.h>

inherit F_DBASE;
inherit F_CLEAN_UP;
inherit F_SAVE;

inherit AREA_MAP;

int query_max_encumbrance() { return 100000000000; }
int query_max_items() {return 30;}
string query_type( int x, int y ) { return area[y][x]["type"]; }
string query_short( int x, int y ) { return area[y][x]["short"]; }
string query_long( int x, int y ) { return area[y][x]["long"]; }
object *query_objects( int x, int y ) { return area[y][x]["loaded"]; }
mapping query_actions( int x, int y ) { return area[y][x]["actions"]; }


// 区域载入的物件集
// Location Of Loaded Objects
// 所有区域载入之物件的座标另成一个集合，以方便快速查找

string *LOLO = ({});

////////////////////////////////////////////////////////////
// 一般设定、检查、查询
////////////////////////////////////////////////////////////
// 传回有载入物件的座标集
string *query_LOLO() { return LOLO; }
// 加入一个座标元素在LOLO集中
void add_LOLO(string location) { if( member_array(location, LOLO) == -1 ) LOLO += ({ location }); }
// 删除一个座标元素在LOLO集中
void del_LOLO(string location) { if( member_array(location, LOLO) != -1 ) LOLO -= ({ location }); }

// 储存区域资料的路径位置
string query_save_file() { return file_name(this_object()); }

// 绝对接受物件移入区域物件
int receive_object(object ob, int from_inventory) { return 1; }
int area_set_type( int x, int y, string type, string icon_type, int color_type );
// 区域检查
int is_area() { return 1; }

// 设定某座标要载入的物件档
int set_loads(int x, int y, string filename, int amount)
{
        if( !check_scope(x, y) ) return 0;
        if( amount <= 0 ) return 0;
        if( undefinedp(area[y][x]["loads"]) )
                area[y][x]["loads"] = ([]);
        area[y][x]["loads"][filename] = amount;
        
        // 加入快速搜寻集
        add_LOLO((string)y+","+(string)x);
        return 1;
}

// 将某座标要载入的物件档移除
int del_loads(int x, int y)
{
        if( !check_scope(x, y) ) return 0;
        if( undefinedp(area[y][x]["loads"]) ) return 1;
        map_delete(area[y][x], "loads");
        
        // 移除快速搜寻集
        del_LOLO((string)y+","+(string)x);
        return 1;
}

// 将某座标的已载入物件移除
int del_loaded(int x, int y)
{
        if( !check_scope(x, y) ) return 0;
        if( undefinedp(area[y][x]["loaded"]) ) return 1;
        map_delete(area[y][x], "loaded");
        return 1;
}

////////////////////////////////////////////////////////////
// 区域里的物件载入、清除
////////////////////////////////////////////////////////////
object make_inventory(string file, int x, int y)
{
    string *exits;
    object ob;

    file = file_path(file);
    ob = new(file);

 // Support for uniqueness
 // if( ob->violate_unique() ) ob = ob->create_replica();
    if( !ob ) return 0;

    ob->set("area_info/x_axis", x);
    ob->set("area_info/y_axis", y);
    ob->set("area_info/x_axis_old", x);
    ob->set("area_info/y_axis_old", y);

    // 将物件移到区域里，并检查是否有guard某方向
        if( move_in(x, y, ob) ) {
                if( (exits=ob->query("guard_exit")) ) {
                        int i = sizeof(exits);
                        while(i--) this_object()->set_area_guard(x, y, exits[i], ob);
                }
            ob->move(this_object());
        }
        else destruct(ob);

    return ob;
}

void reset_callout(int temp)
{
    int i, j, x, y, amount, t=0;
    mapping ob;
        string file;

        if( !sizeof(LOLO) || temp >= sizeof(LOLO) ) return;
        
        for(i=temp;i<sizeof(LOLO);i++) {
        if( sscanf(LOLO[i], "%d,%d", y, x) != 2 ) continue;
        if( !check_scope(x, y) ) continue;
        if( undefinedp(area[y][x]["loads"]) ) continue;
        if( !mapp(ob = area[y][x]["loaded"]) ) ob = ([]);
        if(mapp(area[y][x]["loads"]) && sizeof(area[y][x]["loads"]) > 0  )
        foreach( file, amount in area[y][x]["loads"] ) {
            for(j=amount;j>0;j--) {
                if( objectp(ob[file + " " + j]) ) continue;
                ob[file + " " + j] = make_inventory(file, x, y);
            }
            area[y][x]["loaded"] = ob;
        }
        t++;
        if( t >= 5 ) {
            call_out("reset_callout", 1+random(3), i+1);
            return;
        }
    }
        return;
}

void reset()
{
    int i, amount, x, y;
    mapping ob;
    string file, location;

    // 清空LOO座标集
    LOO = ({});

    // 物件载入集有资料, 递回延迟呼叫产生mob以免cost过多
    call_out("reset_callout", 1, 0);
    return;
}

int clean_up(int inherit_flag)
{
    int i, y, x;
    mapping items;
    string file;
    object ob;

    i = sizeof(LOLO);
    while(i--)
                if( sscanf(LOLO[i], "%d,%d", y, x) == 2 ) {
                if( !mapp(items = query_loaded(x, y)) ) continue;
                foreach(file, ob in items)
                        if( objectp(ob) && ob->is_character() && environment(ob) != this_object() )
                                        return 1;
        }

    return ::clean_up(inherit_flag);
}

// 区域消灭时呼叫此函式
void remove()
{
    int i, y, x, cnt;
    mapping items;
    string file, *objects;
    object ob;

    i = sizeof(LOLO);
        while(i--)
                if( sscanf(LOLO[i], "%d,%d", y, x) == 2 ) {
                        if( !mapp(items = query_loaded(x, y)) ) continue;
                        foreach(file, ob in items) {
                                if( objectp(ob) ) {
                                        message("vision", ob->name() + "化成轻飘飘的白烟消散了。\n", environment(ob));
                                        destruct(ob);
                                        cnt++;
                        }
                }
                // 清空座标物件集，以免往后出错
                map_delete(area[y][x], "objects");
                
        // 清空座标已载入物件之资料，以免往后出错 
        map_delete(area[y][x], "loaded");
    }

    if( cnt && this_player() ) write("警告：" + cnt + " 个NPC由此区域创造并被强制删除。\n");
}

int save()
{
    int i, j, x_size, y_size;
    string *LOO_BAK;
    mapping ICON_BAK;
    mixed *AREA_BAK;
    
        // 存档前将不需要储取的变数清空，以免往后发生无法预期的错误
        LOO_BAK = LOO;
        ICON_BAK = icon;
        AREA_BAK = area;
        
        LOO = ({});
        icon = ([]);
        
        x_size = this_object()->query("x_axis_size");
        y_size = this_object()->query("y_axis_size");
        
    // 每格座标中的暂时变数也要清空
        for(i=0;i<y_size;i++) {
                for(j=0;j<x_size;j++) {
            map_delete(area[i][j], "loaded");
            map_delete(area[i][j], "objects");
        }
    }
        if( ::save() ) {
                LOO = LOO_BAK;
                icon = ICON_BAK;
                area = AREA_BAK;
                return 1;
        }
        
        return 0;
}

void setup()
{
        int i;
        string file;

        seteuid(getuid());

        // 没有储存档
        if( !restore() ) {
        int j, y_size, x_size;

        // 将区域资料变数 area 作初始化
        y_size = this_object()->query("y_axis_size");
        x_size = this_object()->query("x_axis_size");
        if( !y_size || y_size<AREA_YAXIS_MIN || y_size>AREA_YAXIS_MAX ) y_size = DEFAULT_YAXIS_SIZE;
        if( !x_size || x_size<AREA_XAXIS_MIN || x_size>AREA_XAXIS_MAX ) x_size = DEFAULT_XAXIS_SIZE;

        // 要求记忆体
        area = allocate( y_size );
        for(i=0;i<sizeof(area);i++) {
            area[i] = allocate( x_size );
            for(j=0;j<sizeof(area[i]);j++) area[i][j]=([]);
        }
        
        // 清空相关物件集
        LOO = ({});
        LOLO = ({});
        
        // 储存
        save();
        }

    // update 相对路径
    file = base_name(this_object());
    while(i--) if( file[i..i] == "/" ) break;
    set("file_path", file[0..i] );
    this_object()->reset();

}

int load_external_data( string file )
{
        int i=1, j, k=1, n, start, end;
        string str="", unit="";
                        
        if( file_size(file) < 0 ) return 0;
                
        //一共有k行
        while(read_file(file,i,1) != 0 ) {k++;i++;}     
        write("文件一共%d行，现在开始读取。\n",k);
        
        //在这里分配存储党员
        area = allocate(k);
        for(j=0;j<k;j++) 
                area[j]=allocate(200);
                
        //在这里全部填空
   for(i=0;i<k;i++) for(j=0;j<200;j++) area[i][j]=([]);
                        
        for(i=1;i<k;i++) {                      
                reset_eval_cost();
                str = read_file(file,i+1,1);
                printf("读取第%d行...\n",i);
                n=0;
                start=0;
                end=1;
                j=0;
                if(strwidth(str) > 2 )
                while( n < strwidth(str) ) {
                        if( str[n..n+1] == "  ") {
                                area[i-1][j]["icon"] = str[start..n+1]+NOR;
                                if(area[i-1][j]["icon"] == "◣" || area[i-1][j]["icon"] == "◢" )
                                        area_set_type( i-1, j, "mountain", "none", -1 );
                                else area_set_type( i-1, j, "wild", "none", -1 );
                                start = n+2;
                                n+=2;
                                j++;
                        } else if( str[n..n+1] == "　") {
                                area[i-1][j]["icon"] = str[start..n+1]+NOR;
                                if(area[i-1][j]["icon"] == "◣" || area[i-1][j]["icon"] == "◢" )
                                area_set_type( i-1, j, "mountain", "none", -1 );
                                else area_set_type( i-1, j, "wild", "none", -1 );
                                start = n+2;
                                n+=2;
                                j++;
                        } else if(is_chinese(str[n..n+1]) ){
                                area[i-1][j]["icon"] = str[start..n+1]+NOR;
                                if(area[i-1][j]["icon"] == "◣" || area[i-1][j]["icon"] == "◢" )
                                        area_set_type( i-1, j, "mountain", "none", -1 );
                                else area_set_type( i-1, j, "wild", "none", -1 );
                                start = n+2;
                                n+=2;
                                j++;
                        } else  {
                                if( str[n..n+1] == " && n > 2 ) {
                                        reset_eval_cost();
                                        if( str[n-1..n-1] != "m" ) {
                                                end=n-1;
                                                if( start + 2 <= end ) {
                                                if( str[n-2..n-2] == "m" )
                                                        area[i-1][j]["icon"] = str[start..end]+" "+NOR;
                                                else area[i-1][j]["icon"] = str[start..end]+NOR;
                                                if(area[i-1][j]["icon"] == "◣" || area[i-1][j]["icon"] == "◢" )
                                                area_set_type( i-1, j, "mountain", "none", -1 );
                                                else area_set_type( i-1, j, "wild", "none", -1 );
                                                start=n;
                                                j++;
                                                }                       
                                        }                               
                                }
                                n++;
                        }
                        
                }
                printf("共%d个双字元\n",(sizeof(str)-1)/2);
        }
        save();
        return 1;
}

//types1 面积型区域，types2点型区域
/*
        地理类型 : ([ 
           icon : ({字符图标集}), // string *
           owner:  拥有者国家,  // string 
           ratio: 10, //此数用千分之一来除就是载入objects 的概率, int 
           loads : 可能载入的物件, mapping
           block: 可否通过,  int
           no_fight : 是否安全区, int 
           short : ({短描述集}),  string *
           actions : ([动作指令集:动作相关函数集 ]), mapping
        ])
*/

int area_set_type( int x, int y, string type, string icon_type, int color_type )
{
        string *allkeys, *skey;
        int i;
        mapping all;
        mapping types1 = ([
                "wild":([
                        "icon"  : ({"．",}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["/d/city/npc/bing":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"荒野","荒芜之地"}),
                        "actions" : (["dig":"/cmds/area/dig.c","own":"/cmds/area/own.c",]),                                 
                ]),
                "street": ([
                        "icon"  : ({"\x1B[46m※\x1B[0;2m"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"大街","马路","青砖路"}),
                        "actions" : (["":""]),
                ]),
                "inner": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"室内","厅","房"}),
                        "actions" : (["":""]),
                ]),
                "wall": ([
                        "icon"  : ({"╗","║","╝","═","╚","╔"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 1,
                        "no_fight" : 0,
                        "short" : ({"高墙","墙"}),
                        "actions" : (["":""]),
                ]),                             
                "bank": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"钱庄","票号"}),
                        "actions" : (["":""]),
                ]),                             
                "herb": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"药材店","大夫堂"}),
                        "actions" : (["":""]),
                ]),                             
                "misc": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"小店","杂货铺","杂货店"}),
                        "actions" : (["":""]),
                ]),                             
                "factory": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"作坊","手工作坊"}),
                        "actions" : (["":""]),
                ]),                             
                "miner": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"矿井","矿厂"}),
                        "actions" : (["":""]),
                ]),                             
                "tavern": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 1,
                        "short" : ({"客栈","酒家"}),
                        "actions" : (["":""]),
                ]),
                        "temple": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 1,
                        "short" : ({"寺庙","庙"}),
                        "actions" : (["":""]),
                ]),
                "school": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 1,
                        "short" : ({"私塾","学校"}),
                        "actions" : (["":""]),
                ]),
                "stable": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"马房","马厩"}),
                        "actions" : (["":""]),
                ]),
                "ware": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 1,
                        "short" : ({"仓库"}),
                        "actions" : (["":""]),
                ]),
                "mart": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 1,
                        "short" : ({"市场","集市","大集"}),
                        "actions" : (["":""]),
                ]),
                "smith": ([
                        "icon"  : ({"口"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"铁匠铺","打铁铺"}),
                        "actions" : (["":""]),
                ]),
                "pool": ([
                        "icon"  : ({"～"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"水池","池塘","大泡子"}),
                        "actions" : (["":""]),
                         ]),                        
                "plain": ([
                        "icon"  : ({"　",}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"平原","开阔地"}),
                        "actions" : (["":""]),
                ]),
                "water": ([
                        "icon"  : ({"～"}),
                        "owner" : "sys",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"河流","大江"}),
                        "actions" : (["":""]),
                ]),
                           
                "sea": ([
                        "icon"  : ({"~~"}),
                        "owner" : "sys",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"大海","大洋"}),
                        "actions" : (["":""]),
                ]),
                
                "square": ([
                        "icon"  : ({"　"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"广场","十字街头","场"}),
                        "actions" : (["":""]),
                ]),
                "mountain": ([
                        "icon"  : ({"◣","◢"}),
                        "owner" : "sys",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 1,
                        "no_fight" : 0,
                        "short" : ({"大山","高山"}),
                        "actions" : (["":""]),
                ]),
                           
                "bridge": ([
                        "icon"  : ({"＃"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"桥","大桥"}),
                        "actions" : (["":""]),
                ]),                       
                "grass": ([
                        "icon"  : ({"〃"}),
                        "owner" : "none",
                        "ratio" : 10,
                        "loads" : (["":1]),
                        "block" : 0,
                        "no_fight" : 0,
                        "short" : ({"草地","青草地"}),
                        "actions" : (["":""]),
                ]),
        ]);
        //门树木桩关卡船井洞物品
        mapping types2 = ([
        "door": ([
                "icon"  : ({"::"}),
                "owner" : "none",
                "ratio" : 10,
                "loads" : (["":1]),
                "block" : 1,
                "no_fight" : 1,
                "short" : ({"门","大门"}),
                "actions" : (["":""]),
        ]),
        "tree": ([
                "icon"  : ({"木"}),
                "owner" : "none",
                "ratio" : 10,
                "loads" : (["":1]),
                "block" : 1,
                "no_fight" : 1,
                "short" : ({"树","大树","小树"}),
                "actions" : (["":""]),
        ]),
         "pillar": ([
                "icon"  : ({"柱"}),
                "owner" : "none",
                "ratio" : 10,
                "loads" : (["":1]),
                "block" : 1,
                "no_fight" : 1,
                "short" : ({"木桩","桩子"}),
                "actions" : (["":""]),
         ]),
        "fort": ([
                "icon"  : ({"停"}),
                "owner" : "none",
                "ratio" : 10,
                "loads" : (["":1]),
                "block" : 0,
                "no_fight" : 0,
                "short" : ({"关卡","岗哨"}),
                "actions" : (["":""]),
        ]),
        "boat": ([
                "icon"  : ({"船"}),
                "owner" : "none",
                "ratio" : 10,
                "loads" : (["":1]),
                "block" : 0,
                "no_fight" : 0,
                "short" : ({"船","木船","小船"}),
                "actions" : (["":""]),
        ]),
        "well": ([
                "icon"  : ({"井"}),
                "owner" : "none",
                "ratio" : 10,
                "loads" : (["":1]),
                "block" : 0,
                "no_fight" : 0,
                "short" : ({"井","水井"}),
                "actions" : (["":""]),
        ]),
        "cave": ([
                "icon"  : ({"洞"}),
                "owner" : "none",
                "ratio" : 10,
                "loads" : (["":1]),
                "block" : 0,
                "no_fight" : 0,
                "short" : ({"洞","深洞"}),
                "actions" : (["":""]),
                ]),                       
        ]);  
        
        all = types1+types2;
        allkeys = keys(all);
        skey = keys(all[type]);
        
        if( member_array(type, allkeys) == -1 )
                return notify_fail("类型错误!\n");
        if( !check_scope(x, y) ) 
                return notify_fail("不在地图范围内。\n");
                
        if( icon_type == "none" || !icon_type ) icon_type = all[type]["icon"][random(sizeof(all[type]["icon"]))];
        
        if( color_type > 0 && color_type < 31 ) {
          if( color_type == 1 ) icon_type = BBLU+HIG+icon_type+NOR;
                if( color_type == 2 ) icon_type = BBLU+HIY+icon_type+NOR;
                if( color_type == 3 ) icon_type = BBLU+HIR+icon_type+NOR;
                if( color_type == 4 ) icon_type = BBLU+HIM+icon_type+NOR;
                if( color_type == 5 ) icon_type = BGRN+HIC+icon_type+NOR;
                if( color_type == 6 ) icon_type = BGRN+HIB+icon_type+NOR;
                if( color_type == 7 ) icon_type = BGRN+HIY+icon_type+NOR;
                if( color_type == 8 ) icon_type = BGRN+HIR+icon_type+NOR;
                if( color_type == 9 ) icon_type = BGRN+HIM+icon_type+NOR;
                if( color_type == 10 ) icon_type = BGRN+HIC+icon_type+NOR;              
                if( color_type == 11 ) icon_type = BRED+HIG+icon_type+NOR;
                if( color_type == 12 ) icon_type = BRED+HIY+icon_type+NOR;
                if( color_type == 13 ) icon_type = BRED+HIG+icon_type+NOR;
                if( color_type == 14 ) icon_type = BRED+HIM+icon_type+NOR;
                if( color_type == 15 ) icon_type = BRED+HIC+icon_type+NOR;
                if( color_type == 16 ) icon_type = BYEL+HIB+icon_type+NOR;
                if( color_type == 17 ) icon_type = BYEL+HIG+icon_type+NOR;
                if( color_type == 18 ) icon_type = BYEL+HIR+icon_type+NOR;
                if( color_type == 19 ) icon_type = BYEL+HIM+icon_type+NOR;
                if( color_type == 20 ) icon_type = BYEL+HIC+icon_type+NOR;                      
                if( color_type == 21 ) icon_type = BMAG+HIG+icon_type+NOR;
                if( color_type == 22 ) icon_type = BMAG+HIY+icon_type+NOR;
                if( color_type == 23 ) icon_type = BMAG+HIG+icon_type+NOR;
           if( color_type == 24 ) icon_type = BMAG+HIR+icon_type+NOR;
                if( color_type == 25 ) icon_type = BMAG+HIC+icon_type+NOR;
                if( color_type == 26 ) icon_type = BCYN+HIB+icon_type+NOR;
                if( color_type == 27 ) icon_type = BCYN+HIG+icon_type+NOR;
                if( color_type == 28 ) icon_type = BCYN+HIR+icon_type+NOR;
                if( color_type == 29 ) icon_type = BCYN+HIM+icon_type+NOR;
                if( color_type == 30 ) icon_type = BCYN+HIY+icon_type+NOR;
                                
        }
        area[y][x]["type"] = type;
        area[y][x]["icon"]= icon_type;  
        area[y][x]["short"] = all[type]["short"][random(sizeof(all[type]["short"]))];
        area[y][x]["loads"] = all[type]["loads"][random(sizeof(all[type]["loads"]))];
        area[y][x]["block"] = all[type]["block"];
        area[y][x]["no_fight"] = all[type]["no_fight"];
        area[y][x]["owner"] = all[type]["owner"]; 
        area[y][x]["actions"] = all[type]["actions"]; 
        return 1;
        
}


/*
mapping color_icon = ({ 
                BBLU+HIG+"icon"+NOR,  //蓝底高亮绿
                BYEL+HIR+"icon"+NOR,  //黄底高亮红
                BBLU+HIR+"icon"+NOR,  //蓝底高亮红
                BBLU+HIY+"icon"+NOR,  //蓝底高亮黄
                BBLU+HIM+"icon"+NOR,  //蓝底高亮粉
                BBLU+HIC+"icon"+NOR,  //蓝底高亮青
                BBLU+HIW+"icon"+NOR,  //蓝底高亮白
        });
*/
