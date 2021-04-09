/* map.c  这里负责地图的显示、物件的移动以及一些设定等等。
*/
#include <area.h>
#include <ansi.h>
#include <dbase.h>

inherit "/u/whuan/test/prompt_icon.c";

// 区域座标资料(座标物件、图样...)
mixed *area;

// Location Of Objects
// 所有存在物件的座标另成一个集合，以方便快速查找
string *LOO = ({});

// 不能用一般设定方法的项目 (区域形式的出口，要用特别的方式设定)
string *set_data_resist = ({ "objects", "loaded", "loads", "area_exit" });

// 不能用一般删除方法的项目 (可能是区域管理用的项目或其它特别的项目)
string *delete_data_resist = ({ "objects", "loaded", "loads" });

string *get_hp();


varargs int do_look(object me, string arg);

////////////////////////////////////////////////////////////
// 一般设定、检查、查询
////////////////////////////////////////////////////////////
// 传回有物件存在的座标集
string *query_LOO() { return LOO; }
// 加入一个座标元素在LOO集中
void add_LOO(string location) { if( member_array(location, LOO) == -1 ) LOO += ({ location }); }
// 删除一个座标元素在LOO集中
void del_LOO(string location) { if( member_array(location, LOO) != -1 ) LOO -= ({ location }); }

// 使用__DIR__之相对路径
string file_path(string dir) { 
    dir = replace_string(dir, "__DIR__", query("file_path") );
    dir = replace_string(dir, "_DIR_AREA_", _DIR_AREA_);
    dir = replace_string(dir, "_DIR_NPC_", _DIR_NPC_);
    dir = replace_string(dir, "_DIR_WP_", _DIR_WP_);
    dir = replace_string(dir, "_DIR_EQ_", _DIR_EQ_);
    dir = replace_string(dir, "_DIR_ITEM_", _DIR_ITEM_);
    dir = replace_string(dir, "_DIR_WORLD_", _DIR_WORLD_);
    return dir;
}



string chinese_daoxing(int gain) 
{
        int year,day,hour;
        string str;
        
        year=gain/1000;
        day=(gain-year*1000)/4;
        hour=(gain-year*1000-day*4)*3;
        
        str="";
        if(year) str=str+CHINESE_D->chinese_number(year)+"年";
        if(day) str=str+CHINESE_D->chinese_number(day)+"天";
        if(hour) str=str+CHINESE_D->chinese_number(hour)+"时辰";
        if(gain==0) str="未入道途";
                
        return str;
}

string status_color(int current, int max)
{
        int percent;
        if( max>0 ) percent = current * 100 / max;

        else percent = 100;
        if( percent > 100 ) return HIC;
        if( percent >= 90 ) return HIG;
        if( percent >= 60 ) return HIY;
        if( percent >= 30 ) return CYN;
        if( percent >= 10 ) return HIR;
        return RED;
}

// 座标范围检查
int check_scope(int x, int y)
{
    if( y < 0 || x < 0 || y >= sizeof(area) || x >= sizeof(area[y]) ) 
        return 0;
    return 1;
}

// 查询某座标的资讯
mapping *query_info(int x, int y)
{
    if( !check_scope(x, y) ) return 0;
    return area[y][x];
}



// 查询某座标载入的物件
mapping query_loaded(int x, int y)
{
    if( !check_scope(x, y) ) return ([]);
    return area[y][x]["loaded"];
}

// 查询区域中某座标的物件集
mapping *query_inventory(int x, int y)
{
    if( !check_scope(x, y) ) return ({});
    if( undefinedp(area[y][x]["objects"]) ) return ({});
    return area[y][x]["objects"];
}

// 设定区域型出口
int set_area_exit(int x, int y, string filename, int exit_x, int exit_y)
{
    if( !check_scope(x, y) ) return 0;
    area[y][x]["area_exit"] = ([]);
    area[y][x]["area_exit"]["filename"] = filename;
    area[y][x]["area_exit"]["x_axis"] = exit_x;


    area[y][x]["area_exit"]["y_axis"] = exit_y;
    return 1;
}

// 设定区域细节描述
int set_area_detail(int x, int y, string title, string detail)
{
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x]["detail"]) ) area[y][x]["detail"] = ([]);
    area[y][x]["detail"][title] = detail;
    return 1;
}

