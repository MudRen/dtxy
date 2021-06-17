//changan city
// Cracked by 凌惊雪 1-3-2003

inherit ROOM;
#include <ansi.h>

void create ()
{
        set ("short", "龙窖西面");
        set ("long", 
"这儿就是龙窖了，眼前一片昏暗，面前的去路都被很多\n"
HIG"石头(stone)"NOR"给堵住了。\n\n"

);
	set("objects", ([ /* sizeof() == 1 */
        	__DIR__"npc/longnu.c" : 1,
	]));
  	set("item_desc", ([ /* sizeof() == 1 */
  		"stone" : HIY"很多巨大的石块，你可以推推(push)看。\n"NOR,
  		"石头" : HIY"很多巨大的石块，你可以推推(push)看。\n"NOR
	]));
        setup();
}
void init()
{
	add_action("do_push","push");
add_action("do_cast",({"cast"}));
}

int do_push(string arg)
{
	int i;
	object *inv;
        object ob ,room;
        ob = this_player();
        if(!( room = find_object("/d/menggu/longjiao")) )
                room = load_object("/d/menggu/longjiao");
        if( !arg || arg=="" ) return 0;
        if( ob->query_temp("julong_ask")!=1 ) return 0;
	if ( present("julong nu") )
		return notify_fail("龙奴伸手拦住了你。\n");
        inv = all_inventory(ob);
        for(i=0; i<sizeof(inv); i++)
                {	if (inv[i]->is_character() )
                	{message("vision", NOR"你身上背着什么东西？最好不要这样做，很危险的。\n"NOR,ob);
			return 1;}
                }
        if( arg != "stone" && arg != "石头")
                return notify_fail("你要推什么？\n");
        tell_object(ob, HIG"你用尽力气，总算把眼前的石头推开了一些。。。。\n"NOR);
	if (room->query("push") == "south")
        	{
        	tell_object(ob, HIR"你费尽力气，总算进了龙窖。\n"NOR);
        	ob->move("/d/menggu/longjiao");
                ob->set_temp("julong_kill",1);
                 room->add("hero",1);
        	return 1;
        	}
	if (room->query("push_id") == (string)ob->query("id"))
        	return 1;
	if (room->query("push") == "west")
        	return 1;
	if (room->query("push") == "east")
	{
        room->set("push","west");
	room->set("push_id",ob->query("id"));
        return 1;
	}
        return 1;
}

int do_cast(string arg) {
    string *banned_cast=({"chuqiao","qiankun","jieti"});
    if(!arg) return 0;
    while(sscanf(arg,"%s %*s",arg)==2) ;
    if(member_array(arg,banned_cast)==-1) return 0;
    write("这个地方没法使用"+arg+"。\n");
    return 1;
}

