//Cracked by Roath
//changan city

inherit ROOM;
//#include "/d/obj/misc/jitan.h"

void create ()
{
        set ("short", "������");
        set ("long", @LONG

����ʼ����������ƣ�̨�Ϲ�����һ�����ϵ�����Ȼ��
���ؾ����صؽ����������������������˵����񹩷�����
��,��������յİ�����ҵ��
LONG);

//  set("no_quit",1);
//  set("no_flee",1);
//  set("alternative_die",1);
        //set("item_desc", ([" *** " : " *** ", ]));

	set("no_fight",1);
	set("no_cast",1);
	set("no_kill",1);
	set("no_magic",1);
        set("exits", 
        ([ //sizeof() == 4
		"south" : __DIR__"qinglong-e3",
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/keeper" : 1,
                __DIR__"npc/guan" : 1,
        ]));

//        set("outdoors", "changan");
	set("no_clean_up", 0);
        setup();
	replace_program(ROOM);
}