// 删除区域细节描述
int del_area_detail(int x, int y, string title)
{
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x]["detail"]) ) return 1;

    map_delete(area[y][x]["detail"], title);

    if( sizeof(area[y][x]["detail"]) < 1 )
        map_delete(area[y][x], "detail");


    return 1;
}

// 取得区域细节资料
mapping query_area_detail(int x, int y)
{
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x]["detail"]) ) return ([]);
    return area[y][x]["detail"];
}

// 取得某detail的描述
string query_area_detail_arug(int x, int y, string title)
{
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x]["detail"]) ) return 0;
    if( undefinedp(area[y][x]["detail"][title]) ) return 0;
    return area[y][x]["detail"][title];
}

// 设定某方向的guard
int set_area_guard(int x, int y, string exit, object ob)
{


    if( !check_scope(x, y) ) return 0;
    if( !objectp(ob) ) return 0;
    if( undefinedp(area[y][x]["guard"]) ) area[y][x]["guard"] = ([]);
    if( undefinedp(area[y][x]["guard"][exit]) ) area[y][x]["guard"][exit] = ({});
    area[y][x]["guard"][exit] += ({ ob });
    return 1;
}

// 查询某方向是否被guard
int query_area_guard(int x, int y, string exit)
{
    int index;
    object guard;
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x]["guard"]) ) return 0;
    if( undefinedp(area[y][x]["guard"][exit]) ) return 0;
    if( !(index=sizeof(area[y][x]["guard"][exit])) ) return 0;
    while(index--) {
        if( objectp(guard=area[y][x]["guard"][exit][index]) ) {
                if( guard->query("area_info/x_axis") == x && guard->query("area_info/y_axis") == y ) {
                        guard->do_guard_exit(x, y, exit);
                    return 1;
                }


        }
    }
    return 0;
}

// 设定一般资料
int set_data(int x, int y, string type, mixed value)
{
    if( member_array(type, set_data_resist) != -1 ) return 0;
    if( !check_scope(x, y) ) return 0;
    area[y][x][type] = value;
    return 1;
}

// 删除一般资料
int delete_data(int x, int y, string type)
{
    if( member_array(type, delete_data_resist) != -1 ) return 0;
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x][type]) ) return 1;
    map_delete(area[y][x], type);
    return 1;
}



// 取得一般资料
mixed query_data(int x, int y, string type)
{
    if( member_array(type, delete_data_resist) != -1 ) return 0;
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x][type]) ) return 0;
    return area[y][x][type];
}

////////////////////////////////////////////////////////////
// 移动
////////////////////////////////////////////////////////////

// 检查某座标是否有障碍物，是否可穿透
int is_move(int x, int y)
{
    // 如果巫师设定为穿墙模式
    if( wizardp(this_player()) && this_player()->query("option/map_through") ) return 1;
    if( undefinedp(area[y][x]["block"]) ) return 1;
    if( !area[y][x]["block"] ) return 1;
    return 0;
}



// 物件移入某座标处理
int move_in(int x, int y, object ob)
{
    // 超出区域大小范围
    if( !check_scope(x, y) ) return 0;

    // 该座标没有物件集(objects)，则将物件集设为空
    if( undefinedp(area[y][x]["objects"]) ) area[y][x]["objects"] = ({});

    // 一格最多容纳30个物件
    if( sizeof(area[y][x]["objects"]) >= 30 ) {
        write("那个方向太多东西了。\n");
        return 0;
    }

    // 物件已经存在物件集(objects)中，就不需要再加入物件集
    if( member_array( ob, area[y][x]["objects"] ) != -1 ) return 1;

    // 物件加入物件集中
    area[y][x]["objects"] += ({ ob });
    
    // 改变即时的图示


    set_icon_weight(x, y, get_icon_weight(ob));

    // 增加LOO搜寻集
    add_LOO((string)y + "," + (string)x);

    return 1;
}

