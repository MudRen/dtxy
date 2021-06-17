// Room: /d/menggu/yading
#include <ansi.h>
inherit ROOM;

void create()
{
  set ("short", "山崖顶");
  set ("long", @LONG
崖顶是个巨大的平台，积满了皑皑白雪。几块巨大的石头半卧在一边,
形状千奇百怪,上面有许多洞穿的小孔,风过处,如泣如诉.四边的山崖平平
如削,几棵矮树就斜长于崖边.
LONG);
	set("objects", ([ /* sizeof() == 1 */
        __DIR__"npc/fengxue.c" : 1,
]));

  set("outdoors", "menggu");
  setup();
}
void init()
{
	add_action("do_jump","jump");
}

int do_jump(string arg)
{
	int i;
	object *inv;
        object ob;
        ob = this_player();
        if( !arg || arg=="" ) return 0;
        if( ob->query_temp("julong_ask")!=1 ) return 0;
        if( (int)ob->query("combat_exp")<3000000 ) return 0;
        inv = all_inventory(ob);
        for(i=0; i<sizeof(inv); i++)
                {	if (inv[i]->is_character() )
                	{message("vision", NOR"你还是等会再跳吧．\n"NOR,ob);
			return 1;}
                }
        if( arg != "down" )
                return notify_fail("你想要跳崖自杀？这么想不开啊？\n");
        tell_object(ob, HIR"你不加思索，纵身一跃，跳下了悬崖。。。。\n"NOR);
        message("vision", NOR"只见" + ob->query("name") + "纵身跳入了悬崖之中。。。。\n"NOR, environment(ob), ob);
        if((ob->query_skill("dodge",1)<30))
        	ob->unconcious();
        ob->move(__DIR__"entrance");
        return 1;
}


