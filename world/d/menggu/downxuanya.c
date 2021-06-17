// Room: /d/menggu/downxuanya.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "悬崖下");
	set("long", @LONG
陡峭的山崖壁立,漠北苦寒的风沙侵蚀,山崖更是光滑险峻.几柱矮
树平平从山石中伸出,铁灰色的山石愈行愈高,直与天空中的白云相接.
两头白色的大雕围绕着山崖边的一株松树鸣叫.
LONG
	);
	set("objects", ([ /* sizeof() == 1 */
]));
	set("outdoors", "menggu");
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"xiaolu",
]));

	setup();
}
void init()
{
	add_action("do_climb","climb");
}

int do_climb(string arg)
{
	int i;
	object *inv;
        object ob;
        ob = this_player();
        if( !arg || arg=="" ) return 0;
        inv = all_inventory(ob);
        for(i=0; i<sizeof(inv); i++)
                {	if (inv[i]->is_character() )
                	{message("vision", NOR"背着个人，你恐怕上不去。\n"NOR,ob);
			return 1;}
                }
        if( arg != "up" )
                return 1;
        tell_object(ob, HIG"你一纵身，顺着峭壁爬了上去。。。。\n"NOR);
        message("vision", NOR"只见" + ob->query("name") + "纵身爬了上去。。。。\n"NOR, environment(ob), ob);
        ob->move(__DIR__"yading");
        return 1;
}