// 物件移出某座标处理
int move_out(int x, int y, object ob)
{
    // 超出区域大小范围
    if( !check_scope(x, y) ) return 0;

    // 该座标没有物件集(objects)
    if( undefinedp(area[y][x]["objects"]) ) return 1;

    // 改变即时的图示
    set_icon_weight(x, y, -get_icon_weight(ob));

    // 物件不存在于物件集(objects)中，就不需要再移出物件集
    if( member_array( ob, area[y][x]["objects"] ) == -1 ) return 1;



    // 物件移出物件集
    area[y][x]["objects"] -= ({ ob });
     
    // 座标完全没物件时，删除物件集
    if( sizeof(area[y][x]["objects"]) < 1 ) {
        map_delete(area[y][x], "objects");
        // 删除LOO搜寻集
        del_LOO((string)y + "," + (string)x);
    }

    return 1;
}

// 进行移动
// 物件是否合法的在区域中移动
int valid_leave(object ob, string dir)
{
    int x, y, x_past, y_past;
    x_past = ob->query("area_info/x_axis");
    y_past = ob->query("area_info/y_axis");
    
    // 座标转换
    switch( dir ) {


        case     "north":  y = y_past-1; x = x_past;   break;
        case      "east":  y = y_past;   x = x_past+1; break;
        case     "south":  y = y_past+1; x = x_past;   break;
        case      "west":  y = y_past;   x = x_past-1; break;
        case "northeast":  y = y_past-1; x = x_past+1; break;
        case "southeast":  y = y_past+1; x = x_past+1; break;
        case "southwest":  y = y_past+1; x = x_past-1; break;
        case "northwest":  y = y_past-1; x = x_past-1; break;
        default: return 0; break;
    }
    
    // 无法移动至该座标(有障碍物)
    if( !check_scope(x, y) || !is_move(x, y) ) {
        write("这个方向没有出路");
        return 0;
    }

    // 无法往某方向移动因为被某人guard
    if( query_area_guard(x_past, y_past, dir) ) return 0;
        
    //////////////////////////////
    // 移往别的房间
    //////////////////////////////


    if( !undefinedp(area[y][x]["room_exit"]) ) {
        object room;
        if( !objectp(room = load_object(file_path(area[y][x]["room_exit"]))) ) {
            write("这个方向的出口有问题，请通知管理者来处理。\n");
            return 0;
        }
        if( room->is_area() ) {
            write("这个方向的出口有问题，请通知管理者来处理。\n");
            return 0;
        } else {
                // 如果成功移到房间, move 会自动在先前的area里做move_out动作
            if( ob->move(room) ) return 1;
            else {
                write("这个方向的出口有问题，请通知管理者来处理。\n");
                return 0;
            }
        }
        return 0;
    }

    //////////////////////////////
    // 移往别的区域
    //////////////////////////////


    if( !undefinedp(area[y][x]["area_exit"]) ) {
        object room;
        if( !objectp(room = load_object(file_path(area[y][x]["area_exit"]["filename"]))) ) {
            write("这个方向的出口有问题，请通知管理者来处理。\n");
            return 0;
        }
        if( !room->is_area() ) {
            write("这个方向的出口有问题，请通知管理者来处理。\n");
            return 0;
        }

        if( !area_move(room, ob, area[y][x]["area_exit"]["x_axis"], area[y][x]["area_exit"]["y_axis"]) ) {
                write("这个方向的出口有问题，请通知管理者来处理。\n");
                return 0;
        }
        return 1;
    }

    //////////////////////////////
    // 在区域中移动 
    //////////////////////////////
    // 物件移出旧座标
    if( move_out(x_past, y_past, ob) ) {


        // 物件移入新座标
        if( move_in(x, y, ob) ) {
            ob->set("area_info/x_axis", x);
            ob->set("area_info/y_axis", y);
            ob->set("area_info/x_axis_old", x);
            ob->set("area_info/y_axis_old", y);
        } else { 
            // 物件移入失败，退回原座标
            move_in(x_past, y_past, ob);
            return 0;
        }
        if( userp(ob) ) do_look(ob, 0);
    } else return 0;

    return 1;
}



////////////////////////////////////////////////////////////
// 检视区域环境
////////////////////////////////////////////////////////////



