// Room: /d/menggu/downxuanya.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
���͵�ɽ�±���,Į���ຮ�ķ�ɳ��ʴ,ɽ�¸��ǹ⻬�վ�.������
��ƽƽ��ɽʯ�����,����ɫ��ɽʯ��������,ֱ������еİ������.
��ͷ��ɫ�Ĵ��Χ����ɽ�±ߵ�һ����������.
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
                	{message("vision", NOR"���Ÿ��ˣ�������ϲ�ȥ��\n"NOR,ob);
			return 1;}
                }
        if( arg != "up" )
                return 1;
        tell_object(ob, HIG"��һ����˳���ͱ�������ȥ��������\n"NOR);
        message("vision", NOR"ֻ��" + ob->query("name") + "����������ȥ��������\n"NOR, environment(ob), ob);
        ob->move(__DIR__"yading");
        return 1;
}