// 查询某坐标的出口
string *query_exits(int x, int y, int option)
{
    string *exits=({});

    if( !option ) {
        // 往北可能有路
        if( y-1 >= 0 ) {
            if( x-1 >= 0 && is_move(x-1, y-1) ) exits += ({ "northwest" });
            if( x >= 0 && is_move(x, y-1) ) exits += ({ "north" });
            if( x+1 < sizeof(area[0]) && is_move(x+1, y-1) ) exits += ({ "northeast" });
        }

        // 往南可能有路
        if( y+1 < sizeof(area) ) {
            if( x-1 >= 0 && is_move(x-1, y+1) ) exits += ({ "southwest" });
            if( x >= 0 && is_move(x, y+1) ) exits += ({ "south" });
            if( x+1 < sizeof(area[0]) && is_move(x+1, y+1) ) exits += ({ "southeast" });
        }

        // 往东可能有路
        if( x+1 < sizeof(area[0]) && is_move(x+1, y) ) exits += ({ "east" });
    


        // 往西可能有路
        if( x-1 >= 0 && is_move(x-1, y) ) exits += ({ "west" });
    } else {
        // 往北可能有路
        if( y-1 >= 0 ) {
            if( x-1 >= 0 && is_move(x-1, y-1) ) exits += ({ "西北("HIK"nw"NOR")" });
            if( x >= 0 && is_move(x, y-1) ) exits += ({ "北("HIK"n"NOR")" });
            if( x+1 < sizeof(area[0]) && is_move(x+1, y-1) ) exits += ({ "东北("HIK"ne"NOR")" });
        }

        // 往南可能有路
        if( y+1 < sizeof(area) ) {
            if( x-1 >= 0 && is_move(x-1, y+1) ) exits += ({ "西南("HIK"sw"NOR")" });
            if( x >= 0 && is_move(x, y+1) ) exits += ({ "南("HIK"s"NOR")" });
            if( x+1 < sizeof(area[0]) && is_move(x+1, y+1) ) exits += ({ "东南("HIK"se"NOR")" });
        }

        // 往东可能有路
        if( x+1 < sizeof(area[0]) && is_move(x+1, y) ) exits += ({ "东("HIK"e"NOR")" });
    
        // 往西可能有路
        if( x-1 >= 0 && is_move(x-1, y) ) exits += ({ "西("HIK"w"NOR")" });
    }


    return exits;
}

// 地图显示
varargs string show_area(int x, int y, int type)
{
    int i, j, x_start, y_start, x_size, y_size;
    string msg, *hpstr;

    // 决定显示地图的Y轴起点, X轴起点
    y_size = sizeof(area);
    x_size = sizeof(area[0]);

    if( y <= 5 || y_size <= 11 ) y_start = 0;
    else if( y >= y_size-6 ) y_start = y_size-11;
    else y_start = y-5;

    if( x <= 9 || x_size <= 19 ) x_start = 0;
    else if( x >= x_size-9 ) x_start = x_size-19;
    else x_start = x-9;
        
    hpstr = get_hp();



    // 建立即时地图
    msg = sprintf(BBLU"╲"LINE" %-21s %s (%2d,%2d) "NOR+BBLU"╱"NOR,
            query("name") + (area[y][x]["short"] ? " - " + area[y][x]["short"] : ""),
            (area[y][x]["no_fight"] ? "非战区" : "战斗区"), x, y, )+hpstr[0];
    
    for(i=y_start;i<y_size && i<y_start+11;i++) {
        msg += BBLU"▕"NOR;
        for(j=x_start;j<x_size && j<x_start+19;j++) {
            if( y == i && x == j ) msg += HIY+"㊣"NOR;
            else if( undefinedp(area[i][j]["icon"]) && 
                    (!undefinedp(area[i][j]["room_exit"]) || !undefinedp(area[i][j]["area_exit"])) )
                        msg += HIW"。"NOR;
            else {
                int check=1;
                if( check && (type & 2) == 2 ) {
                    // 座标有设不即时变更图示
                    if( !area[i][j]["nonprompt_icon"] && check_icon(j, i) ) {
                        msg += get_icon(j, i);
                        check = 0;
                    }
                }
                if( check && (type & 4) == 4 ) {
                    if( area[i][j]["block"] ) {


                        msg += "■";
                    } else msg += "  ";
                    check = 0;     // 图形已设定则归零
                }
                // 图形未定
                if( check ) msg += area[i][j]["icon"] ? area[i][j]["icon"] : "  ";
            }
        }
        msg += BBLU"▏"NOR;
        msg += hpstr[i-y_start+1];        
    }
    msg += BBLU"╱￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣╲"NOR;
    msg += hpstr[12];
    
    if( (type & 1) == 1 ) return msg;
    else { return SAVEC+HOME+msg+RESTC; }
}

varargs string show_objects(int x, int y, int type)
{
    string str = "";
    object ob;
    


    if( undefinedp(area[y][x]["objects"]) ) return "";

    foreach(ob in area[y][x]["objects"]) {
        if( ob == this_player() ) continue;
        if( !objectp(ob) || environment(ob) != this_object() ||
            ob->query("area_info/y_axis") != y || ob->query("area_info/x_axis") != x ) {
                area[y][x]["objects"] -= ({ ob });
                continue;
        }
        str += sprintf("  %s\n", ob->short() );
    } 
    return str;
}

varargs int do_look(object me, string arg)
{
    int i=0, op=0;
    string str="", *exits;
    mapping info, option;

    if( !userp(me) ) return 0;

    info = me->query("area_info");


    option = me->query("option");

    if( !info ) 
        return notify_fail("没有设置 area_info, 请联系wiz。\n");
    if( !option ) option = ([]);
    if( !check_scope(info["x_axis"], info["y_axis"]) ) 
        return notify_fail("进入区域超出area边界，请联系wiz。\n");

    if( arg ) {
        if( (str = query_area_detail_arug(info["x_axis"], info["y_axis"], arg)) )
            message("vision", str + "\n", me);
        else return notify_fail("你要看什么？\n");
        return 1;
    }

    // 是否取消冻结即时地图
    if( option["map_unfreeze"] ) op = op | 1;

    // 显示即时图形变换
    if( !option["map_obj_icon_hidden"] ) op = op | 2;

    // 将原本的地图图形变换成二种 有障碍物 与 没障碍物
    if( option["map_block"] ) op = op | 4;



    // 显示地图
    if( !option["map_hidden"] ) str += show_area(info["x_axis"], info["y_axis"], op);
    
    // 出口提示
    exits = query_exits(info["x_axis"], info["y_axis"], 1);
    
    str += "地理信息：";
    
    str += uncolor(query("name"));
    
    if(area[info["y_axis"]][info["x_axis"]]["short"])
        str += "->"+area[info["y_axis"]][info["x_axis"]]["short"];   
        
    if(area[info["y_axis"]][info["x_axis"]]["type"])
        str += "->"+area[info["y_axis"]][info["x_axis"]]["type"]+"\n";
    else str += "->类型未知\n";
    
    if( (i = sizeof(exits)) ) {
        str += "道路出口: ";
        while( i-- ) str += exits[i] + ( i ? "、" : "。\n" );
    } else str += "这里没有任何出口。\n";
    


    // 显示物件
    if( !option["map_obj_hidden"] ) str += show_objects(info["x_axis"], info["y_axis"], 0);
        
    message("vision", str, me);

    return 1;
}

varargs int map_ansi_save()
{
    int i, j, x, y;
    string file, msg="", msg2="";

    y = sizeof(area);
    x = sizeof(area[0]);

    file = base_name(this_object());

    for(i=0;i<y;i++) {
        for(j=0;j<x;j++) {
                if( j <= 49 ) {
                    if( undefinedp(area[i][j]["icon"]) ) msg += "  ";
                else msg += area[i][j]["icon"];


            } else {
                    if( undefinedp(area[i][j]["icon"]) ) msg2 += "  ";
                else msg2 += area[i][j]["icon"];
            }
        }
        msg += "\n";
        if( x > 49 ) msg2 += "\n";
    }
    
    if( x <= 49 ) {
            if( !write_file(file + ".ansi" , msg, 1) ) write("储存ANSI档失败。\n");
        else write("储存ANSI档成功(" + file + ".ansi)。\n");
    } else {
        write("因为此area宽度超过五十个字大小，故分成左右二个图档储存。\n");
            if( !write_file(file + "_left.ansi" , msg, 1) ) write("储存左半边ANSI档失败。\n");
        else write("储存左半边ANSI档成功(" + file + "_left.ansi)。\n");
            if( !write_file(file + "_right.ansi" , msg2, 1) ) write("储存右半边ANSI档失败。\n");
        else write("储存右半边ANSI档成功(" + file + "_right.ansi)。\n");
    }
    
    return 1;
}



varargs int map_html_save()
{
    int i, j, x, y;
    string file, msg="", tmp;

    y = sizeof(area);
    x = sizeof(area[0]);

    file = base_name(this_object());

    msg += "<html>\n";
    msg += "<head>\n";
    msg += "<title>" + this_object()->query("name") + "</title>\n";
    msg += "</head>\n";
    msg += "<body bgcolor=000000><font size=2 face=细明体>\n";
    for(i=0;i<y;i++) {
        for(j=0;j<x;j++) {
            if( undefinedp(area[i][j]["icon"]) ) msg += "　";
                else {
                        tmp = replace_string(area[i][j]["icon"], "  ", "　");
                    msg += color_to_html(tmp);
                    msg += "</span>";
                }


        }
        msg += "\n<br>";
    }
    msg += "</font></body>\n</html>";

    if( !write_file(file + ".html" , msg, 1) )
        write("储存HTML档失败。\n");

    write("储存HTML档成功。\n");

    return 1;
}
 
 /*取得 ob 的hp 数据描述*/
        
string *get_hp()
{
        string *hpstr, str;
        object ob = this_player();
        mapping my = ob->query_entire_dbase();
        int dao, x, i;  
        hpstr = allocate(13);
        


        hpstr[0]= sprintf(NOR CYN"┏━━━━━━━━━━━━━━"HIY"X"HIR"·"HIY"L"HIR"·"HIY"Q"HIR"·"HIY"Y"NOR CYN"━━━━━━━━━━━━━━┓\n"NOR,);
        hpstr[1]= sprintf(NOR CYN"┃"NOR WHT" 个人状态"NOR CYN" 姓 名："NOR WHT"%-12s "NOR CYN" 性别："NOR WHT"%-10s "NOR CYN"I D："NOR WHT"%-13s"NOR CYN"┃\n"NOR,ob->name(),ob->query("gender"),"["+capitalize(ob->query("id"))+"]");
        hpstr[2]= sprintf(NOR CYN"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n"NOR);
        hpstr[3]= sprintf(NOR CYN"┃"NOR WHT"〖 气血 〗%s%7-d/%8-d%s[%3d%%]"NOR,status_color(to_int(my["kee"]),to_int(my["eff_kee"])),to_int(my["kee"]),to_int(my["eff_kee"]),status_color(to_int(my["eff_kee"]),to_int(my["max_kee"])),to_int(my["eff_kee"])*100/to_int(my["max_kee"]))+sprintf(NOR WHT"  〖 内力 〗%s%7-d/%7-d(+%4d)"NOR CYN"┃\n"NOR,status_color(to_int(my["force"]),to_int( my["max_force"])), to_int(my["force"]), to_int(my["max_force"]),to_int(my["force_factor"]));
        hpstr[4]= sprintf(NOR CYN"┃"NOR WHT"〖 心神 〗%s%7-d/%8-d%s[%3d%%]"NOR,status_color(to_int(my["sen"]),to_int(my["eff_sen"])),to_int(my["sen"]),to_int(my["eff_sen"]),status_color(to_int(my["eff_sen"]),to_int(my["max_sen"])),to_int(my["eff_sen"])*100/to_int(my["max_sen"]))+sprintf(NOR WHT"  〖 法力 〗%s%7-d/%7-d(+%4d)"NOR CYN"┃\n"NOR,status_color(to_int(my["mana"]), to_int(my["max_mana"])), to_int(my["mana"]), to_int(my["max_mana"]),my["mana_factor"]);
                
        if(my["food"]*100/ob->max_food_capacity()>100) str=HIC+"很饱";
        else if(my["food"]*100/ob->max_food_capacity()>90) str=HIG+"正常";
        else if(my["food"]*100/ob->max_food_capacity()>60) str=HIY+"缺食";        
                else if(my["food"]*100/ob->max_food_capacity()>30) str=CYN+"缺食";
        else if(my["food"]*100/ob->max_food_capacity()>10) str=HIR+"缺食";
        else str=RED+"饥饿";
        
        hpstr[5]= sprintf(NOR CYN"┃"NOR WHT"〖 食物 〗%s%7-d/%7-d [%4s%s]"NOR,status_color(my["food"], ob->max_food_capacity()), my["food"], ob->max_food_capacity(),str,status_color(my["food"], ob->max_food_capacity())) + sprintf(NOR WHT"  〖 武学 〗%s%18-d    "NOR CYN"┃\n"HIG,HIY,(int)ob->query("combat_exp"));
        
        if(my["water"]*100/ob->max_water_capacity()>100) str=HIC+"很饱";
        else if(my["water"]*100/ob->max_water_capacity()>90) str=HIG+"正常";
        else if(my["water"]*100/ob->max_water_capacity()>60) str=HIY+"缺水";
        else if(my["water"]*100/ob->max_water_capacity()>30) str=CYN+"缺水";
        else if(my["water"]*100/ob->max_water_capacity()>10) str=HIR+"缺水";
        else str=RED+"饥渴";
        
        hpstr[6]= sprintf(NOR CYN"┃"NOR WHT"〖 饮水 〗%s%7-d/%7-d [%4s%s]"NOR,status_color(my["water"], ob->max_water_capacity()),my["water"], ob->max_water_capacity(),str,status_color(my["water"], ob->max_water_capacity()))+ sprintf(NOR WHT"  〖 潜能 〗%s%14-d "NOR CYN"       ┃\n"NOR,HIG,(int)ob->query("potential") - (int)ob->query("learned_points"));       


        
        dao=(int)ob->query("daoxing");
        str = YEL;
        hpstr[7]= sprintf(NOR CYN"┃"NOR WHT"〖 道行 〗%s%52-s    "NOR CYN"┃\n"NOR,HIM,chinese_daoxing(dao));    
        hpstr[8]= sprintf(NOR CYN"┃"NOR WHT"〖 官职 〗%s%11-d "NOR,HIG,(int)ob->query("office_number"))+sprintf(NOR WHT"  〖 战意 〗%s%10-d "NOR CYN"  "HIG,HIR,(int)ob->query_temp("zhanyi"))+sprintf(NOR WHT"  〖 杀气 〗%s%5-d "NOR CYN" ┃\n"HIG,HIR,(int)ob->query("bellicosity"));
        
        if (ob->query("degree")){
                hpstr[9]= sprintf(NOR CYN"┃"NOR WHT"〖 官拜 〗%s%35-s                  "NOR,HIW,ob->query("degree"))+sprintf(NOR  HIW"  〖 等级 〗   "NOR "%s%3-d "CYN"┃\n"NOR ,str,ob->query("level"));
        }else{
                hpstr[9]= sprintf(NOR CYN"┃"NOR WHT"〖 官拜 〗%s%35-s    "NOR ,HIW,"未入仕途")+sprintf(NOR  HIW"  〖 等级 〗   "NOR "%s%3-d "CYN"┃\n"NOR ,str,ob->query("level"));
        }
        str = HIY;              
        hpstr[10]= sprintf(NOR CYN"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n"NOR);
        hpstr[11]= sprintf(NOR CYN"┃"NOR MAG"    〖 特技点数 〗 "NOR WHT"%3d"NOR ,ob->query("special_point")-ob->query("specialed_point"))+ sprintf(NOR CYN""NOR MAG"    〖 属性点数 〗 "NOR WHT"%3d"NOR ,ob->query("attribute_point")-ob->query("attributed_point"))+sprintf(NOR CYN""NOR MAG"  〖 技能点数 〗 "NOR WHT"%3d"NOR CYN" ┃\n"NOR ,ob->query("skills_point")-ob->query("skillsed_point"));
        
        hpstr[12]= sprintf(NOR CYN"┗━━━━━━━━━━━━━━"HIY"X"HIR"·"HIY"L"HIR"·"HIY"Q"HIR"·"HIY"Y"NOR CYN"━━━━━━━━━━━━━━┛\n"NOR);

        return hpstr;
}
